"""Los monstruos y objetos del especial de Halloween (mapa_halloween.py, halloween.inc), hechos con bloques.

Van en modelos del HUB que en el castillo no salen (los engranajes, FashionDiva, el ropero, los trajes), armados como
la mitad de abajo de Sabrina (kart_modelo.como_sabrina: ejes de cadera, x a los lados, y hacia delante, z arriba, el
suelo en z = -212) porque halloween.inc los pone con MatrizDesdeAngulos igual que el kart al rival. El juego los
tiene en modelos_cargados uno corrido: el modelo n de la lista es modelos_cargados[n + 1].

  13 fantasma     14 murcielago     15 calabaza (la que se junta y la saltarina)     16 manzana encantada
  17 Rey Calabaza 18 portal         20 cristal magico (el de Sabrina)                21 bola de fuego del jefe
  22 luna
"""
import math

import kart_modelo as km
from kart_modelo import Malla, SUELO

BLANCO_FANTASMA, NEGRO, ROJO_OJO = (215, 225, 245), (15, 12, 20), (255, 40, 40)
NARANJA, NARANJA_OSCURO, VERDE_TALLO = (255, 130, 20), (200, 80, 10), (60, 130, 40)
AMARILLO_LUZ, MORADO_CAPA, ORO = (255, 230, 80), (70, 30, 90), (240, 200, 70)


def tronco(m, r0, r1, z0, z1, color, lados=6, cy=0):
    """Un tronco de cono de pie (eje z): radio r0 abajo y r1 arriba (r1 = 0, una punta)."""
    ab = [(r0 * math.cos(2 * math.pi * (i + 0.5) / lados), cy + r0 * math.sin(2 * math.pi * (i + 0.5) / lados), z0)
          for i in range(lados)]
    if r1 == 0:
        m.solido(ab + [(0, cy, z1)], [list(range(lados))] + [(i, (i + 1) % lados, lados) for i in range(lados)], color)
        return
    ar = [(r1 * math.cos(2 * math.pi * (i + 0.5) / lados), cy + r1 * math.sin(2 * math.pi * (i + 0.5) / lados), z1)
          for i in range(lados)]
    caras = [list(range(lados)), list(range(lados, 2 * lados))]
    caras += [(i, (i + 1) % lados, lados + (i + 1) % lados, lados + i) for i in range(lados)]
    m.solido(ab + ar, caras, color)


def cara_calabaza(m, r, z0, z1, ojos=NEGRO, dientes=False):
    """Los ojos y la boca de una calabaza de radio r (en su cara de delante, +y)."""
    h = z1 - z0
    y = r * 0.95
    m.caja(-r * 0.55, -r * 0.18, y - 8, y + 8, z0 + h * 0.55, z0 + h * 0.8, ojos)
    m.caja(r * 0.18, r * 0.55, y - 8, y + 8, z0 + h * 0.55, z0 + h * 0.8, ojos)
    m.caja(-r * 0.6, r * 0.6, y - 8, y + 8, z0 + h * 0.2, z0 + h * 0.38, NEGRO if not dientes else ojos)


def fantasma(nodo):
    m = Malla()
    s = SUELO + 90                                  # flota: la sabana no toca el suelo
    tronco(m, 115, 80, s, s + 210, BLANCO_FANTASMA)
    tronco(m, 80, 30, s + 210, s + 300, BLANCO_FANTASMA)
    m.caja(-42, -14, 66, 76, s + 200, s + 250, NEGRO)          # ojos
    m.caja(14, 42, 66, 76, s + 200, s + 250, NEGRO)
    m.caja(-22, 22, 74, 84, s + 120, s + 175, NEGRO)          # la boca abierta: "buuu"
    m.caja(-170, -70, -20, 20, s + 130, s + 165, BLANCO_FANTASMA)   # brazos
    m.caja(70, 170, -20, 20, s + 130, s + 165, BLANCO_FANTASMA)
    return km.como_sabrina(nodo, m, "FANTASMA")


def murcielago(nodo):
    m = Malla()
    s = SUELO
    m.caja(-36, 36, -40, 40, s - 30, s + 40, NEGRO)            # cuerpo y cabeza
    km.piramide(m, (-20, -10, s + 40), (-24, -10, s + 90), 13, NEGRO)    # orejas
    km.piramide(m, (20, -10, s + 40), (24, -10, s + 90), 13, NEGRO)
    m.caja(-200, -36, -30, 30, s + 10, s + 22, (40, 30, 50))  # alas
    m.caja(36, 200, -30, 30, s + 10, s + 22, (40, 30, 50))
    m.caja(-24, -8, 38, 46, s + 12, s + 26, ROJO_OJO)         # ojos rojos
    m.caja(8, 24, 38, 46, s + 12, s + 26, ROJO_OJO)
    return km.como_sabrina(nodo, m, "MURCIELAGO")


def calabaza(nodo):
    m = Malla()
    s = SUELO
    tronco(m, 95, 110, s, s + 70, NARANJA_OSCURO, lados=8)
    tronco(m, 110, 70, s + 70, s + 150, NARANJA, lados=8)
    m.caja(-12, 12, -12, 12, s + 150, s + 195, VERDE_TALLO)   # el tallo
    cara_calabaza(m, 104, s + 20, s + 140, ojos=AMARILLO_LUZ, dientes=True)
    return km.como_sabrina(nodo, m, "CALABAZA")


def manzana(nodo):
    m = Malla()
    s = SUELO
    tronco(m, 55, 75, s, s + 55, (200, 20, 40))
    tronco(m, 75, 45, s + 55, s + 120, (230, 30, 50))
    m.caja(-6, 6, -6, 6, s + 120, s + 160, (90, 60, 30))      # rabito
    m.caja(6, 50, -4, 4, s + 140, s + 160, (60, 170, 60))     # hoja
    return km.como_sabrina(nodo, m, "MANZANA")


def rey_calabaza(nodo):
    """El jefe: una calabaza enorme con ojos de fuego, corona dorada y una capa morada que flota debajo."""
    m = Malla()
    s = SUELO + 60
    tronco(m, 60, 200, s, s + 220, MORADO_CAPA)               # la capa (de punta abajo)
    tronco(m, 230, 270, s + 220, s + 330, NARANJA_OSCURO, lados=8)
    tronco(m, 270, 170, s + 330, s + 500, NARANJA, lados=8)
    cara_calabaza(m, 262, s + 250, s + 480, ojos=AMARILLO_LUZ, dientes=True)
    tronco(m, 150, 150, s + 500, s + 570, ORO)                # la corona
    for a in (0, 2.1, 4.2):
        km.piramide(m, (150 * math.cos(a), 150 * math.sin(a), s + 570), (150 * math.cos(a), 150 * math.sin(a), s + 660),
                    30, ORO)
    return km.como_sabrina(nodo, m, "REYcalabaza")


def portal(nodo):
    """Dos laminas cruzadas con el remolino azul del juego sobre una base dorada (halloween.inc lo hace girar)."""
    m = Malla()
    s = SUELO
    tronco(m, 200, 170, s, s + 50, ORO)
    for ancho_x in (True, False):
        if ancho_x:
            m.caja_textura(-170, 170, -10, 10, s + 50, s + 470, 101, [(200, 200, 255)] * 6)
        else:
            m.caja_textura(-10, 10, -170, 170, s + 50, s + 470, 101, [(200, 200, 255)] * 6)
    return km.como_sabrina(nodo, m, "PORTAL")


def bola_fuego(nodo):
    m = Malla()
    pts = lambda r: [(0, 0, r), (0, 0, -r), (r, 0, 0), (-r, 0, 0), (0, r, 0), (0, -r, 0)]
    caras = [(0, 2, 4), (0, 4, 3), (0, 3, 5), (0, 5, 2), (1, 4, 2), (1, 3, 4), (1, 5, 3), (1, 2, 5)]
    m.solido(pts(70), caras, (255, 110, 20))
    return km.como_sabrina(nodo, m, "FUEGO")


def luna(nodo):
    """Una luna llena enorme: un disco de 8 lados de cara a +y (halloween.inc la pone siempre lejos, al norte)."""
    m = Malla()
    km.prisma(m, 700, -20, 20, (250, 240, 200), lados=8)
    return km.como_sabrina(nodo, m, "LUNA")


def reemplazos(cielo):
    """Para nivel_fantasma.construir_bytes: el cielo de noche, la copia sin uso de SABdefault vacia y los modelos."""
    import nivel_plataformas as n
    return {n.INDICE_CIELO: n.nodo_cielo(cielo), 11: km.vacio,
            13: fantasma, 14: murcielago, 15: calabaza, 16: manzana, 17: rey_calabaza, 18: portal,
            20: km.cristal, 21: bola_fuego, 22: luna}


if __name__ == "__main__":
    for f in (fantasma, murcielago, calabaza, manzana, rey_calabaza, portal, bola_fuego, luna, km.cristal):
        h = f({"nombre": "x"})["hijos"][0]
        print(f"{f.__name__:14s} {len(h['tris']):4d} triangulos {len(h['verts']):4d} vertices")
