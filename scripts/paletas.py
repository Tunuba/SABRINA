"""Busca que paleta (CLUT) de la VRAM pinta un color que se ve en pantalla, cambiandolas en vivo.

Uso: python paletas.py <estado> <r> <g> <b> [tolerancia] [y_desde]
  Ejemplo, el naranja del pantalon de Sabrina: python paletas.py saltar 230 90 20 60 400
Para cada grupo de 16 colores alineado (una paleta de 4 bits) en la mitad derecha de la VRAM desde la
fila y_desde que tenga algun color parecido al pedido, cambia esos colores por azul, captura, mide
cuantos pixeles de la pantalla cambiaron y lo deja como estaba. Imprime las paletas que mas pintan y
arma una hoja con sus capturas en notas\\capturas\\paletas_hoja.png.
"""
import io
import os
import struct
import sys

import numpy as np
from PIL import Image

from emu import RAIZ, Emu
from explorar import CUE, estado
from hoja import hoja

est = sys.argv[1]
objetivo = np.array([int(v) for v in sys.argv[2:5]])
tol = int(sys.argv[5]) if len(sys.argv) > 5 else 60
y0 = int(sys.argv[6]) if len(sys.argv) > 6 else 440
CAP = os.path.join(RAIZ, r"notas\capturas")


def rgb(v):
    return np.array([(v & 31) << 3, ((v >> 5) & 31) << 3, ((v >> 10) & 31) << 3])


def captura(e):
    return np.asarray(Image.open(io.BytesIO(e._pedir("/api/v1/screen/still"))).convert("RGB")).astype(int)


with Emu(iso=CUE, log="paletas.log", extra=("-fastboot",)) as e:
    e.cargar(estado(est))
    e.esperar(4)
    e.eval("PCSX.pauseEmulator(); return 'ok'")     # quieto, para que solo cambie lo que cambie la paleta
    vram = bytearray(e.vram())
    e.eval("PCSX.resumeEmulator(); return 'ok'")
    base = None
    resultados = []
    for y in range(y0, 512):
        for x in range(512, 1024, 16):
            off = (y * 1024 + x) * 2
            pal = list(struct.unpack_from("<16H", vram, off))
            cerca = [i for i, v in enumerate(pal) if v and np.abs(rgb(v) - objetivo).max() <= tol]
            if not cerca:
                continue
            nueva = pal[:]
            for i in cerca:
                r, g, b = (pal[i] & 31), (pal[i] >> 5) & 31, (pal[i] >> 10) & 31
                nueva[i] = (pal[i] & 0x8000) | b | (g << 5) | (r << 10)    # rojo por azul
            if base is None:
                e.esperar(2)
                base = captura(e)
            e.escribir_vram(x, y, 16, 1, struct.pack("<16H", *nueva))
            e.esperar(2)
            img = captura(e)
            e.escribir_vram(x, y, 16, 1, struct.pack("<16H", *pal))
            if img.shape == base.shape:
                cambio = int((np.abs(img - base).sum(axis=2) > 60).sum())
            else:
                cambio = -1
            resultados.append((cambio, x, y, len(cerca), img))
    resultados.sort(key=lambda r: -r[0])
    print(f"{len(resultados)} paletas con ese color")
    rutas = []
    for cambio, x, y, n, img in resultados[:12]:
        print(f"  paleta x {x} y {y}: {n} colores parecidos, {cambio} pixeles cambian")
        r = os.path.join(CAP, f"paleta_{x}_{y}.png")
        Image.fromarray(img.astype(np.uint8)).save(r)
        rutas.append(r)
    if rutas:
        hoja(os.path.join(CAP, "paletas_hoja.png"), 4, rutas)
