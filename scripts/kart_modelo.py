"""El carrito de SABRINA KART: reemplaza la mitad de abajo de Sabrina (el modelo SABdefault del HUB) por un kart.

Sabrina son dos modelos (ver notas/FORMATOS.md): SABdefault, de la cadera para abajo (Hips con LegR/L, ShinR/L y
FootR/L), y SABdefault1, de la cadera para arriba. Aqui se vacian las piernas, las espinillas y los pies (los nodos
se quedan, sin triangulos, porque las animaciones mueven un hueso por nodo) y en la cadera va el kart: chasis,
cabina, asiento, morro, parachoques, tablero con volante, aleron, escapes y cuatro ruedas. El torso (el otro
modelo) sale de la cabina.

Ejes de la cadera: x a los lados, y hacia delante (hacia donde apuntan los pies), z hacia arriba; la cadera esta a
212 del suelo y el pecho empieza 14 por encima de ella. Los colores son lisos: cada triangulo muestrea un solo texel
casi gris (el mismo truco que el cielo, TEX_CIELO) y el color lo pone el vertice.

Uso: python kart_modelo.py      escribe notas/capturas/kart_modelo.obj para mirarlo y dice cuantos triangulos son
"""
import math
import os
import struct

import nivel_plataformas as n

SUELO = -212                     # el suelo, en coordenadas de la cadera
ROSA, MORADO, ORO = (235, 80, 170), (110, 45, 150), (235, 190, 60)
NEGRO, GRIS, CREMA = (28, 26, 32), (150, 150, 165), (240, 225, 200)


class Malla:
    def __init__(self, transformar=None):
        """transformar(p) -> p: para armar en otros ejes (el rival va en los del mundo)."""
        self.verts, self.tris = [], []
        self.t = transformar or (lambda p: p)

    def _v(self, p, color):
        c = [min(255, round(color[k] * 128 / n.TEXEL_CIELO[k])) for k in range(3)]
        self.verts.append(struct.pack("<3hh3Bx", *[round(q) for q in p], 0, *c))
        return len(self.verts) - 1

    def _cara(self, idx, pos, centro):
        """Un triangulo mirando hacia fuera del solido (centro dentro de el)."""
        p0, p1, p2 = (pos[i] for i in idx)
        u = [p1[k] - p0[k] for k in range(3)]
        v = [p2[k] - p0[k] for k in range(3)]
        nn = [u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0]]
        m = [(p0[k] + p1[k] + p2[k]) / 3 - centro[k] for k in range(3)]
        if sum(nn[k] * m[k] for k in range(3)) < 0:
            idx = (idx[0], idx[2], idx[1])
            nn = [-q for q in nn]
        lon = math.sqrt(sum(q * q for q in nn)) or 1
        nb = [round(q / lon * 127) & 0xFF for q in nn]
        uv = n.UV_CIELO * 3
        self.tris.append(tuple(idx) + (n.TEX_CIELO,) + tuple(uv) + (1, 0, *nb, 4))

    def solido(self, puntos, caras, color):
        """puntos: vertices; caras: listas de indices (convexas, se abren en abanico)."""
        puntos = [self.t(p) for p in puntos]
        base = [self._v(p, color) for p in puntos]
        pos = {base[i]: puntos[i] for i in range(len(puntos))}
        centro = [sum(p[k] for p in puntos) / len(puntos) for k in range(3)]
        for c in caras:
            for j in range(1, len(c) - 1):
                self._cara((base[c[0]], base[c[j]], base[c[j + 1]]), pos, centro)

    def caja(self, x0, x1, y0, y1, z0, z1, color):
        pts = [(x, y, z) for z in (z0, z1) for y in (y0, y1) for x in (x0, x1)]
        caras = [(0, 1, 3, 2), (4, 5, 7, 6), (0, 1, 5, 4), (2, 3, 7, 6), (0, 2, 6, 4), (1, 3, 7, 5)]
        self.solido(pts, caras, color)

    def rueda(self, cx, cy, cz, r, ancho, color, lados=8):
        """Un prisma de 'lados' caras con el eje en x."""
        pts = []
        for x in (cx - ancho / 2, cx + ancho / 2):
            for i in range(lados):
                a = 2 * math.pi * (i + 0.5) / lados
                pts.append((x, cy + r * math.cos(a), cz + r * math.sin(a)))
        caras = [list(range(lados)), list(range(lados, 2 * lados))]
        caras += [(i, (i + 1) % lados, lados + (i + 1) % lados, lados + i) for i in range(lados)]
        self.solido(pts, caras, color)


def kart(m=None, cuerpo=ROSA, chasis=MORADO, adorno=ORO, simple=False):
    """El kart en ejes de la cadera. Ruedas de 6 lados, sin tapacubos: el .INO tiene tamano fijo. simple: sin
    volante, soportes ni escapes (el del rival, que se ve de lejos)."""
    m = m or Malla()
    m.caja(-64, 64, -125, 135, -186, -158, chasis)          # chasis
    m.caja(-72, -54, -112, 70, -158, 4, cuerpo)             # lados de la cabina
    m.caja(54, 72, -112, 70, -158, 4, cuerpo)
    m.caja(-54, 54, -118, -88, -158, -8, cuerpo)            # respaldo (bajo: se ve la espalda de quien maneja)
    m.caja(-50, 50, -88, 40, -158, 8, chasis)               # asiento (tapa el hueco hasta el pecho)
    m.caja(-54, 54, 70, 112, -158, -6, chasis)              # tablero
    m.caja(-50, 50, 112, 200, -184, -112, cuerpo)           # morro
    m.caja(-68, 68, 200, 216, -192, -160, adorno)           # parachoques
    if not simple:
        m.caja(-5, 5, 40, 70, -20, 14, GRIS)                # columna del volante
        m.caja(-26, 26, 34, 42, -6, 30, NEGRO)              # volante
        m.caja(-46, -34, -150, -124, -158, -40, GRIS)       # soportes del aleron
        m.caja(34, 46, -150, -124, -158, -40, GRIS)
        m.caja(-38, -20, -152, -125, -176, -160, GRIS)      # escapes
        m.caja(20, 38, -152, -125, -176, -160, GRIS)
    m.caja(-84, 84, -178, -128, -40, -26, adorno)           # aleron (bajo y atras)
    r = 40
    for y in (-82, 122):
        for lado in (-1, 1):
            m.rueda(lado * 92, y, SUELO + r, r, 30, NEGRO, lados=6)
    return m


VERDE, VERDE_OSCURO, PLATA = (60, 175, 90), (25, 70, 40), (200, 205, 215)
PELO, AMARILLO, ROSITA = (40, 34, 46), (250, 225, 40), (230, 140, 160)


def salem(m):
    """Salem, el gato negro de Sabrina, sentado en el asiento (bloques, en ejes de la cadera)."""
    m.caja(-30, 30, -60, 20, -20, 70, PELO)                 # cuerpo
    m.caja(-34, 34, -30, 40, 70, 136, PELO)                 # cabeza
    m.caja(-30, -12, -10, 14, 136, 170, PELO)               # orejas
    m.caja(12, 30, -10, 14, 136, 170, PELO)
    m.caja(-22, -8, 40, 44, 100, 114, AMARILLO)             # ojos
    m.caja(8, 22, 40, 44, 100, 114, AMARILLO)
    m.caja(-24, -10, 10, 40, 30, 46, PELO)                  # patas al volante
    m.caja(10, 24, 10, 40, 30, 46, PELO)
    m.caja(-6, 6, -150, -60, 20, 34, PELO)                  # cola, hacia atras y arriba
    m.caja(-6, 6, -162, -148, 20, 130, PELO)


def rival(nodo_original):
    """Para construir_bytes(reemplazos={17: rival}): el modelo de FashionDiva (no sale en la pista) es el kart verde
    de Salem. Va armado igual que la mitad de abajo de Sabrina (la raiz con la matriz de SABdefault y una cadera hija
    a 212 del suelo con la malla en ejes de cadera), porque kart.inc lo pone en su sitio igual que el juego a Sabrina:
    MatrizDesdeAngulos con la escala de ella. Con la malla en ejes del mundo salia de punta."""
    import ino
    raiz_sab = ino.leer_ino("H1W")["modelos"][1][1][0]
    cadera_sab = raiz_sab["hijos"][0]
    m = Malla()
    kart(m, cuerpo=VERDE, chasis=VERDE_OSCURO, adorno=PLATA, simple=True)
    salem(m)
    cadera = dict(cadera_sab, nombre="RIVALkart\0", hijos=[], tris=m.tris, verts=m.verts)
    return dict(raiz_sab, nombre=nodo_original["nombre"], hijos=[cadera], tris=[], verts=[])


def vacio(nodo_original):
    """El modelo 11 del HUB es una segunda copia de SABdefault que nadie dibuja en el kart (probado con capturas): se
    vacia y deja sitio en el .INO para el decorado. Los nodos se quedan, sin triangulos."""
    def vaciar(nodo):
        return dict(nodo, tris=[], verts=[], hijos=[vaciar(h) for h in nodo["hijos"]])
    return vaciar(nodo_original)


def armar(nodo_original):
    """Para nivel_fantasma.construir_bytes(reemplazos={1: armar}): el arbol de SABdefault con el kart."""
    raiz = dict(nodo_original)
    caderas = dict(raiz["hijos"][0])

    def vaciar(nodo):
        return dict(nodo, tris=[], verts=[], hijos=[vaciar(h) for h in nodo["hijos"]])
    m = kart()
    caderas.update(tris=m.tris, verts=m.verts, hijos=[vaciar(h) for h in caderas["hijos"]])
    raiz["hijos"] = [caderas] + raiz["hijos"][1:]
    return raiz


if __name__ == "__main__":
    m = kart()
    print(len(m.verts), "vertices,", len(m.tris), "triangulos")
    ruta = os.path.join(n.disco.RAIZ, "notas", "capturas", "kart_modelo.obj")
    with open(ruta, "w", encoding="utf-8") as f:
        for v in m.verts:
            x, y, z = struct.unpack_from("<3h", v)
            f.write(f"v {x} {z} {-y}\n")
        for t in m.tris:
            f.write(f"f {t[0] + 1} {t[1] + 1} {t[2] + 1}\n")
    print("escrito", ruta)
