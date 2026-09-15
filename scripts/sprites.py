"""Dibuja los sprites 2D de un nivel: registros de 32 bytes con el mismo formato que las texturas
(h4 ancho, h5 alto, h6 TPAGE, h7 CLUT, h8 u y v dentro de la pagina).
  seccion 2 del .INO: la pantalla (iconos, digitos, retratos)
  seccion 5 del .INO: los cuadros de las particulas; cada efecto (tabla del ejecutable en 0x80074898)
  dice desde que cuadro empieza y cuantos usa (FUN_8001e9e4 y FUN_8001f?? en Particle.c)

Uso: python sprites.py H1W [particulas]   deja notas\\modelos\\<nivel>\\sprites.png o particulas.png
"""
import os
import struct
import sys

import numpy as np
from PIL import Image, ImageDraw

import ino
from ino_obj import SAL, Texturas

nivel = sys.argv[1]
seccion = "particulas" if len(sys.argv) > 2 and sys.argv[2] == "particulas" else "sec2"
s = ino.leer_ino(nivel)
tex = Texturas(nivel, s["texturas"])
imgs = []
for k, r in enumerate(s[seccion]):
    h = struct.unpack("<16H", r)
    w, alto, tpage, clut, uo, vo = h[4], h[5], h[6], h[7], h[8] & 0xFF, h[8] >> 8
    if seccion == "particulas":
        # h4 y h5 son el tamano en el mundo (0x1000 = 1.0); el de pixeles sale de la u y v finales en h14
        w, alto = (h[14] & 0xFF) - uo + 1, (h[14] >> 8) - vo + 1
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
ruta = os.path.join(SAL, nivel, "sprites.png" if seccion == "sec2" else "particulas.png")
hoja.save(ruta)
print(ruta, len(imgs), "sprites")
