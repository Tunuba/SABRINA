"""Junta varias capturas en una sola imagen, en cuadricula, con el nombre de cada una.

Uso: python hoja.py salida.png columnas captura1.png captura2.png ...
"""
import os
import sys

from PIL import Image, ImageDraw


def legible(r):
    """Las capturas con la pantalla apagada salen como PNG de 0x0, que PIL no abre."""
    try:
        Image.open(r).load()
        return True
    except Exception:
        return False


def hoja(salida, columnas, rutas, ancho=320, alto=240):
    rutas = [r for r in rutas if legible(r)]
    filas = (len(rutas) + columnas - 1) // columnas
    h = Image.new("RGB", (columnas * ancho, filas * (alto + 14)), (40, 40, 40))
    d = ImageDraw.Draw(h)
    for i, r in enumerate(rutas):
        x, y = (i % columnas) * ancho, (i // columnas) * (alto + 14)
        h.paste(Image.open(r).convert("RGB").resize((ancho, alto)), (x, y + 14))
        d.text((x + 4, y + 1), os.path.basename(r), fill=(255, 255, 255))
    h.save(salida)


if __name__ == "__main__":
    hoja(sys.argv[1], int(sys.argv[2]), sys.argv[3:])
