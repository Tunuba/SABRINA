"""SABRINA KART: arma el disco con la pista (niveles\\kart.json) y el ejecutable con el modo carrera, y lo abre.

El modo carrera es C del juego descompilado: decomp/src/objetos/kart.inc, que se compila dentro de la camara
(camara_g08.c) solo con -DSABRINA_KART. armar_c.py lo mete en los huecos de las funciones de la camara
(decomp/build/SLUS_kart.exe) y aqui se parchan en una copia del disco el ejecutable y el nivel del HUB.

Uso: python kart.py              abre el juego en la pista (arma el disco si falta)
     python kart.py armar        vuelve a armar todo: pista (mapa_kart.py), ejecutable (WSL) y disco
     python kart.py probar       lo arranca sin ventana, prueba la salida, el giro y los muros y saca capturas
     python kart.py vuelta       sin ventana, el piloto automatico corre las 3 vueltas y avisa si se atasca
     python kart.py vuelta ganar lo mismo con Salem congelado, para ver la fiesta de cuando gana Sabrina
"""
import os
import subprocess
import sys

import disco
import traducir
from emu import RAIZ, Emu
from explorar import CAP, recorrer

CUE = os.path.join(disco.DISCO, "sabrina_kart.cue")
PISTA = os.path.join(disco.DISCO, "sabrina_kart (Track 01).bin")
EXE = os.path.join(RAIZ, "decomp", "build", "SLUS_kart.exe")
SOLO = os.path.join(RAIZ, "decomp", "build", "kart_solo.txt")
NIVEL = os.path.join(RAIZ, "niveles", "kart.json")
PASOS_HASTA_EL_HUB = "w2160 CROSS w300 START w60 CROSS w240 w1300"
# las funciones que se arman en C: todas las de la camara (sus huecos guardan el kart)
CAMARA = ("func_800350A4,func_800350FC,func_80036250,func_8003630C,func_80036410,func_80036524,func_8003795C,"
          "func_8003821C,func_80037278,func_80037468,func_80037738,func_80036880,func_80036D58,func_80037A18,"
          "func_80035314,func_800365F0")


def wsl():
    """El distro de WSL con el compilador (en esta PC Ubuntu-24.04; en la del amigo Ubuntu)."""
    r = subprocess.run(["wsl.exe", "-l", "-q"], capture_output=True)
    nombres = r.stdout.decode("utf-16-le", "ignore").split()
    return "Ubuntu-24.04" if "Ubuntu-24.04" in nombres else "Ubuntu"


def armar_exe():
    d = os.path.join(RAIZ, "decomp").replace("\\", "/")
    ruta_wsl = "/mnt/" + d[0].lower() + d[2:]
    r = subprocess.run(["wsl.exe", "-d", wsl(), "--cd", ruta_wsl, "--", "python3", "armar_c.py", "--solo", CAMARA,
                        "--D", "SABRINA_KART", "--O", "Os", "--huecos", "src/mods/kart_huecos.c",
                        "--salida", "build/SLUS_kart.exe"], capture_output=True, text=True)
    print(r.stdout.strip(), r.stderr.strip())
    if r.returncode or "funciones en C" not in r.stdout or "otros: 0" not in r.stdout:
        sys.exit("no se pudo armar el ejecutable del kart (ver decomp/build/armado_c.txt)")


def armar_disco():
    import nivel_plataformas as n
    plats, cielo = n.cargar_nivel(NIVEL)
    errores, _ = n.validar(plats)
    if errores:
        sys.exit("pista invalida: " + "; ".join(errores))
    import kart_modelo
    ino = n.nf.construir_bytes(n.nodo_de(plats), n.CONSERVAR_PLAT, sin_objetos=True, paredes=True,
                               reemplazos={n.INDICE_CIELO: n.nodo_cielo(dict(n.CIELO_DEFECTO, **(cielo or {}))),
                                           1: kart_modelo.armar, 11: kart_modelo.vacio, 17: kart_modelo.rival,
                                           20: kart_modelo.caja, 21: kart_modelo.pocion, 22: kart_modelo.bola})
    disco.parchar({traducir.EXE: open(EXE, "rb").read(), "GRAPHICS\\HUB\\H1W.INO": ino}, PISTA)
    disco.cue_mod(CUE, PISTA)
    # la musica del pueblo (pista 3) es la de la carrera: musica_kart.py, hecha con los sonidos del juego
    import musica_kart
    if not os.path.exists(musica_kart.PISTA):
        musica_kart.escribir(musica_kart.componer())
    texto = open(CUE, encoding="utf-8").read()
    original = f'"{disco.NOMBRE} (Track 03).bin"'
    assert original in texto
    open(CUE, "w", encoding="utf-8").write(texto.replace(original, f'"{os.path.basename(musica_kart.PISTA)}"', 1))
    print("disco", CUE)


def armar():
    subprocess.run([sys.executable, os.path.join(RAIZ, "scripts", "mapa_kart.py")], check=True)
    subprocess.run([sys.executable, os.path.join(RAIZ, "scripts", "musica_kart.py")], check=True)
    armar_exe()
    armar_disco()


def leer(e, dir_, tam=4):
    v = int(float(e.eval(f"return rd{tam * 8}({dir_})")))
    return v - (1 << (tam * 8)) if v >= 1 << (tam * 8 - 1) else v


def probar():
    """Una prueba sin ventana: llega a la pista, espera la cuenta atras, deja que el kart acelere solo, gira, y va
    diciendo donde esta Sabrina; saca capturas en notas/capturas/kart_*.png."""
    from nivel_plataformas import P_SABRINA
    with Emu(iso=CUE, log="kart.log", extra=("-fastboot",), puerto=8096) as e:
        recorrer(e, "kart_arranque", PASOS_HASTA_EL_HUB)

        def donde(txt):
            s = leer(e, P_SABRINA)
            print(f"{txt:14s} cuadro {e.frames():6d}  x {leer(e, s + 0x24) / 256:8.0f}  y {leer(e, s + 0x28) / 256:6.0f}"
                  f"  z {leer(e, s + 0x2C) / 256:8.0f}  rumbo {leer(e, s + 0x32, 2) & 0xFFF:5d}", flush=True)
        donde("arranque")
        e.captura(os.path.join(CAP, "kart_0_arranque.png"))
        e.pulsar("SELECT", 4, 4)
        e.esperar(60)
        e.captura(os.path.join(CAP, "kart_1_cuenta.png"))
        e.esperar(150)
        donde("salida")
        e.esperar(90)
        e.captura(os.path.join(CAP, "kart_2_acelera.png"))
        e.esperar(90)
        donde("recta")
        e.captura(os.path.join(CAP, "kart_3_recta.png"))
        e.lua("boton", b="RIGHT", f=60)
        e.esperar(30)
        e.captura(os.path.join(CAP, "kart_4_giro.png"))
        e.esperar(30)
        donde("giro")
        e.lua("boton", b="RIGHT", f=400)
        e.esperar(400)
        donde("contra el muro")
        e.captura(os.path.join(CAP, "kart_5_muro.png"))


def simbolos():
    """Direcciones de las variables del kart (las static de kart.inc) en el ultimo armado (decomp/build/armado_c.elf)."""
    d = os.path.join(RAIZ, "decomp").replace("\\", "/")
    r = subprocess.run(["wsl.exe", "-d", wsl(), "--cd", "/mnt/" + d[0].lower() + d[2:], "--", "mipsel-linux-gnu-nm",
                        "build/armado_c.elf"], capture_output=True, text=True)
    sim = {}
    for linea in r.stdout.splitlines():
        p = linea.split()
        if len(p) == 3 and p[2].startswith("k_"):
            sim[p[2]] = int(p[0], 16)
    return sim


def vuelta(ganar=False, limite=30000):
    """Piloto automatico sin ventana: corre la carrera entera solo con izquierda y derecha, apuntando al centro de
    cada curva, y va diciendo vuelta, punto de control, rapidez y tiempo. Avisa si el kart se atasca (y saca una
    captura ahi) y mide cuantos pasos del juego hay por segundo (para K_SEG). Cada 2 segundos usa el hechizo que lleve.
    Al llegar saca capturas de la fiesta de la meta (fiesta_*.png). ganar: deja a Salem congelado (escribe su k_rhielo
    en la RAM) para ver la fiesta de cuando gana Sabrina. Capturas en notas/capturas/vuelta_*.png."""
    import math
    import mapa_kart as m
    from nivel_plataformas import P_SABRINA
    sim = simbolos()
    faltan = [k for k in ("k_tiempo", "k_vuelta", "k_cp", "k_fase", "k_vel") if k not in sim]
    if faltan:
        sys.exit(f"no estan en armado_c.elf: {faltan}")
    puntos = [(1024, -896), m.B, m.C, m.D, m.E, m.F, m.G, m.H, m.A]
    with Emu(iso=CUE, log="kart_vuelta.log", extra=("-fastboot",), puerto=8096) as e:
        recorrer(e, "kart_arranque", PASOS_HASTA_EL_HUB)
        e.pulsar("SELECT", 4, 4)
        s = leer(e, P_SABRINA)
        # una URL larga hace que el servidor del emulador conteste 404: las direcciones van en una tabla de Lua aparte
        dirs = [a & 0xFFFFFFFF for a in (s + 0x24, s + 0x2C, sim["k_tiempo"], sim["k_vuelta"], sim["k_cp"],
                                         sim["k_fase"], sim["k_vel"])]
        e.eval("KA={" + ",".join(map(str, dirs)) + "} return 1")
        e.eval(f"KR={(s + 0x32) & 0xFFFFFFFF} return 1")
        e.eval("function KK() local t={} for i,a in ipairs(KA) do t[i]=tonumber(rd32(a)) end "
               "t[#t+1]=tonumber(rd16(KR)) return table.concat(t,',') end return 1")
        consulta = "return KK()"
        firmado = lambda v: v - (1 << 32) if v >= 1 << 31 else v
        objetivo, inicio, t_inicio, ultimo, atascos = 1, None, None, [], 0
        f0 = e.frames()
        while e.frames() - f0 < limite:
            x, z, t, vta, k_cp, fase, vel, rumbo = (firmado(int(float(v))) for v in e.eval(consulta).split(","))
            x, z = x / 256, z / 256
            if fase == 2 and inicio is None:
                inicio, t_inicio = e.frames(), t
            if fase == 2 and ganar:
                e.eval(f"wr32({sim['k_rhielo'] & 0xFFFFFFFF},1000) return 1")
            if fase == 3:
                print(f"META en el cuadro {e.frames() - f0}: tiempo {t / 60:.2f} s", flush=True)
                for i in range(8):
                    e.esperar(30)
                    e.captura(os.path.join(CAP, f"fiesta_{i}.png"))
                if "k_puesto" in sim:
                    print(f"puesto de Sabrina: {leer(e, sim['k_puesto'] & 0xFFFFFFFF)}; Salem lleva "
                          f"{leer(e, sim['k_rd'] & 0xFFFFFFFF)} de {3 * 46640}", flush=True)
                break
            tx, tz = puntos[objetivo]
            if math.hypot(tx - x, tz - z) < 1000:
                objetivo = (objetivo + 1) % len(puntos)
                tx, tz = puntos[objetivo]
            quiere = math.atan2(tx - x, tz - z) * 4096 / (2 * math.pi)
            dif = (quiere - (rumbo & 0xFFF) + 2048) % 4096 - 2048
            boton = "RIGHT" if dif > 60 else ("LEFT" if dif < -60 else None)
            if (e.frames() - f0) % 120 < 4:
                boton = "TRIANGLE" if boton is None else boton + ",TRIANGLE"
            if boton:
                e.lua("boton", b=boton, f=4)
            e.esperar(4)
            ultimo.append((e.frames(), x, z))
            if len(ultimo) > 30:
                ultimo.pop(0)
                if fase == 2 and math.hypot(ultimo[-1][1] - ultimo[0][1], ultimo[-1][2] - ultimo[0][2]) < 300:
                    atascos += 1
                    print(f"ATASCADO en ({x:.0f}, {z:.0f}) vuelta {vta} punto {k_cp}", flush=True)
                    e.captura(os.path.join(CAP, f"vuelta_atasco{atascos}.png"))
                    ultimo.clear()
                    if atascos > 5:
                        break
            if (e.frames() - f0) % 240 < 4:
                print(f"cuadro {e.frames() - f0:6d}  vuelta {vta} punto {k_cp} rapidez {vel:5d}  ({x:7.0f}, {z:7.0f})"
                      f"  tiempo {t}", flush=True)
                e.captura(os.path.join(CAP, f"vuelta_{(e.frames() - f0) // 240:03d}.png"))
        if inicio is not None:
            cuadros = e.frames() - inicio
            pasos = t - t_inicio
            print(f"pasos del juego por segundo: {pasos * 60 / max(1, cuadros):.1f} ({pasos} en {cuadros} cuadros)")
        print("atascos:", atascos)


if __name__ == "__main__":
    modo = sys.argv[1] if len(sys.argv) > 1 else "jugar"
    if modo == "armar":
        armar()
    elif modo == "probar":
        if not os.path.exists(CUE):
            armar()
        probar()
    elif modo == "vuelta":
        if not os.path.exists(CUE):
            armar()
        vuelta(ganar="ganar" in sys.argv)
    elif modo == "jugar":
        if not os.path.exists(CUE):
            armar()
        print("abriendo SABRINA KART; espera unos 40 segundos a que pase la intro...", flush=True)
        with Emu(iso=CUE, log="kart_jugar.log", extra=("-fastboot",), puerto=8095, ui=True) as e:
            recorrer(e, "kart_jugar", PASOS_HASTA_EL_HUB)
            e.eval("PCSX.settings.spu.Mute = false; return 'ok'")
            print("listo: SELECT empieza la carrera (cierra la ventana del emulador para terminar)", flush=True)
            e.p.wait()
    else:
        print(__doc__)
