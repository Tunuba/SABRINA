"""Genera niveles\\halloween.json y decomp\\src\\objetos\\halloween_mapa.h: SABRINA, NOCHE DE BRUJAS EN EL CASTILLO.

El especial de Halloween: un castillo embrujado de cuatro zonas, cada una como un mini nivel. Sabrina camina, corre
y salta como en el juego, junta las calabazas de cada zona (al juntarlas todas se abre el portal a la siguiente),
come manzanas encantadas para curarse y lanza cristales magicos (cuadrado) contra los monstruos. El codigo esta en
decomp/src/objetos/halloween.inc (SABRINA_HALLOWEEN) y los monstruos y objetos en scripts/halloween_modelos.py.

1. El cementerio de Greendale (donde aparece Sabrina): lapidas, la cripta con su tejado, arboles muertos y una reja
   de hierro alrededor. Salen fantasmas.
2. El gran salon del castillo: suelo de ajedrez, columnas, dos balcones con escaleras y candelabros dorados. Fantasmas,
   murcielagos y calabazas saltarinas.
3. La torre embrujada: plataformas que suben en espiral por dentro hasta lo alto (3000). Murcielagos.
4. La mazmorra del Rey Calabaza: columnas, braseros y el jefe.

Las zonas estan lejos una de otra (se pasa por los portales) pero se ven: desde el cementerio asoman el castillo y la
torre por encima de la reja. Los lados que nadie ve no se generan (sin_lados), como en mapa_kart.

Uso: python mapa_halloween.py      (escribe los dos archivos y dice cuanto ocupa el .INO con los modelos)
"""
import os

import nivel_plataformas as n

# texturas (galeria del editor, PALETA en nivel_plataformas)
PIEDRA, VETEADA, LISA, PIEDRA3, PIEDRA4, PIEDRA5 = 16, 1, 13, 67, 71, 98
MARMOL, AGUA, LADRILLO, TEJAS, TABLONES = 69, 66, 88, 96, 97
VALLA, HIERBA, ORO, AZULEJO, GLIFO = 100, 81, 77, 78, 79
PUERTA_ORO, MURAL, BANDA_ORO, OXIDO = 90, 75, 70, 89
TELA_ROJA, TELA_VERDE, REMOLINO = 106, 107, 101
PUERTA, PANELES, ARCO = 108, 110, 109

MURO = 450                       # con menos de ~370 Sabrina se sube sola
HONDO = 600                      # cuanto bajan los bloques por debajo del suelo
# colores de noche (128 = la textura tal cual)
TIERRA, LAPIDA, HIERRO = (70, 72, 58), (105, 105, 115), (60, 55, 70)
MADERA_MUERTA, PIEDRA_NOCHE, LADRILLO_NOCHE = (70, 55, 50), (85, 85, 100), (95, 70, 70)

bloques = []
zonas = []                       # por zona: salida (x, z, rumbo), calabazas, manzanas, fantasmas, murcielagos,
                                 # saltarinas [(x, y, z)], portal (x, y, z)


def suelo(nombre, x0, z0, x1, z1, h=0, **kw):
    kw.setdefault("prof", 300)
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 1024)
    kw.setdefault("tex_lado", PIEDRA)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, h, **kw))


def pared(nombre, x0, z0, x1, z1, alto=MURO, base=0, **kw):
    """Un bloque macizo de 'alto' sobre 'base' que baja hasta HONDO bajo el suelo (o 'extra')."""
    kw.setdefault("color", PIEDRA_NOCHE)
    kw.setdefault("tex_tapa", PIEDRA)
    kw.setdefault("tex_lado", PIEDRA)
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 1024)
    extra = kw.pop("extra", HONDO if base == 0 else 0)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -(base + alto), pared=True, prof=alto + extra, **kw))


def escalon(nombre, x0, z0, x1, z1, alto, **kw):
    """Algo que se pisa (no es pared): un escalon, una lapida, un balcon. Baja hasta el suelo."""
    kw.setdefault("color", PIEDRA_NOCHE)
    kw.setdefault("tex_tapa", PIEDRA)
    kw.setdefault("tex_lado", PIEDRA)
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 512)
    kw.setdefault("prof", alto + 100)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -alto, **kw))


def losa(nombre, x0, z0, x1, z1, alto, grueso=120, **kw):
    """Una losa que flota a 'alto' (se pisa por arriba y se ve por abajo)."""
    kw.setdefault("color", PIEDRA_NOCHE)
    kw.setdefault("tex_tapa", PIEDRA)
    kw.setdefault("tex_lado", PIEDRA)
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 512)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -alto, prof=grueso, techo=True, **kw))


def recinto(nombre, x0, z0, x1, z1, alto, grueso=256, **kw):
    """Cuatro muros alrededor del rectangulo (por fuera de el)."""
    pared(nombre + "_n", x0 - grueso, z0 - grueso, x1 + grueso, z0, alto, **kw)
    pared(nombre + "_s", x0 - grueso, z1, x1 + grueso, z1 + grueso, alto, **kw)
    pared(nombre + "_o", x0 - grueso, z0, x0, z1, alto, **kw)
    pared(nombre + "_e", x1, z0, x1 + grueso, z1, alto, **kw)


def zona(nombre, salida, calabazas, manzanas, fantasmas=(), murcielagos=(), saltarinas=(), esqueletos=(), dulces=(),
         farolas=(), velas=(), sustos=(), portal=None, lema=""):
    """salida: donde aparece Sabrina al entrar (x, z, rumbo). No puede caer en una arista de los triangulos del suelo
    (multiplos de 256 y sus diagonales) o Sabrina se cae a traves: por eso las salidas van corridas (+37, +53).
    Las posiciones van (x, y, z) con y hacia abajo (0 = el suelo, -500 = sobre un balcon de 500). farolas y velas son
    decorado (calabazas encendidas y velas). sustos: (x0, z0, x1, z1, tipo, cual): al entrar Sabrina en el rectangulo
    pasa una vez: 1 sale de golpe el fantasma 'cual' delante de ella, 2 salen los murcielagos de la chimenea y se
    levanta el esqueleto 'cual', 3 cae del techo la calabaza saltarina 'cual'. Los monstruos de un susto esperan
    dormidos hasta entonces. En la ultima zona los fantasmas duermen hasta que el Rey Calabaza los llama."""
    zonas.append(dict(nombre=nombre, lema=lema, salida=salida, calabazas=list(calabazas), manzanas=list(manzanas),
                      fantasmas=list(fantasmas), murcielagos=list(murcielagos), saltarinas=list(saltarinas),
                      esqueletos=list(esqueletos), dulces=list(dulces), farolas=list(farolas), velas=list(velas),
                      sustos=list(sustos), portal=portal))


# ==================================================================== 1. el cementerio de Greendale
Z1 = (-2048, -3584, 3072, 1536)
suelo("cementerio", *Z1, color=TIERRA, tex_tapa=HIERBA)
recinto("reja", *Z1, MURO, color=HIERRO, tex_tapa=OXIDO, tex_lado=VALLA)
# lapidas en filas, con un camino por el centro (se pueden pisar: son escalones de 300)
for i, z in enumerate((-2304, -1280, 512)):
    for j, x in enumerate((-1536, -896, 1024, 1664)):
        escalon(f"lapida{i}{j}", x, z, x + 256, z + 256, 300 if (i + j) % 2 else 220, color=LAPIDA, tex_tapa=PIEDRA,
                tex_lado=VETEADA)
# la cripta: muros, tejado de dos aguas (dos losas escalonadas) y dos columnas delante de la puerta
pared("cripta", 1536, -3328, 2560, -2560, 560, color=(90, 90, 105), tex_tapa=PIEDRA, tex_lado=VETEADA)
pared("cripta_tejado", 1408, -3456, 2688, -2432, 160, base=560, color=(70, 55, 65), tex_tapa=TEJAS, tex_lado=TEJAS)
pared("cripta_punta", 1792, -3456, 2304, -2432, 160, base=720, color=(70, 55, 65), tex_tapa=TEJAS, tex_lado=TEJAS)
for x in (1536, 2304):
    pared(f"cripta_col{x}", x, -2560, x + 256, -2304, 560, color=(110, 110, 125), tex_tapa=MARMOL, tex_lado=MARMOL)
pared("cripta_puerta", 1792, -2560, 2304, -2304, 420, color=(40, 30, 35), tex_tapa=PIEDRA, tex_lado=PUERTA)
# arboles muertos: tronco y dos ramas
for i, (x, z) in enumerate(((-1792, 1024), (2560, 1024), (-1792, -3328), (2816, -1280))):
    pared(f"arbol{i}", x, z, x + 256, z + 256, 1000, color=MADERA_MUERTA, tex_tapa=TABLONES, tex_lado=TABLONES)
    losa(f"arbol{i}_rama", x - 384, z, x + 640, z + 256, 760, 100, color=MADERA_MUERTA, tex_tapa=TABLONES,
         tex_lado=TABLONES)
zona("EL CEMENTERIO DE GREENDALE", (128, -896, 0x800),
     calabazas=[(-1536, 0, -3200), (2048, -720, -2944), (-1152, 0, 768), (1792, 0, 1024), (-512, 0, -1792),
                (2432, 0, -1792)],
     manzanas=[(512, 0, 1024), (-1792, 0, -768)],
     fantasmas=[(-1408, 0, -2048), (2304, 0, -1024), (-1024, 0, 1280)],
     dulces=[(128, 0, -1536), (128, 0, -2304), (640, 0, -640), (-384, 0, 256), (1280, 0, -128), (2688, 0, 0)],
     farolas=[(-1536, -300, -2304), (1664, -300, -2304), (-896, -300, -1280), (1024, -300, 512), (1536, -560, -2944),
              (-896, -220, 512)],
     velas=[(1600, 0, -2176), (2240, 0, -2176)],
     portal=(512, 0, -3200), lema="LOS FANTASMAS SALEN DE SUS TUMBAS...")

# ==================================================================== 2. la casa del terror
# Una casa embrujada con techo: vestibulo, biblioteca, comedor y dormitorio, con puertas entre ellos; muebles; y tres
# sustos (el fantasma de la biblioteca, la calabaza que cae en el comedor, los murcielagos de la chimenea y el
# esqueleto del ataud en el dormitorio).
ZC = (-1024, 4608, 3072, 7680)
PAPEL, MADERA_CASA = (95, 45, 55), (85, 60, 45)
suelo("casa_suelo", *ZC, color=MADERA_CASA, tex_tapa=TABLONES)
recinto("casa", *ZC, 900, color=PAPEL, tex_tapa=PIEDRA, tex_lado=PANELES)
pared("casa_tabique_v1", 1024, 4608, 1280, 5888, 900, color=PAPEL, tex_lado=PANELES)
pared("casa_tabique_v2", 1024, 6400, 1280, 7680, 900, color=PAPEL, tex_lado=PANELES)
pared("casa_tabique_h1", -1024, 6144, -256, 6400, 900, color=PAPEL, tex_lado=PANELES)
pared("casa_tabique_h2", 256, 6144, 1024, 6400, 900, color=PAPEL, tex_lado=PANELES)
pared("casa_tabique_h3", 1280, 6144, 2048, 6400, 900, color=PAPEL, tex_lado=PANELES)
pared("casa_tabique_h4", 2560, 6144, 3072, 6400, 900, color=PAPEL, tex_lado=PANELES)
losa("casa_techo", *ZC, 1000, 100, color=(50, 35, 40), tex_tapa=TEJAS,
     tex_lado=PANELES)
# vestibulo: el reloj de pie
pared("reloj_pie", -1024, 4608, -768, 4864, 700, color=(110, 80, 40), tex_tapa=TABLONES, tex_lado=PUERTA_ORO)
# biblioteca: estanterias contra la pared y la mesa de lectura
pared("estanteria", 1536, 4608, 2816, 4864, 700, color=(90, 60, 40), tex_tapa=TABLONES, tex_lado=PANELES)
escalon("mesa_lectura", 2048, 5376, 2560, 5632, 200, color=(100, 70, 45), tex_tapa=TABLONES, tex_lado=TABLONES)
# comedor: la mesa larga
escalon("mesa_comedor", -640, 6784, 640, 7168, 220, color=(90, 55, 40), tex_tapa=TABLONES, tex_lado=TABLONES)
# dormitorio: la cama, el ataud y la chimenea con sus brasas
escalon("cama", 2304, 6912, 2944, 7552, 180, color=(130, 35, 45), tex_tapa=TELA_ROJA, tex_lado=TABLONES)
escalon("ataud", 1408, 7168, 1664, 7680, 160, color=(45, 30, 30), tex_tapa=TABLONES, tex_lado=PUERTA)
pared("chimenea", 2816, 6400, 3072, 6912, 620, color=(100, 60, 55), tex_tapa=PIEDRA, tex_lado=LADRILLO)
escalon("brasas", 2560, 6528, 2816, 6784, 90, color=(255, 110, 20), tex_tapa=TELA_ROJA, tex_lado=ORO)
zona("LA CASA DEL TERROR", (-512 + 37, 5376 + 53, 0x400),
     calabazas=[(2560, 0, 5888), (0, -220, 6976), (2624, -180, 7232), (-768, 0, 4864), (1856, 0, 7424)],
     manzanas=[(512, 0, 7424), (1536, 0, 4992)],
     fantasmas=[(2304, 0, 5120), (-640, 0, 7360)],
     murcielagos=[(2688, -500, 6656), (2560, -600, 6912), (2816, -450, 7168)],
     saltarinas=[(0, 0, 6528)],
     esqueletos=[(1536, 0, 7424), (-768, 0, 6912)],
     dulces=[(0, 0, 5376), (512, 0, 5376), (1152, 0, 6144), (2304, 0, 6272), (-512, 0, 6656), (768, 0, 7040)],
     farolas=[(-896, 0, 5888), (2944, -620, 6528)],
     velas=[(-384, -220, 6976), (384, -220, 6976), (2304, -200, 5504), (-896, -700, 4736)],
     sustos=[(1408, 4736, 2944, 6016, 1, 0), (-896, 6528, 896, 7552, 3, 0), (1408, 6528, 2944, 7552, 2, 0)],
     portal=(1984, 0, 6976), lema="NO MIRES DEBAJO DE LA CAMA...")

# ==================================================================== 2. el gran salon del castillo
Z2 = (6144, -3584, 11264, 1536)
for i in range(5):
    for j in range(5):
        x0, z0 = Z2[0] + 1024 * i, Z2[1] + 1024 * j
        claro = (i + j) % 2 == 0
        suelo(f"ajedrez{i}{j}", x0, z0, x0 + 1024, z0 + 1024, color=(150, 145, 160) if claro else (55, 50, 65),
              tex_tapa=MARMOL if claro else LISA)
recinto("castillo", *Z2, 1000, color=LADRILLO_NOCHE, tex_tapa=PIEDRA, tex_lado=LADRILLO)
for k, (x, z) in enumerate(((7168, -2048), (10240, -2048), (7168, 0), (10240, 0))):
    pared(f"columna{k}", x, z, x + 384, z + 384, 1000, color=(120, 115, 135), tex_tapa=MARMOL, tex_lado=MARMOL)
# balcon norte con su escalera al oeste, balcon sur con la suya al este
escalon("balcon_n", 6144, -3584, 11264, -3072, 500, color=(100, 75, 70), tex_tapa=TABLONES, tex_lado=PANELES)
for k, alto in enumerate((170, 340)):
    escalon(f"escalera_n{k}", 6144 + 512 * k, -3072, 6656 + 512 * k, -2560, alto, color=(100, 75, 70),
            tex_tapa=TABLONES, tex_lado=PANELES)
escalon("balcon_s", 6144, 1024, 11264, 1536, 500, color=(100, 75, 70), tex_tapa=TABLONES, tex_lado=PANELES)
for k, alto in enumerate((170, 340)):
    escalon(f"escalera_s{k}", 10752 - 512 * k, 512, 11264 - 512 * k, 1024, alto, color=(100, 75, 70),
            tex_tapa=TABLONES, tex_lado=PANELES)
# el trono al fondo y los candelabros que cuelgan
escalon("trono", 10752, -1280, 11264, -768, 260, color=(150, 40, 50), tex_tapa=TELA_ROJA, tex_lado=PUERTA_ORO)
for k, (x, z) in enumerate(((7680, -1280), (9728, -1280))):
    losa(f"candelabro{k}", x, z, x + 512, z + 512, 1300, 80, color=(220, 180, 70), tex_tapa=ORO, tex_lado=ORO)
zona("EL GRAN SALON DEL CASTILLO", (6656 + 37, -1024 + 53, 0x400),
     calabazas=[(8704, -500, -3328), (6656, -500, 1280), (10496, -500, 1280), (8704, 0, -512), (11008, -260, -1024),
                (7424, 0, 512)],
     dulces=[(7680, 0, -1024), (8192, 0, -1024), (9216, 0, -1024), (9728, 0, -1024), (7168, -500, -3328),
             (10240, -500, 1280)],
     farolas=[(6400, -500, -3328), (11008, -500, -3328), (6400, -500, 1280), (11008, -500, 1280)],
     velas=[(7936, -1300, -1024), (9984, -1300, -1024), (10880, -260, -1152), (10880, -260, -896)],
     manzanas=[(9216, 0, 0), (8192, -500, -3328)],
     fantasmas=[(8704, 0, -1536), (9728, 0, 512)],
     murcielagos=[(7680, -700, -1024), (9728, -700, -1024)],
     saltarinas=[(8192, 0, 0), (9984, 0, -2304)],
     portal=(8704, 0, -1024), lema="LOS CANDELABROS TIEMBLAN SOLOS...")

# ==================================================================== 3. la torre embrujada
Z3 = (13312, -3584, 15360, -1536)
suelo("torre_suelo", *Z3, color=PIEDRA_NOCHE, tex_tapa=PIEDRA5)
recinto("torre", *Z3, 3400, color=(80, 75, 95), tex_tapa=PIEDRA, tex_lado=VETEADA)
# el tejado conico de la torre: tres pisos que se achican (se ve desde todo el castillo)
for k, (m, alto) in enumerate(((0, 300), (384, 300), (768, 300))):
    pared(f"torre_tejado{k}", Z3[0] - 256 + m, Z3[1] - 256 + m, Z3[2] + 256 - m, Z3[3] + 256 - m, alto,
          base=3400 + 300 * k, color=(70, 40, 80), tex_tapa=TEJAS, tex_lado=TEJAS)
# las plataformas en espiral, pegadas a los muros por dentro, subiendo 250 cada una (Sabrina sube sola hasta ~360):
# ocho sitios (esquinas y mitades de cada lado) de 576 con huecos de 96, que se saltan hasta desde parada; la vuelta y
# media llega hasta 2750, pegada a la cima del centro (3000)
ox, oz = Z3[0] + 64, Z3[1] + 64
PELDANO = 576
anillo = [(ox + 672 * a, oz + 672 * b) for a, b in ((0, 0), (1, 0), (2, 0), (2, 1), (2, 2), (1, 2), (0, 2), (0, 1))]
plataformas = []
for k in range(11):
    x, z = anillo[(k + 1) % 8]
    alto = 250 * (k + 1)
    losa(f"peldano{k}", x, z, x + PELDANO, z + PELDANO, alto, color=(110, 95, 120), tex_tapa=PIEDRA3, tex_lado=VETEADA)
    plataformas.append((x + PELDANO // 2, alto, z + PELDANO // 2))
losa("torre_cima", ox + PELDANO, oz + PELDANO, ox + 1344, oz + 1344, 3000, 160, color=(130, 110, 60), tex_tapa=ORO,
     tex_lado=BANDA_ORO)
zona("LA TORRE EMBRUJADA", (14336 + 37, -2560 + 53, 0x400),
     calabazas=[(x, -a, z) for (x, a, z) in plataformas[1:11:2]],
     dulces=[(x, -a, z) for (x, a, z) in plataformas[0:11:2]],
     farolas=[(ox + 960, -3000, oz + 640), (ox + 640, -3000, oz + 960)],
     velas=[(x + 150, -a, z + 150) for (x, a, z) in plataformas[2:11:3]],
     manzanas=[(plataformas[5][0], -plataformas[5][1], plataformas[5][2])],
     murcielagos=[(14336, -900, -2560), (14336, -1700, -2560), (14336, -2500, -2560), (13824, -1300, -3072)],
     portal=(ox + 960, -3000, oz + 960), lema="SUBE HASTA LO MAS ALTO, SI TE ATREVES")

# ==================================================================== 4. la mazmorra del Rey Calabaza
Z4 = (6144, 4096, 10240, 8192)
suelo("mazmorra", *Z4, color=(90, 60, 60), tex_tapa=PIEDRA5)
recinto("mazmorra", *Z4, 900, color=(75, 60, 70), tex_tapa=PIEDRA, tex_lado=VETEADA)
for k, (x, z) in enumerate(((6912, 4864), (8960, 4864), (6912, 6912), (8960, 6912))):
    pared(f"pilar{k}", x, z, x + 384, z + 384, 900, color=(95, 80, 90), tex_tapa=PIEDRA, tex_lado=VETEADA)
    pared(f"brasero{k}", x + 64, z + 64, x + 320, z + 320, 120, base=900, color=(255, 120, 30), tex_tapa=TELA_ROJA,
          tex_lado=ORO)
zona("LA MAZMORRA DEL REY CALABAZA", (6656 + 37, 6144 + 53, 0x400), calabazas=[],
     manzanas=[(7168, 0, 7680), (9216, 0, 4608), (9216, 0, 7680)],
     fantasmas=[(8192, 0, 5120), (8192, 0, 7168)],
     esqueletos=[(6656, 0, 4608), (9728, 0, 7680)],
     dulces=[(7424, 0, 5632), (8960, 0, 5632), (7424, 0, 6656), (8960, 0, 6656)],
     farolas=[(7104, -1020, 5056), (9152, -1020, 5056), (7104, -1020, 7104), (9152, -1020, 7104)],
     lema="EL REY CALABAZA: NADIE SALE DE MI CASTILLO!")
JEFE = (8192, 6144)

cielo = dict(cenit=[12, 6, 30], horizonte=[160, 70, 30], nadir=[20, 8, 28])   # noche con el resplandor naranja


# ==================================================================== lados que no se ven
def cubierto(p, lado, otros):
    x0, z0, x1, z1 = p["x0"], p["z0"], p["x1"], p["z1"]
    if lado in ("x0", "x1"):
        x = x0 - 32 if lado == "x0" else x1 + 32
        puntos = [(x, z) for z in range(z0 + 32, z1, 64)]
    else:
        z = z0 - 32 if lado == "z0" else z1 + 32
        puntos = [(x, z) for x in range(x0 + 32, x1, 64)]
    # el vecino tiene que tapar el lado entero de arriba abajo: empezar igual o mas arriba y llegar igual o mas abajo
    # (un tejado que flota sobre un muro no le tapa los lados: sin ellos el muro no choca y Sabrina lo atraviesa)
    fondo = p["h"] + p.get("prof", n.PROFUNDO)
    return all(any(q["x0"] <= x < q["x1"] and q["z0"] <= z < q["z1"] and q["h"] <= p["h"] and not q.get("techo")
                   and q["h"] + q.get("prof", n.PROFUNDO) >= fondo for q in otros) for x, z in puntos)


for p in bloques:
    if p.get("techo"):
        continue
    otros = [q for q in bloques if q is not p]
    p["sin_lados"] = [l for l in ("x0", "x1", "z0", "z1") if cubierto(p, l, otros)]


def medir():
    """(bytes del .INO con el mapa, el cielo y los modelos de Halloween, bytes que caben)."""
    import halloween_modelos as hm
    maximo = os.path.getsize(os.path.join(n.disco.RAIZ, "extraido", "GRAPHICS", "HUB", "H1W.INO"))
    try:
        n.nf.construir_bytes(n.nodo_de(bloques), n.CONSERVAR_PLAT, sin_objetos=True, paredes=True, callar=True,
                             reemplazos=hm.reemplazos(dict(n.CIELO_DEFECTO, **cielo)))
    except ValueError:
        pass
    return n.nf.ULTIMO["tamano"], maximo


def escribir_h(ruta):
    def lista(nombre, puntos, n_max):
        f.write(f"static const s16 {nombre}[HW_ZONAS][{n_max}][3] = {{\n")
        for z in zonas:
            pts = z[puntos] + [(0, 0, 0)] * (n_max - len(z[puntos]))
            f.write("    {" + ", ".join("{%d, %d, %d}" % p for p in pts) + "},\n")
        f.write("};\n")
    LISTAS = ("calabazas", "manzanas", "fantasmas", "murcielagos", "saltarinas", "esqueletos", "dulces", "farolas",
              "velas")
    maxs = {k: max(1, max(len(z[k]) for z in zonas)) for k in LISTAS}
    max_sustos = max(1, max(len(z["sustos"]) for z in zonas))
    with open(ruta, "w", encoding="utf-8", newline="\n") as f:
        f.write("/* Generado por scripts/mapa_halloween.py: no editar a mano. El castillo de Halloween (niveles/halloween.json).\n"
                " * Por zona: la salida (x, z, rumbo), cuantas calabazas, y las posiciones (x, y, z; y hacia abajo) de las\n"
                " * calabazas, las manzanas, los fantasmas, los murcielagos y las calabazas saltarinas; el portal; el jefe. */\n")
        f.write(f"#define HW_ZONAS {len(zonas)}\n")
        for k, v in maxs.items():
            f.write(f"#define HW_MAX_{k.upper()} {v}\n")
        f.write("static const s16 hw_salida[HW_ZONAS][3] = {" + ", ".join("{%d, %d, %d}" % z["salida"] for z in zonas) + "};\n")
        for k in LISTAS:
            f.write(f"static const u8 hw_n_{k}[HW_ZONAS] = {{" + ", ".join(str(len(z[k])) for z in zonas) + "};\n")
        for k in LISTAS:
            lista(f"hw_{k}", k, maxs[k])
        f.write(f"#define HW_MAX_SUSTOS {max_sustos}\n")
        f.write("static const u8 hw_n_sustos[HW_ZONAS] = {" + ", ".join(str(len(z["sustos"])) for z in zonas) + "};\n")
        f.write("static const s16 hw_sustos[HW_ZONAS][HW_MAX_SUSTOS][6] = {\n")
        for z in zonas:
            su = z["sustos"] + [(0, 0, 0, 0, 0, 0)] * (max_sustos - len(z["sustos"]))
            f.write("    {" + ", ".join("{%d, %d, %d, %d, %d, %d}" % t for t in su) + "},\n")
        f.write("};\n")
        f.write("static const char *const hw_nombre[HW_ZONAS] = {" + ", ".join('"%s"' % z["nombre"] for z in zonas) +
                "};\n")
        f.write("static const char *const hw_lema[HW_ZONAS] = {" + ", ".join('"%s"' % z["lema"] for z in zonas) +
                "};\n")
        f.write("static const s16 hw_portal[HW_ZONAS][3] = {" + ", ".join(
            "{%d, %d, %d}" % (z["portal"] or (0, 0, 0)) for z in zonas) + "};\n")
        f.write(f"#define HW_JEFE_X {JEFE[0]}\n#define HW_JEFE_Z {JEFE[1]}\n")
        f.write(f"#define HW_DULCES_TOTAL {sum(len(z['dulces']) for z in zonas)}\n")


if __name__ == "__main__":
    errores, avisos = n.validar(bloques)
    print(len(bloques), "bloques; errores:", errores)
    for a in avisos:
        if "no se alcanza" not in a:         # las zonas se unen por portales: esas son normales
            print("aviso:", a)
    tam, maximo = medir()
    print(f"tamano del .INO (con los modelos): {tam} de {maximo} bytes ({100 * tam / maximo:.1f} %)")
    if not errores and tam <= maximo:
        ruta = os.path.join(n.NIVELES, "halloween.json")
        n.guardar(bloques, ruta, cielo)
        print("escrito", ruta)
        h = os.path.join(n.disco.RAIZ, "decomp", "src", "objetos", "halloween_mapa.h")
        escribir_h(h)
        print("escrito", h)
