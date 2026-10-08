"""Abre el juego con ventana y sonido, ya pasada la intro, para jugar una de las dos pruebas propias.

Uso: python jugar.py camara     camara libre (disco\\libre.cue, el ejecutable en C decomp\\build\\SLUS_libre.exe)
     python jugar.py nivel      nivel de plataformas (disco\\sabrina_plataformas.cue)
  --rearmar   vuelve a armar el disco aunque ya exista

Camara libre: SELECT la prende y la apaga; con ella prendida las flechas arriba/abajo avanzan, izquierda/derecha
giran, triangulo/equis miran arriba/abajo, L2/R2 van de lado, L1/R1 suben/bajan y cuadrado va mas rapido.
Se cierra al cerrar la ventana del emulador. Los atajos son CAMARA_LIBRE.bat y NIVEL_PLATAFORMAS.bat.
"""
import os
import subprocess
import sys

import disco
from emu import RAIZ, Emu
from explorar import recorrer

# lo mismo que mini_nivel.py / nivel_plataformas.py: pasar el titulo, "New game" y la intro del HUB
PASOS_HASTA_EL_HUB = "w2160 CROSS w300 START w60 CROSS w240 w1300"


def disco_camara(rearmar):
    cue = os.path.join(disco.DISCO, "libre.cue")
    if rearmar or not os.path.exists(cue):
        exe = os.path.join(RAIZ, "decomp", "build", "SLUS_libre.exe")
        if not os.path.exists(exe):
            sys.exit(f"falta {exe}: armalo con decomp\\armar_c.py (la camara libre va en camara_g08.c)")
        subprocess.run([sys.executable, os.path.join(RAIZ, "scripts", "armar_disco_c.py"), exe, "libre"], check=True)
    return cue


def disco_nivel(rearmar):
    import nivel_plataformas
    if rearmar or not os.path.exists(nivel_plataformas.CUE_PLAT):
        nivel_plataformas.armar_disco()
    return nivel_plataformas.CUE_PLAT


if __name__ == "__main__":
    modos = {"camara": disco_camara, "nivel": disco_nivel}
    if len(sys.argv) < 2 or sys.argv[1] not in modos:
        print(__doc__)
        sys.exit(1)
    modo = sys.argv[1]
    cue = modos[modo]("--rearmar" in sys.argv)
    print(f"abriendo {os.path.basename(cue)}; espera unos 40 segundos a que pase la intro...", flush=True)
    with Emu(iso=cue, log=f"jugar_{modo}.log", extra=("-fastboot",), puerto=8095, ui=True) as e:
        recorrer(e, f"jugar_{modo}", PASOS_HASTA_EL_HUB)
        e.eval("PCSX.settings.spu.Mute = false; return 'ok'")      # Emu lo deja mudo para las rondas automaticas
        print("listo, ya puedes jugar (cierra la ventana del emulador para terminar)", flush=True)
        e.p.wait()
