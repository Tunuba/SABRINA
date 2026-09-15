"""Convierte un volcado de VRAM de PS1 (1024x512, 16 bits por pixel, 1 MB) en PNG.

Uso: python vram_png.py entrada.vram salida.png

Cada pixel es 0bSBBBBBGGGGGRRRRR en little endian. El bit S (semitransparencia) se ignora.
Las texturas de 4 y 8 bits se ven como franjas de colores raros; eso es normal, porque la
VRAM se interpreta aqui toda como si fuera de 16 bits.
"""
import sys

from PIL import Image


def vram_a_imagen(datos: bytes) -> Image.Image:
    if len(datos) != 1024 * 512 * 2:
        raise ValueError(f"se esperaban 1048576 bytes, llegaron {len(datos)}")
    rgb = bytearray(1024 * 512 * 3)
    for i in range(1024 * 512):
        v = datos[2 * i] | (datos[2 * i + 1] << 8)
        r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
        rgb[3 * i] = (r << 3) | (r >> 2)
        rgb[3 * i + 1] = (g << 3) | (g >> 2)
        rgb[3 * i + 2] = (b << 3) | (b >> 2)
    return Image.frombytes("RGB", (1024, 512), bytes(rgb))


if __name__ == "__main__":
    with open(sys.argv[1], "rb") as f:
        vram_a_imagen(f.read()).save(sys.argv[2])
