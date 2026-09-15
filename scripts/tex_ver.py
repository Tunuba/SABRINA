"""Muestra un .TEX (mitad derecha de la VRAM, 512x512 en unidades de 16 bits) de tres formas:
16 bits en color, 8 bits en gris (1024x512) y 4 bits en gris (2048x512). En la vista que toque,
cada textura se ve con su forma; los colores reales dependen de la paleta que elija el modelo.

Uso: python tex_ver.py entrada.TEX carpeta_salida
"""
import os
import sys

import numpy as np
from PIL import Image

d = np.frombuffer(open(sys.argv[1], "rb").read(), dtype=np.uint8)
sal = sys.argv[2]
os.makedirs(sal, exist_ok=True)
nombre = os.path.splitext(os.path.basename(sys.argv[1]))[0]

v16 = d.view("<u2").reshape(512, 512)
r, g, b = (v16 & 31), (v16 >> 5) & 31, (v16 >> 10) & 31
rgb = (np.stack([r, g, b], -1) * 255 // 31).astype(np.uint8)
Image.fromarray(rgb, "RGB").save(os.path.join(sal, f"{nombre}_16.png"))

Image.fromarray(d.reshape(512, 1024), "L").save(os.path.join(sal, f"{nombre}_8.png"))

n4 = np.empty(d.size * 2, dtype=np.uint8)
n4[0::2], n4[1::2] = d & 15, d >> 4
Image.fromarray((n4.reshape(512, 2048) * 17).astype(np.uint8), "L").save(os.path.join(sal, f"{nombre}_4.png"))
print("listo", nombre)
