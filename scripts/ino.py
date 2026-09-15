"""Lector de los .INO (mundo y modelos de cada nivel), escrito a partir del cargador del juego.

Orden del archivo, tal como lo lee FUN_80018670:
 1. FUN_8001d230  cuadricula: int16 A, int16 B, int16 ancho, int16 alto, int32 C; A*12, B*8, C*2 bytes
 2. FUN_80024328  uint16 n; n*32 bytes
 3. FUN_8001ce0c  int16 ntex; ntex*32 (texturas); 0xDC bytes (tabla de 110 int16); luego un arbol de
                  nodos por cada modelo de la lista del nivel (punteros en 0x8007C244 + 4*nivel)
 4. FUN_80018c14  uint16 n; n*12 bytes
 5. FUN_8001f4a8  uint16 n; n*32 bytes (particulas, Particle.c)
Nodo de modelo (FUN_8001c7d4): int16 nvert (negativo = fin de la lista de hermanos), int16 ntri,
int16 nhijos, 32 bytes de MATRIX (int16 m[3][3], 2 de relleno, int32 t[3]), int16 largo del nombre y el
nombre, los hijos (uno por uno), ntri triangulos de 28 bytes (int32 v0 v1 v2, int32 textura, u0 v0 u1 v1
u2 v2, 6 bytes mas) y nvert vertices de 12 bytes.

Uso: python ino.py H1W        resume el archivo y comprueba que se lee hasta el ultimo byte
"""
import os
import struct
import sys

RAIZ = r"C:\Proyectos\SABRINA"
EXE = open(os.path.join(RAIZ, r"extraido\SLUS_012.08"), "rb").read()
NIVELES = ["FRW", "S1W", "S2W", "S3W", "E1W", "E2W", "E3W", "J1W", "J2W", "J3W", "W1W", "W2W", "W3W", "H1W", "C1W"]
CARPETA = {"FR": "FRONT", "H1": "HUB", "C1": "CHAOS", "S": "STONE", "E": "EGYPT", "J": "JAPAN", "W": "WEST"}


def _u32(direccion):
    return struct.unpack_from("<I", EXE, direccion - 0x80010000 + 0x800)[0]


def _cadena(direccion):
    o = direccion - 0x80010000 + 0x800
    return EXE[o:EXE.index(b"\0", o)].decode("ascii", "replace")


def modelos_del_nivel(nivel):
    """Nombres de los modelos que el juego espera en el .INO de ese nivel, en orden."""
    lista = _u32(0x8007C244 + 4 * nivel)
    res = []
    while True:
        p = _u32(lista + 4 * len(res))
        if p == 0:
            return res
        res.append(_cadena(p) if 0x80010000 <= p < 0x80080000 else f"{p:08x}")


class Lector:
    def __init__(self, d):
        self.d, self.p = d, 0

    def leer(self, n):
        b = self.d[self.p:self.p + n]
        if len(b) != n:
            raise ValueError(f"fin de archivo en {self.p:#x} pidiendo {n}")
        self.p += n
        return b

    def h(self):
        return struct.unpack("<h", self.leer(2))[0]

    def H(self):
        return struct.unpack("<H", self.leer(2))[0]

    def i(self):
        return struct.unpack("<i", self.leer(4))[0]


def leer_nodo(r):
    nvert = r.h()
    if nvert < 0:
        return None
    ntri, nhijos = r.h(), r.h()
    m = struct.unpack("<9h2x3i", r.leer(32))
    nombre = r.leer(r.h()).decode("ascii", "replace")
    hijos = [leer_nodo(r) for _ in range(nhijos)]
    tris = [struct.unpack("<4i6B6B", r.leer(28)) for _ in range(ntri)]
    verts = [r.leer(12) for _ in range(nvert)]
    return dict(nombre=nombre, matriz=m[:9], tras=m[9:], hijos=hijos, tris=tris, verts=verts)


def leer_ino(nombre):
    carpeta = CARPETA.get(nombre[:2]) or CARPETA[nombre[0]]
    d = open(os.path.join(RAIZ, "extraido", "GRAPHICS", carpeta, nombre + ".INO"), "rb").read()
    r = Lector(d)
    s = {}
    a, b, ancho, alto, c = struct.unpack("<4hi", r.leer(12))
    s["cuadricula"] = dict(A=a, B=b, ancho=ancho, alto=alto, C=c, celdas=r.leer(a * 12), listas=r.leer(b * 8),
                           indices=r.leer(c * 2))
    n = r.H()
    s["sec2"] = [r.leer(32) for _ in range(n)]
    ntex = r.h()
    s["texturas"] = [r.leer(32) for _ in range(ntex)]
    s["tabla"] = r.leer(0xDC)
    s["modelos"] = []
    for nom in modelos_del_nivel(NIVELES.index(nombre)):
        hermanos = []
        while True:
            nodo = leer_nodo(r)
            if nodo is None:
                break
            hermanos.append(nodo)
        s["modelos"].append((nom, hermanos))
    n = r.H()
    s["sec6"] = [r.leer(12) for _ in range(n)]
    n = r.H()
    s["particulas"] = [r.leer(32) for _ in range(n)]
    s["sobra"] = len(d) - r.p
    s["tamano"] = len(d)
    return s


def contar(nodos):
    t = v = n = 0
    for nd in nodos:
        a, b, c = contar(nd["hijos"])
        t, v, n = t + len(nd["tris"]) + a, v + len(nd["verts"]) + b, n + 1 + c
    return t, v, n


if __name__ == "__main__":
    s = leer_ino(sys.argv[1])
    g = s["cuadricula"]
    print(f"{sys.argv[1]}.INO {s['tamano']} bytes, sobran {s['sobra']}")
    print(f"  cuadricula {g['ancho']}x{g['alto']}, A {g['A']} B {g['B']} C {g['C']}")
    print(f"  seccion 2: {len(s['sec2'])} registros, texturas {len(s['texturas'])}")
    for nom, hermanos in s["modelos"]:
        t, v, n = contar(hermanos)
        print(f"  modelo {nom}: {n} nodos, {t} triangulos, {v} vertices"
              + (f", primer nodo '{hermanos[0]['nombre']}'" if hermanos else ""))
    print(f"  seccion 6: {len(s['sec6'])}, particulas {len(s['particulas'])}")
