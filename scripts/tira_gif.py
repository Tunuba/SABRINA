"""Junta cuadros sueltos de varios GIF en una hoja, una fila por GIF.

Uso: python tira_gif.py salida.png cuadros_por_fila a.gif b.gif ...
"""
import sys

from PIL import Image, ImageDraw

salida, n, rutas = sys.argv[1], int(sys.argv[2]), sys.argv[3:]
filas = []
for r in rutas:
    im = Image.open(r)
    paso = max(1, im.n_frames // n)
    cuadros = []
    for k in range(0, im.n_frames, paso):
        im.seek(k)
        cuadros.append(im.convert("RGB").resize((180, 180)))
    filas.append((r.split("\\")[-1], cuadros[:n]))
hoja = Image.new("RGB", (180 * n, 194 * len(filas)), (40, 40, 40))
d = ImageDraw.Draw(hoja)
for i, (nom, cuadros) in enumerate(filas):
    d.text((4, i * 194), nom, fill=(255, 255, 255))
    for k, c in enumerate(cuadros):
        hoja.paste(c, (k * 180, i * 194 + 14))
hoja.save(salida)
