"""Dibuja texto con la letra del juego (seccion 4 del .INO, leida de FUN_80018d3c).

Tabla de letras: un registro de 12 bytes por codigo de caracter. +4 TPAGE (byte), +5 avance en pixeles,
+6 CLUT (int16), +8 u, +9 v, +10 ancho; el alto es 32. El caracter '~' (0x7E) no se dibuja: avanza 7.

Uso: python letra.py FRW "Nuevo juego"      deja notas\\modelos\\<nivel>\\texto.png
"""
import os
import struct
import sys

import numpy as np
from PIL import Image

import ino
from ino_obj import SAL, Texturas


# El juego convierte cada caracter ASCII a su casilla con la tabla de 128 bytes en 0x8006551C.
# Iconos: @ triangulo, < cuadrado, = X, > circulo, ` cruceta, ^ bloque de barra; el espacio da 126.
_o = 0x8006551C - 0x80010000 + 0x800
ASCII_A_LETRA = ino.EXE[_o:_o + 128]


def dibujar_texto(nivel, texto, escala=2):
    s = ino.leer_ino(nivel)
    tex = Texturas(nivel, s["texturas"])
    glifos = s["sec6"]
    codigos = [ASCII_A_LETRA[ord(c)] if ord(c) < 128 else 126 for c in texto]
    ancho = sum(7 if k >= len(glifos) else glifos[k][5] for k in codigos) + 8
    lienzo = np.zeros((40, ancho, 4), dtype=np.uint8)
    x = 4
    for k in codigos:
        if k >= len(glifos):          # 126: espacio
            x += 7
            continue
        g = glifos[k]
        tpage, avance, clut, u, v, w = g[4], g[5], struct.unpack_from("<H", g, 6)[0], g[8], g[9], g[10]
        pag = tex.pagina(tpage, clut)
        if pag is not None and w:
            rgb, alfa = pag
            vv = (np.arange(32) + v) & 0xFF
            uu = (np.arange(w) + u) & 0xFF
            trozo = np.dstack([rgb[vv][:, uu], alfa[vv][:, uu][..., None] * 255]).astype(np.uint8)
            dst = lienzo[4:36, x:x + w]
            trozo = trozo[:, :dst.shape[1]]
            m = trozo[..., 3] > 0
            dst[m] = trozo[m]
        x += avance
    img = Image.fromarray(lienzo, "RGBA")
    return img.resize((img.width * escala, img.height * escala), Image.NEAREST)


if __name__ == "__main__":
    nivel, texto = sys.argv[1], sys.argv[2]
    s = ino.leer_ino(nivel)
    print(f"{nivel}: {len(s['sec6'])} caracteres en la tabla")
    fondo = Image.new("RGBA", (1, 1), (20, 20, 60, 255))
    img = dibujar_texto(nivel, texto)
    salida = Image.new("RGBA", img.size, (20, 20, 60, 255))
    salida.alpha_composite(img)
    os.makedirs(os.path.join(SAL, nivel), exist_ok=True)
    ruta = os.path.join(SAL, nivel, "texto.png")
    salida.convert("RGB").save(ruta)
    print(ruta)
