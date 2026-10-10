"""SABRINA KART: arma el disco con la pista (niveles\\kart.json) y el ejecutable con el modo carrera, y lo abre.

El modo carrera es C del juego descompilado: decomp/src/objetos/kart.inc, que se compila dentro de la camara
(camara_g08.c) solo con -DSABRINA_KART. armar_c.py lo mete en los huecos de las funciones de la camara
(decomp/build/SLUS_kart.exe) y aqui se parchan en una copia del disco el ejecutable y el nivel del HUB.

Uso: python kart.py              abre el juego en la pista (arma el disco si falta)
     python kart.py armar        vuelve a armar todo: pista (mapa_kart.py), ejecutable (WSL) y disco
     python kart.py probar       lo arranca sin ventana, prueba la salida, el giro y los muros y saca capturas
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
                        "--D", "SABRINA_KART", "--salida", "build/SLUS_kart.exe"], capture_output=True, text=True)
    print(r.stdout.strip(), r.stderr.strip())
    if r.returncode or "16 funciones en C" not in r.stdout:
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
                                           1: kart_modelo.armar})
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


if __name__ == "__main__":
    modo = sys.argv[1] if len(sys.argv) > 1 else "jugar"
    if modo == "armar":
        armar()
    elif modo == "probar":
        if not os.path.exists(CUE):
            armar()
        probar()
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
