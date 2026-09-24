"""Convierte un .TEX completo (512x512, 16 bits, la mitad derecha de la VRAM) a PNG y de vuelta,
igual que pic.py hace con los .PIC.

Uso
  python tex.py a_png  entrada.TEX salida.png
  python tex.py a_tex  entrada.png salida.TEX     (la imagen debe medir 512x512)
  python tex.py todos  carpeta_salida             (convierte todos los .TEX del juego)

Ojo, esto NO es lo mismo que tex_ver.py: tex_ver.py exporta tres vistas de solo lectura (16, 8 y
4 bits) para ver la forma de cada textura. Este script en cambio hace el viaje completo de ida y
vuelta, pero solo tiene sentido pintar directo sobre el PNG en las partes del .TEX que son colores de
16 bits de verdad: los modelos y letras usan texturas de 4 u 8 bits (un numero por pixel que senala
una posicion de paleta, no un color), asi que ahi lo que se ve en este PNG es la paleta entera
aplastada en una fila de swatches (como en notas\\capturas de mod_rosa), no la forma del dibujo. Para
esas franjas, lo que se puede repintar con este script es el COLOR de cada entrada de la paleta (que
es lo que hacen mod_ropa.py y mod_rosa.py a mano); para redibujar la FORMA habria que editar la vista
de 4/8 bits de tex_ver.py y reempacar los nibbles/bytes de vuelta, que todavia no esta hecho.

Formato de pixel de la PS1: bits 0-4 rojo, 5-9 verde, 10-14 azul, bit 15 semitransparencia. A
diferencia de pic.py, aca 0x0000 se deja tal cual (no se fuerza a 1): en las paletas 0x0000 suele
querer decir "color transparente" a proposito (indice 0 del CLUT), y forzarlo cambiaria ese
significado. El bit 15 se guarda en el canal alfa del PNG (255 = marcado, 0 = no) para que el viaje
de ida y vuelta sea exacto; si se pinta con un editor que no respeta el alfa, ese bit se pierde.
"""
import glob
import os
import struct
import sys

from PIL import Image

ANCHO = ALTO = 512
EXTRAIDO = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "extraido")


def tex_a_imagen(datos):
    if len(datos) != ANCHO * ALTO * 2:
        raise ValueError(f"un TEX mide {ANCHO * ALTO * 2} bytes, este {len(datos)}")
    rgba = bytearray()
    for (v,) in struct.iter_unpack("<H", datos):
        r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
        rgba += bytes(((r << 3) | (r >> 2), (g << 3) | (g >> 2), (b << 3) | (b >> 2),
                       255 if v & 0x8000 else 0))
    return Image.frombytes("RGBA", (ANCHO, ALTO), bytes(rgba))


def imagen_a_tex(img):
    img = img.convert("RGBA")
    if img.size != (ANCHO, ALTO):
        raise ValueError(f"la imagen debe medir {ANCHO}x{ALTO}, mide {img.size}")
    out = bytearray()
    for r, g, b, a in img.getdata():
        v = (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10) | (0x8000 if a >= 128 else 0)
        out += struct.pack("<H", v)
    return bytes(out)


if __name__ == "__main__":
    modo = sys.argv[1]
    if modo == "a_png":
        tex_a_imagen(open(sys.argv[2], "rb").read()).save(sys.argv[3])
    elif modo == "a_tex":
        open(sys.argv[3], "wb").write(imagen_a_tex(Image.open(sys.argv[2])))
    elif modo == "todos":
        os.makedirs(sys.argv[2], exist_ok=True)
        for ruta in sorted(glob.glob(os.path.join(EXTRAIDO, "GRAPHICS", "*", "*.TEX"))):
            nombre = os.path.splitext(os.path.basename(ruta))[0]
            tex_a_imagen(open(ruta, "rb").read()).save(os.path.join(sys.argv[2], nombre + ".png"))
            print(nombre)
