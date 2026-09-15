"""Dibuja los sprites 2D de un nivel (seccion 2 del .INO): registros de 32 bytes con el mismo formato que
las texturas (h4 ancho, h5 alto, h6 TPAGE, h7 CLUT, h8 u y v dentro de la pagina).

Uso: python sprites.py H1W        deja notas\\modelos\\<nivel>\\sprites.png
"""
import os
import struct
import sys

import numpy as np
from PIL import Image, ImageDraw

import ino
from ino_obj import SAL, Texturas

nivel = sys.argv[1]
s = ino.leer_ino(nivel)
tex = Texturas(nivel, s["texturas"])
imgs = []
for k, r in enumerate(s["sec2"]):
    h = struct.unpack("<16H", r)
    w, alto, tpage, clut, uo, vo = h[4], h[5], h[6], h[7], h[8] & 0xFF, h[8] >> 8
    pag = tex.pagina(tpage, clut)
    if pag is None or not (0 < w <= 256 and 0 < alto <= 256):
        imgs.append((k, None, (w, alto, tpage, clut)))
        continue
    rgb, alfa = pag
    v = (np.arange(alto) + vo) & 0xFF
    u = (np.arange(w) + uo) & 0xFF
    trozo = np.dstack([rgb[v][:, u], alfa[v][:, u][..., None] * 255]).astype(np.uint8)
    imgs.append((k, Image.fromarray(trozo, "RGBA"), (w, alto, tpage, clut)))
celda = 72
hoja = Image.new("RGB", (celda * 10, (celda + 12) * ((len(imgs) + 9) // 10)), (60, 60, 60))
d = ImageDraw.Draw(hoja)
for i, (k, im, dat) in enumerate(imgs):
    x, y = (i % 10) * celda, (i // 10) * (celda + 12)
    d.text((x + 2, y), f"{k} {dat[0]}x{dat[1]}", fill=(255, 255, 255))
    if im is not None:
        im.thumbnail((celda - 4, celda - 4))
        hoja.paste(im, (x + 2, y + 12), im)
os.makedirs(os.path.join(SAL, nivel), exist_ok=True)
ruta = os.path.join(SAL, nivel, "sprites.png")
hoja.save(ruta)
print(ruta, len(imgs), "sprites")
