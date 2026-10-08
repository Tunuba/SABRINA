"""Genera niveles\\castillo.json: un complejo con patio amurallado y estanque, puerta con dintel, camino, una fortaleza
con salon de columnas, habitaciones y puertas, y una muralla con rampas hasta una torre. Sirve de ejemplo de mapa de
verdad hecho con los bloques del motor (nivel_plataformas.py); se puede abrir y retocar en el editor.

Uso: python mapa_castillo.py        (escribe niveles\\castillo.json)

El .INO del disco tiene un tamano fijo (313.628 bytes): las paredes interiores y las columnas llevan cuadros de 256
(paso_lado), la fortaleza de 384 y el resto de 512; con todo a 384 ya no cabe (ver nivel_plataformas.tamano_ino).

Medidas (unidades del modelo; Sabrina aparece en (128, -896) y mide ~250; salta 380): todo en multiplos de 256. Las
alturas son positivas hacia arriba aqui y se pasan a h = -alto. La isla flota: los bloques bajan hasta 600 por
debajo del suelo (prof) para que el borde se vea como un acantilado.
"""
import os

import nivel_plataformas as n

ISLA = 600                      # cuanto baja el suelo de la isla
PIEDRA, LADRILLO, CLARA = (190, 180, 170), (215, 205, 195), (170, 170, 170)
AGUA, MARMOL, MADERA, TEJAS = (150, 205, 215), (180, 190, 230), (190, 170, 150), (200, 160, 140)
bloques = []


def suelo(nombre, x0, z0, x1, z1, h=0, **kw):
    """Un suelo: baja ISLA desde su tapa (acantilado de la isla) y lleva cuadros de 512."""
    kw.setdefault("prof", ISLA)
    kw.setdefault("paso", 512)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -h, **kw))


def muro(nombre, x0, z0, x1, z1, alto, hasta=0, **kw):
    """Un muro de 'alto' sobre la altura 'hasta' (por defecto el suelo, 0); baja hasta 'hasta'... y, si baja a la isla,
    prof se alarga con extra."""
    extra = kw.pop("extra", 0)
    kw.setdefault("color", PIEDRA)
    kw.setdefault("tex_tapa", 16)
    kw.setdefault("tex_lado", 1)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -(hasta + alto), pared=True, prof=alto + extra, **kw))


def rampa(nombre, x0, z0, x1, z1, h_ini, h_fin, eje, **kw):
    kw.setdefault("prof", 300)
    kw.setdefault("tex_tapa", 97)
    kw.setdefault("tex_lado", 16)
    kw.setdefault("color", MADERA)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -h_ini, h2=-h_fin, eje=eje, **kw))


# ------------------------------------------------------------------ patio con estanque (Sabrina aparece aqui)
c_patio = dict(color=CLARA, tex_tapa=67, tex_lado=1)
suelo("patio_o", -2048, -3072, 512, 1024, **c_patio)           # contiene la salida (128, -896)
suelo("patio_e", 1536, -3072, 3072, 1024, **c_patio)
suelo("patio_n", 512, -3072, 1536, -512, **c_patio)
suelo("patio_s", 512, 512, 1536, 1024, **c_patio)
suelo("estanque", 512, -512, 1536, 512, h=-256, color=AGUA, tex_tapa=66, tex_lado=66, prof=300)
bloques.append(n.nueva("estatua", 896, -128, 1152, 128, -300, color=MARMOL, tex_tapa=69, tex_lado=69,
                       prof=556, pared=True))

# ------------------------------------------------------------------ muralla del patio (la isla baja 700 + ISLA)
for nombre, x0, z0, x1, z1 in (("muralla_o", -2304, -3328, -2048, 1280), ("muralla_n", -2048, -3328, 3328, -3072),
                               ("muralla_s", -2048, 1024, 3328, 1280), ("muralla_e1", 3072, -3072, 3328, -1024),
                               ("muralla_e2", 3072, 0, 3328, 1024)):
    muro(nombre, x0, z0, x1, z1, 700, extra=ISLA, color=PIEDRA)
suelo("umbral", 3072, -1024, 3328, 0, color=CLARA, tex_tapa=98, tex_lado=1)           # la puerta
bloques.append(n.nueva("dintel", 3072, -1024, 3328, 0, -700, color=PIEDRA, tex_tapa=16, tex_lado=1, prof=250,
                       techo=True, pared=True))

# ------------------------------------------------------------------ camino hasta la fortaleza
suelo("camino", 3328, -1536, 6400, 512, color=CLARA, tex_tapa=98, tex_lado=1)
muro("camino_n", 3328, -1792, 6400, -1536, 500, extra=ISLA, color=PIEDRA)
muro("camino_s", 3328, 512, 6400, 768, 500, extra=ISLA, color=PIEDRA)

# ------------------------------------------------------------------ fortaleza: salon, columnas, habitaciones
suelo("salon", 6400, -3072, 10496, 2048, color=MADERA, tex_tapa=97, tex_lado=88)
ladrillo = dict(color=LADRILLO, tex_tapa=16, tex_lado=88)
for nombre, x0, z0, x1, z1 in (("fort_o1", 6400, -3072, 6656, -512), ("fort_o2", 6400, 256, 6656, 2048),   # la puerta: z -512..256
                               ("fort_e", 10240, -3072, 10496, 2048), ("fort_n", 6656, -3072, 10240, -2816),
                               ("fort_s", 6656, 1792, 10240, 2048)):
    muro(nombre, x0, z0, x1, z1, 1000, extra=ISLA, paso_lado=384, **ladrillo)
for nombre, x0, z0, x1, z1 in (("sala_n1", 6656, -1792, 8192, -1536), ("sala_n2", 8960, -1792, 10240, -1536),   # puerta x 8192..8960
                               ("sala_s1", 6656, 768, 7424, 1024), ("sala_s2", 8192, 768, 10240, 1024),     # puerta x 7424..8192
                               ("cuarto_n1", 8192, -2816, 8448, -2560), ("cuarto_n2", 8192, -2048, 8448, -1792),   # puerta z -2560..-2048
                               ("cuarto_s1", 8448, 1024, 8704, 1280), ("cuarto_s2", 8448, 1536, 8704, 1792)):     # puerta z 1280..1536
    muro(nombre, x0, z0, x1, z1, 1000, paso_lado=256, **ladrillo)       # lo que se ve de cerca: mas detalle
for nombre, x0, z0 in (("col1", 7168, -1280), ("col2", 9728, -1280), ("col3", 7168, -256), ("col4", 9728, -256)):
    muro(nombre, x0, z0, x0 + 256, z0 + 256, 1000, color=CLARA, tex_tapa=16, tex_lado=16, paso_lado=256)
bloques.append(n.nueva("tejado", 6400, -3072, 10496, 2048, -1100, color=TEJAS, tex_tapa=96, tex_lado=108, prof=100,
                       techo=True, paso=512, pared=True))

# ------------------------------------------------------------------ muralla del patio: paseo, rampas y torre
bloques.append(n.nueva("paseo", -2048, -3072, 3072, -2560, -500, color=CLARA, tex_tapa=98, tex_lado=1, prof=500,
                       paso=512, pared=True))
rampa("rampa_paseo", -1792, -2560, -1280, -1536, 0, 500, "z")      # del patio (z -1536) al paseo (z -2560)
rampa("rampa_torre", 1280, -3072, 2304, -2560, 500, 1100, "x")     # del paseo a lo alto de la torre
bloques.append(n.nueva("torre", 2304, -3072, 3072, -2304, -1100, color=PIEDRA, tex_tapa=16, tex_lado=1, prof=1100,
                       pared=True))

cielo = dict(cenit=[50, 60, 150], horizonte=[255, 200, 140], nadir=[40, 50, 110])

if __name__ == "__main__":
    errores, avisos = n.validar(bloques)
    print(len(bloques), "bloques; errores:", errores, "avisos:", avisos)
    if not errores:
        ruta = os.path.join(n.NIVELES, "castillo.json")
        n.guardar(bloques, ruta, cielo)
        print("escrito", ruta)
