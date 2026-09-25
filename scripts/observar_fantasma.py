"""Mira en vivo que le pasa a Sabrina en el nivel fantasma: arranca el disco, llega al HUB y, mientras camina,
anota cada pocos cuadros su posicion (objeto en 0x8007CAF8, +0x24 x, +0x28 y, +0x2C z; -y es arriba), su
funcion de estado (+0) y su vida (+0x118), y saca capturas de pantalla.

Uso: python observar_fantasma.py [disco.cue] ["pasos"]
"""
import os
import sys

from emu import RAIZ, Emu
from explorar import CAP, recorrer

cue = sys.argv[1] if len(sys.argv) > 1 and __name__ == "__main__" else os.path.join(RAIZ, "disco", "sabrina_fantasma.cue")
PASOS = sys.argv[2] if len(sys.argv) > 2 else "w30 UP:60 w30 RIGHT:60 w30 UP:90 w30 CROSS UP:40 w60"
P_SABRINA = 0x8007CAF8


def leer(e):
    # el endpoint eval corta el codigo a ~250 caracteres: una lectura corta por pedido
    p = int(float(e.eval(f"return rd32({P_SABRINA})")))
    if p == 0:
        return "sin objeto"
    s = lambda v: v - (1 << 32) if v >= 1 << 31 else v
    w = [int(float(e.eval(f"return rd32({p + o})"))) for o in (0x24, 0x28, 0x2C, 0)]
    vida = int(float(e.eval(f"return rd16({p + 0x118})")))
    return f"{s(w[0])} {s(w[1])} {s(w[2])} {w[3]:08x} {vida}"


if __name__ == "__main__":
    with Emu(iso=cue, log="observar_fantasma.log", extra=("-fastboot",), puerto=8098) as e:
        recorrer(e, "obs_arranque", "w2160 CROSS w300 START w60 CROSS w240 w1300")
        print("cuadro  x  y  z  estado  vida")
        cuadro = 0
        print(cuadro, leer(e), flush=True)
        for i, p in enumerate(PASOS.split()):
            recorrer(e, f"obs_{i:02d}", p + " c")
            cuadro += int(p.split(":")[1]) if ":" in p else int(p[1:]) if p[0] == "w" else 6
            print(cuadro, p, "|", leer(e), flush=True)
