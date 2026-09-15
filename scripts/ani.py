"""Lector de las animaciones .ANI (bloques MAO), escrito a partir de FUN_8002f02c.

Un .ANI es una fila de animaciones. Cada una: "MAO\\0", uint16 pistas, uint16 cuadros, y por cada pista
tres int16 (cabecera) y cuadros*3 bytes.

Uso: python ani.py SABRINA        resume el archivo y comprueba que se lee hasta el ultimo byte
"""
import os
import struct
import sys

RAIZ = r"C:\Proyectos\SABRINA"


def leer_ani(nombre):
    d = open(os.path.join(RAIZ, "extraido", "ANIMS", nombre.upper() + ".ANI"), "rb").read()
    p = 0
    anims = []
    while p < len(d):
        if d[p:p + 4] != b"MAO\0":
            raise ValueError(f"se esperaba MAO en {p:#x}, hay {d[p:p + 4]!r}")
        pistas, cuadros = struct.unpack_from("<HH", d, p + 4)
        p += 8
        lista = []
        for _ in range(pistas):
            a, b, c = struct.unpack_from("<3h", d, p)
            p += 6
            datos = d[p:p + cuadros * 3]
            p += cuadros * 3
            lista.append(dict(cab=(a, b, c), datos=datos))
        anims.append(dict(cuadros=cuadros, pistas=lista))
    return anims, len(d) - p


if __name__ == "__main__":
    anims, sobra = leer_ani(sys.argv[1])
    print(f"{len(anims)} animaciones, sobran {sobra} bytes")
    for i, a in enumerate(anims[:6]):
        print(f"  animacion {i}: {len(a['pistas'])} pistas, {a['cuadros']} cuadros")
    a = anims[0]
    for k, t in enumerate(a["pistas"][:45]):
        tri = [tuple(t["datos"][f * 3:f * 3 + 3]) for f in range(min(4, a["cuadros"]))]
        print(f"    pista {k:2d} cab {t['cab']}  primeros cuadros {tri}")
