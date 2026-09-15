"""Primer mod: la pantalla de carga "Loading ... please wait" (GRAPHICS\\FRONT\\FR.PIC) en espanol.

Busca la caja del texto original por brillo, la pinta con el color del fondo y escribe el texto
nuevo centrado en el mismo sitio, con el mismo gris. Deja el disco parchado en
  disco\\sabrina_mod (Track 01).bin  y  disco\\sabrina_mod.cue
y la imagen editada en mods\\FR_es.png para revisarla.

Uso: python mod_carga.py ["Texto nuevo"]
"""
import os
import sys
from collections import Counter

from PIL import Image, ImageDraw, ImageFont

import disco
from pic import imagen_a_pic, pic_a_imagen

TEXTO = sys.argv[1] if len(sys.argv) > 1 else "Cargando... espera un momento"
RUTA = r"GRAPHICS\FRONT\FR.PIC"
MODS = os.path.join(disco.RAIZ, "mods")
os.makedirs(MODS, exist_ok=True)

img = pic_a_imagen(open(os.path.join(disco.RAIZ, "extraido", RUTA), "rb").read())
px = img.load()

# El texto es lo claro en la franja de arriba; la barra de progreso queda mas abajo (y > 150)
claros = [(x, y) for y in range(150) for x in range(512) if sum(px[x, y]) > 180]
x0, x1 = min(x for x, _ in claros), max(x for x, _ in claros)
y0, y1 = min(y for _, y in claros), max(y for _, y in claros)
fondo = Counter(px[x, y] for y in range(10) for x in range(512)).most_common(1)[0][0]
tinta = Counter(px[x, y] for x, y in claros).most_common(1)[0][0]
print(f"texto original en x {x0}-{x1}, y {y0}-{y1}; fondo {fondo}, tinta {tinta}")

d = ImageDraw.Draw(img)
d.rectangle((x0 - 2, y0 - 2, x1 + 2, y1 + 2), fill=fondo)
alto = y1 - y0 + 1
fuente = ImageFont.truetype(r"C:\Windows\Fonts\arialbd.ttf", int(alto * 1.25))
caja = d.textbbox((0, 0), TEXTO, font=fuente)
ancho_t = caja[2] - caja[0]
if ancho_t > 500:
    fuente = ImageFont.truetype(r"C:\Windows\Fonts\arialbd.ttf", int(alto * 1.25 * 500 / ancho_t))
    caja = d.textbbox((0, 0), TEXTO, font=fuente)
cx, cy = (x0 + x1) // 2, (y0 + y1) // 2
d.text((cx - (caja[2] - caja[0]) // 2 - caja[0], cy - (caja[3] - caja[1]) // 2 - caja[1]), TEXTO,
       font=fuente, fill=tinta)
img.save(os.path.join(MODS, "FR_es.png"))

pista = os.path.join(disco.DISCO, "sabrina_mod (Track 01).bin")
disco.parchar({RUTA: imagen_a_pic(img)}, pista)
disco.cue_mod(os.path.join(disco.DISCO, "sabrina_mod.cue"), pista)
print("disco parchado:", pista)
