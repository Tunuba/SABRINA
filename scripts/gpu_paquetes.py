"""Decodifica los paquetes de dibujo (display list) que el juego arma en la RAM para la GPU.

Cada poligono con textura lleva escrito su CLUT (paleta, en la VRAM) y su TPAGE (pagina de textura y
profundidad de color). Este script recorre la RAM buscando paquetes validos, agrupa los poligonos por
paleta y dice, por cada una, cuantos poligonos la usan, donde caen en pantalla y que colores tiene.

Uso: python gpu_paquetes.py <estado> [r g b]    con un color, marca las paletas que lo contienen
Tambien se usa como biblioteca: paquetes(ram) y paleta(vram, clut, bpp).

Formato de los comandos (psx-spx): poligonos con textura 0x24-0x27 (FT3, 7 palabras), 0x2C-0x2F (FT4, 9),
0x34-0x37 (GT3, 9), 0x3C-0x3F (GT4, 12). La palabra de uv0 lleva el CLUT arriba; la de uv1 lleva la TPAGE.
CLUT: x = (clut & 0x3f) * 16, y = (clut >> 6) & 0x1ff. TPAGE: x = (t & 0xf) * 64, y = ((t >> 4) & 1) * 256,
profundidad (t >> 7) & 3 (0 = 4 bits, 1 = 8 bits, 2 = 15 bits).
"""
import os
import struct
import sys
from collections import defaultdict

import numpy as np

# largo en palabras (sin la cabecera), indice de xy, de uv0 (con clut) y de uv1 (con tpage)
FORMAS = {}
for c in range(0x24, 0x28):
    FORMAS[c] = (7, (1, 3, 5), 2, 4)
for c in range(0x2C, 0x30):
    FORMAS[c] = (9, (1, 3, 5, 7), 2, 4)
for c in range(0x34, 0x38):
    FORMAS[c] = (9, (1, 4, 7), 2, 5)
for c in range(0x3C, 0x40):
    FORMAS[c] = (12, (1, 4, 7, 10), 2, 5)


def paquetes(ram):
    """Devuelve una lista de (direccion, cmd, clut, tpage, [(x, y), ...]) de poligonos con textura."""
    w = np.frombuffer(ram, dtype="<u4")
    n = len(w)
    res = []
    largos = w >> 24
    for i in np.nonzero((largos >= 7) & (largos <= 12))[0]:
        if i + 1 >= n:
            continue
        cmd = int(w[i + 1] >> 24)
        forma = FORMAS.get(cmd)
        if not forma or forma[0] != int(largos[i]) or i + 1 + forma[0] > n:
            continue
        sig = int(w[i]) & 0xFFFFFF
        if sig != 0xFFFFFF and (sig >= 0x200000 or sig & 3):
            continue
        p = w[i + 1:i + 1 + forma[0]]
        xy = []
        for k in forma[1]:
            x, y = struct.unpack("<hh", struct.pack("<I", int(p[k])))
            xy.append((x, y))
        if any(abs(x) > 1024 or abs(y) > 1024 for x, y in xy):
            continue
        clut = int(p[forma[2]]) >> 16
        tpage = int(p[forma[3]]) >> 16
        if (tpage >> 7) & 3 == 3:
            continue
        res.append((0x80000000 + 4 * int(i), cmd, clut, tpage, xy))
    return res


def clut_xy(clut):
    return (clut & 0x3F) * 16, (clut >> 6) & 0x1FF


def paleta(vram, clut, bpp):
    """Colores RGB de la paleta: 16 entradas si la textura es de 4 bits, 256 si es de 8."""
    x, y = clut_xy(clut)
    n = 16 if bpp == 0 else 256
    v = struct.unpack_from(f"<{n}H", vram, (y * 1024 + x) * 2)
    return [((c & 31) << 3, ((c >> 5) & 31) << 3, ((c >> 10) & 31) << 3) for c in v], list(v)


def resumen(ram, vram, color=None, tol=50):
    grupos = defaultdict(list)
    for dirc, cmd, clut, tpage, xy in paquetes(ram):
        grupos[(clut, tpage)].append(xy)
    filas = []
    for (clut, tpage), polis in grupos.items():
        bpp = (tpage >> 7) & 3
        xs = [x for p in polis for x, _ in p]
        ys = [y for p in polis for _, y in p]
        tiene = None
        if color is not None and bpp in (0, 1):
            cols, _ = paleta(vram, clut, bpp)
            tiene = sum(1 for c in cols if max(abs(c[k] - color[k]) for k in range(3)) <= tol)
        filas.append((len(polis), clut, tpage, bpp, min(xs), max(xs), min(ys), max(ys), tiene))
    filas.sort(key=lambda f: -f[0])
    return filas


if __name__ == "__main__":
    from emu import Emu
    from explorar import CUE, estado
    color = tuple(int(v) for v in sys.argv[2:5]) if len(sys.argv) >= 5 else None
    with Emu(iso=CUE, log="gpu.log", extra=("-fastboot",)) as e:
        e.cargar(estado(sys.argv[1]))
        e.esperar(4)
        e.eval("PCSX.pauseEmulator(); return 'ok'")
        ram, vram = e.ram(), e.vram()
    filas = resumen(ram, vram, color)
    print(f"{sum(f[0] for f in filas)} poligonos con textura, {len(filas)} combinaciones de paleta y pagina")
    for n, clut, tpage, bpp, x0, x1, y0, y1, tiene in filas[:60]:
        cx, cy = clut_xy(clut)
        tx, ty = (tpage & 0xF) * 64, ((tpage >> 4) & 1) * 256
        marca = f"  {tiene} colores parecidos" if tiene else ""
        print(f"  {n:4d} polis  clut ({cx:4d},{cy:3d})  pagina ({tx:4d},{ty:3d}) {4 << bpp if bpp < 2 else 16} bits"
              f"  pantalla x {x0}..{x1} y {y0}..{y1}{marca}")
