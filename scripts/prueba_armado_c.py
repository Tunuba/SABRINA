"""Juega el mismo guion en el disco original y en el armado con C y compara.

Uso: python prueba_armado_c.py <disco_c.cue> [guion]
En cada paso 'c' guarda la captura y los SHA1 de la pantalla y de la RAM sin el codigo del juego
(0x80010000-0x8007D000 se ignora porque ahi cambian los bytes a proposito). Un emulador igual de
determinista en los dos discos deberia dar los mismos hashes.
"""
import hashlib
import os
import sys

from emu import RAIZ, Emu
from explorar import CAP

GUION = "w2160 c CROSS w300 START w60 CROSS w240 c w1300 c w300 c"


def correr(cue, nombre, guion):
    marcas = []
    with Emu(iso=os.path.join(RAIZ, "disco", cue), log=f"armadoc_{nombre}.log", extra=("-fastboot",),
             depurar=True) as e:
        n = 0
        for p in guion.split():
            if p == "c":
                r = os.path.join(CAP, f"armadoc_{nombre}_{n:02d}.png")
                e.captura(r)
                ram = e.ram()
                marcas.append((hashlib.sha1(open(r, "rb").read()).hexdigest()[:10],
                               hashlib.sha1(ram[0x7D000:]).hexdigest()[:10],
                               hashlib.sha1(ram[:0x10000]).hexdigest()[:10]))
                n += 1
            elif p[0] == "w" and p[1:].isdigit():
                e.esperar(int(p[1:]))
            else:
                b, _, f = p.partition(":")
                e.pulsar(b.replace("+", ","), f=int(f) if f else 6)
    return marcas


if __name__ == "__main__":
    guion = sys.argv[2] if len(sys.argv) > 2 else GUION
    a = correr(sys.argv[1], "c", guion)
    b = correr("Sabrina the Teenage Witch - A Twitch in Time! (USA).cue", "orig", guion)
    for i, (x, y) in enumerate(zip(a, b)):
        print(i, "pantalla", "IGUAL" if x[0] == y[0] else "DISTINTA", "| RAM", "IGUAL" if x[1] == y[1] else "DISTINTA",
              "| inicio RAM", "IGUAL" if x[2] == y[2] else "DISTINTA", x, y)
