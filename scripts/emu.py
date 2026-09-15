"""Arranca PCSX-Redux sin ventana y lo maneja por HTTP con las rutas de control.lua.

Ejemplo
    from emu import Emu
    with Emu(iso=r"C:\\Proyectos\\SABRINA\\disco\\sabrina.cue") as e:
        e.esperar(300)              # 5 segundos de juego
        e.pulsar("START")
        e.captura("titulo.png")
        ram = e.ram()               # 2 MB de RAM principal

Sin BIOS de Sony usa OpenBIOS, que viene con el emulador. Para usar una BIOS real, pasar
bios=r"ruta\\scph1001.bin".
"""
import os
import subprocess
import time
import urllib.parse
import urllib.request

RAIZ = r"C:\Proyectos\SABRINA"
REDUX = os.path.join(RAIZ, "herramientas", "pcsx-redux")
CONTROL = os.path.join(RAIZ, "scripts", "control.lua")
LOGS = os.path.join(RAIZ, "notas", "logs")


class Emu:
    def __init__(self, iso=None, exe=None, puerto=8091, bios=None, log="emu.log", extra=(), depurar=False):
        os.makedirs(LOGS, exist_ok=True)
        if depurar:
            # los puntos de interrupcion (contar en control.lua) solo funcionan con el interprete
            extra = (*extra, "-debugger", "-interpreter")
        self.base = f"http://127.0.0.1:{puerto}"
        args = [os.path.join(REDUX, "pcsx-redux.exe"), "-no-ui", "-stdout",
                "-bios", bios or os.path.join(REDUX, "openbios.bin"),
                "-webserver", "-webserver-port", str(puerto), "-softgpu",
                "-dofile", CONTROL, "-run", *extra]
        if iso:
            args += ["-iso", iso]
        if exe:
            args += ["-exe", exe]
        self.log = os.path.join(LOGS, log)
        # La salida estandar del lanzador llega vacia; los mensajes del emulador y los printf del
        # juego (por ejemplo "Loading %s...") van a -logfile
        self.tty = self.log.replace(".log", ".tty.log")
        args += ["-logfile", self.tty]
        self._logf = open(self.log, "wb")
        self.p = subprocess.Popen(args, cwd=REDUX, stdout=self._logf, stderr=subprocess.STDOUT,
                                  creationflags=subprocess.CREATE_NO_WINDOW)
        limite = time.time() + 30
        while True:
            try:
                self.frames()
                break
            except OSError:
                if self.p.poll() is not None:
                    raise RuntimeError(f"el emulador salio con codigo {self.p.returncode}, ver {self.log}")
                if time.time() > limite:
                    self.cerrar()
                    raise RuntimeError(f"el emulador no respondio en 30 s, ver {self.log}")
                time.sleep(0.2)

    def __enter__(self):
        return self

    def __exit__(self, *a):
        self.cerrar()

    def _pedir(self, ruta, datos=None, **q):
        url = self.base + ruta
        if q:
            url += "?" + urllib.parse.urlencode(q)
        with urllib.request.urlopen(urllib.request.Request(url, data=datos), timeout=60) as r:
            return r.read()

    def lua(self, nombre, **q):
        return self._pedir("/api/v1/lua/" + nombre, **q).decode("utf-8", "replace")

    def frames(self):
        return int(self.lua("frames"))

    def esperar(self, n):
        """Espera a que pasen n frames del juego (60 por segundo en NTSC)."""
        meta = self.frames() + n
        while self.frames() < meta:
            time.sleep(0.01)

    def pulsar(self, botones, f=6, soltar=6):
        """Pulsa botones (texto separado por comas) f frames y espera otros 'soltar' frames."""
        self.lua("boton", b=botones, f=f)
        self.esperar(f + soltar)

    def eval(self, codigo):
        return self.lua("eval", c=codigo)

    def captura(self, ruta):
        png = self._pedir("/api/v1/screen/still")
        with open(ruta, "wb") as f:
            f.write(png)
        return ruta

    def ram(self):
        return self._pedir("/api/v1/cpu/ram/raw")

    def vram(self):
        return self._pedir("/api/v1/gpu/vram/raw")

    def escribir_vram(self, x, y, ancho, alto, datos):
        """Escribe un rectangulo de la VRAM (unidades de 16 bits). datos: bytes de ancho*alto*2."""
        return self._pedir("/api/v1/gpu/vram/raw", datos=bytes(datos), x=x, y=y, width=ancho, height=alto)

    def guardar(self, ruta):
        return self.lua("guardar", n=os.path.abspath(ruta))

    def cargar(self, ruta):
        return self.lua("cargar", n=os.path.abspath(ruta))

    def cerrar(self):
        if self.p.poll() is None:
            try:
                self.lua("salir")
                self.p.wait(5)
            except (OSError, subprocess.TimeoutExpired):
                pass
        if self.p.poll() is None:
            subprocess.run(["taskkill", "/T", "/F", "/PID", str(self.p.pid)], capture_output=True)
        self._logf.close()
