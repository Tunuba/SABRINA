"""Recorre el juego con una lista de pasos y captura la pantalla, partiendo de un estado guardado.

Uso: python explorar.py <estado_inicial|arranque> <nombre> <pasos> [--guardar estado_final]
  pasos   lista separada por espacios. Cada paso es uno de
            BOTON[+BOTON][:frames]   pulsa (por defecto 6 frames), por ejemplo CROSS o UP+CROSS:30
            w<frames>                espera esos frames
            c                        guarda una captura
  arranque en vez de un estado arranca el disco desde cero.
Ejemplo: python explorar.py titulo nuevo "CROSS w120 c w120 c"
Las capturas quedan en notas\\capturas\\<nombre>_NN.png y una hoja con todas en <nombre>_hoja.png
Los estados viven en C:\\Proyectos\\SABRINA\\estados\\<nombre>.estado
"""
import os
import sys

from emu import RAIZ, Emu
from hoja import hoja

CUE = os.path.join(RAIZ, r"disco\Sabrina the Teenage Witch - A Twitch in Time! (USA).cue")
CAP = os.path.join(RAIZ, r"notas\capturas")
EST = os.path.join(RAIZ, "estados")
os.makedirs(CAP, exist_ok=True)
os.makedirs(EST, exist_ok=True)


def estado(nombre):
    return os.path.join(EST, nombre + ".estado")


def recorrer(e, nombre, pasos):
    capturas = []
    for p in pasos.split():
        if p == "c":
            r = os.path.join(CAP, f"{nombre}_{len(capturas):02d}.png")
            e.captura(r)
            capturas.append(r)
        elif p[0] == "w" and p[1:].isdigit():
            e.esperar(int(p[1:]))
        else:
            botones, _, f = p.partition(":")
            e.pulsar(botones.replace("+", ","), f=int(f) if f else 6)
    if capturas:
        hoja(os.path.join(CAP, f"{nombre}_hoja.png"), 4, capturas)
    return capturas


if __name__ == "__main__":
    inicio, nombre, pasos = sys.argv[1], sys.argv[2], sys.argv[3]
    final = sys.argv[sys.argv.index("--guardar") + 1] if "--guardar" in sys.argv else None
    # --cue otro.cue usa un disco parchado (en la carpeta disco). Ojo: un estado guardado trae el
    # ejecutable viejo en la RAM, asi que para ver cambios del ejecutable hay que partir de "arranque".
    cue = os.path.join(RAIZ, "disco", sys.argv[sys.argv.index("--cue") + 1]) if "--cue" in sys.argv else CUE
    with Emu(iso=cue, log=f"explorar_{nombre}.log", extra=("-fastboot",)) as e:
        if inicio != "arranque":
            e.cargar(estado(inicio))
            e.esperar(2)
        caps = recorrer(e, nombre, pasos)
        if final:
            e.guardar(estado(final))
        print(f"{len(caps)} capturas, frame {e.frames()}")
