"""Buscar valores en la RAM del juego comparando fotos de memoria, como un buscador de trucos.

Uso como biblioteca
    from memoria import foto, leer32, escribir32
    a = foto(e)        # numpy int32 de toda la RAM (2 MB, 524288 palabras)
Direcciones: la RAM empieza en 0x80000000; la palabra i esta en 0x80000000 + 4*i.

Uso directo: python memoria.py posicion
  Busca la posicion de Sabrina: palabras que no cambian quieta y cambian siempre hacia el mismo lado
  mientras camina hacia adelante.
"""
import os
import sys

import numpy as np

from emu import RAIZ, Emu

CUE = os.path.join(RAIZ, r"disco\Sabrina the Teenage Witch - A Twitch in Time! (USA).cue")


def foto(e):
    return np.frombuffer(e.ram(), dtype="<i4").copy()


def dir_(i):
    return 0x80000000 + 4 * int(i)


def leer32(e, direccion):
    off = direccion & 0x1FFFFF
    return int(e.eval(f"return ffi.cast('int32_t*', PCSX.getMemPtr() + {off})[0]"))


def escribir32(e, direccion, valor):
    off = direccion & 0x1FFFFF
    e.eval(f"ffi.cast('int32_t*', PCSX.getMemPtr() + {off})[0] = {int(valor)}; return 'ok'")


def buscar_posicion(estado="saltar", boton="UP"):
    with Emu(iso=CUE, log="memoria.log", extra=("-fastboot",)) as e:
        e.cargar(os.path.join(RAIZ, "estados", estado + ".estado"))
        e.esperar(20)
        s0 = foto(e)
        e.esperar(30)
        s1 = foto(e)
        e.lua("boton", b=boton, f=90)
        e.esperar(30)
        s2 = foto(e)
        e.esperar(30)
        s3 = foto(e)
        e.esperar(40)
        s4 = foto(e)
        e.esperar(40)
        s5 = foto(e)     # ya soltado: la posicion debe quedarse quieta otra vez
    todas = []
    for nombre, ancho, conv in (("32 bits", 4, None), ("16 bits", 2, "<i2")):
        f = [x if conv is None else x.view(conv).astype(np.int32) for x in (s0, s1, s2, s3, s4, s5)]
        d1, d2, d3 = f[2] - f[1], f[3] - f[2], f[4] - f[3]
        quieta = f[0] == f[1]
        mono = (np.sign(d1) == np.sign(d2)) & (np.sign(d2) == np.sign(d3)) & (d1 != 0)
        razonable = (np.abs(d1) > 4) & (np.abs(d1) < 1 << 22)
        cand = np.nonzero(quieta & mono & razonable)[0]
        print(f"{nombre}: {len(cand)} candidatas")
        for i in cand[:40]:
            print(f"  {0x80000000 + ancho * int(i):08x}  {f[1][i]:>11d} {f[2][i]:>11d} {f[3][i]:>11d} "
                  f"{f[4][i]:>11d} {f[5][i]:>11d}   pasos {d1[i]} {d2[i]} {d3[i]}")
        todas.append(cand)
    return todas


if __name__ == "__main__" and sys.argv[1:2] == ["posicion"]:
    buscar_posicion(*(sys.argv[2:4]))
