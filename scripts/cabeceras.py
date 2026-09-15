"""Muestra los primeros bytes de un archivo de cada tipo, para empezar a leer los formatos.

Uso: python cabeceras.py
"""
import glob
import os

EXT = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "extraido")

for patron in ("SLUS_012.08", r"GRAPHICS\HUB\H1.PIC", r"GRAPHICS\HUB\H1.TEX", r"GRAPHICS\HUB\H1W.INO",
               r"WRLDDATA\HUB\H1W.BIN", r"ANIMS\HUB.ANI", r"ANIMS\SABRINA.ANI", r"SOUND\HUB\H1W.VHD"):
    for ruta in glob.glob(os.path.join(EXT, patron)):
        d = open(ruta, "rb").read()
        print(f"== {patron}  {len(d)} bytes")
        for fila in range(0, 64, 16):
            b = d[fila:fila + 16]
            print(f"  {fila:04x}  {b.hex(' ')}  {''.join(chr(c) if 32 <= c < 127 else '.' for c in b)}")
