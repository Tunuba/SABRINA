"""Convierte los .PIC de Sabrina (pantallas completas de 512x220, 16 bits por pixel, sin cabecera)
a PNG y de vuelta.

Uso
  python pic.py a_png  entrada.PIC salida.png
  python pic.py a_pic  entrada.png salida.PIC     (la imagen debe medir 512x220)
  python pic.py todos  carpeta_salida            (convierte todos los .PIC del juego)

Formato de pixel de la PS1: bits 0-4 rojo, 5-9 verde, 10-14 azul, bit 15 semitransparencia.
El valor 0x0000 es transparente para la GPU, por eso el negro del juego se guarda como 0x0001 y
a_pic nunca escribe 0x0000.
"""
import glob
import os
import struct
import sys

from PIL import Image

ANCHO, ALTO = 512, 220
EXTRAIDO = r"C:\Proyectos\SABRINA\extraido"


def pic_a_imagen(datos):
    if len(datos) != ANCHO * ALTO * 2:
        raise ValueError(f"un PIC mide {ANCHO * ALTO * 2} bytes, este {len(datos)}")
    rgb = bytearray()
    for (v,) in struct.iter_unpack("<H", datos):
        r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
        rgb += bytes(((r << 3) | (r >> 2), (g << 3) | (g >> 2), (b << 3) | (b >> 2)))
    return Image.frombytes("RGB", (ANCHO, ALTO), bytes(rgb))


def imagen_a_pic(img):
    img = img.convert("RGB")
    if img.size != (ANCHO, ALTO):
        raise ValueError(f"la imagen debe medir {ANCHO}x{ALTO}, mide {img.size}")
    out = bytearray()
    for r, g, b in img.getdata():
        v = (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)
        out += struct.pack("<H", v or 1)
    return bytes(out)


if __name__ == "__main__":
    modo = sys.argv[1]
    if modo == "a_png":
        pic_a_imagen(open(sys.argv[2], "rb").read()).save(sys.argv[3])
    elif modo == "a_pic":
        open(sys.argv[3], "wb").write(imagen_a_pic(Image.open(sys.argv[2])))
    elif modo == "todos":
        os.makedirs(sys.argv[2], exist_ok=True)
        for ruta in sorted(glob.glob(os.path.join(EXTRAIDO, "GRAPHICS", "*", "*.PIC"))):
            nombre = os.path.splitext(os.path.basename(ruta))[0]
            pic_a_imagen(open(ruta, "rb").read()).save(os.path.join(sys.argv[2], nombre + ".png"))
            print(nombre)
