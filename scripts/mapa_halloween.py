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


def zona(salida, calabazas, manzanas, fantasmas=(), murcielagos=(), saltarinas=(), portal=None):
    """salida: donde aparece Sabrina al entrar (x, z, rumbo). No puede caer en una arista de los triangulos del suelo
    (multiplos de 256 y sus diagonales) o Sabrina se cae a traves: por eso las salidas van corridas (+37, +53)."""
    zonas.append(dict(salida=salida, calabazas=list(calabazas), manzanas=list(manzanas), fantasmas=list(fantasmas),
                      murcielagos=list(murcielagos), saltarinas=list(saltarinas), portal=portal))


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
zona((128, -896, 0x800),
     calabazas=[(-1536, 0, -3200), (2048, -720, -2944), (-1152, 0, 768), (1792, 0, 1024), (-512, 0, -1792),
                (2432, 0, -1792)],
     manzanas=[(512, 0, 1024), (-1792, 0, -768)],
     fantasmas=[(-1408, 0, -2048), (2304, 0, -1024), (-1024, 0, 1280)],
     portal=(512, 0, -3200))

# ==================================================================== 2. el gran salon del castillo
Z2 = (6144, -3584, 11264, 1536)
for i in range(5):
    for j in range(5):
        x0, z0 = Z2[0] + 1024 * i, Z2[1] + 1024 * j
        claro = (i + j) % 2 == 0
        suelo(f"ajedrez{i}{j}", x0, z0, x0 + 1024, z0 + 1024, color=(150, 145, 160) if claro else (55, 50, 65),
              tex_tapa=MARMOL if claro else LISA)
recinto("castillo", *Z2, 1000, color=LADRILLO_NOCHE, tex_tapa=PIEDRA, tex_lado=LADRILLO)
# almenas sobre el muro del castillo (se ven de lejos, desde el cementerio)
for k in range(5):
    x = Z2[0] + 512 + 1024 * k
    pared(f"almena_n{k}", x, Z2[1] - 256, x + 256, Z2[1], 220, base=1000, color=LADRILLO_NOCHE, tex_lado=LADRILLO)
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
zona((6656 + 37, -1024 + 53, 0x400),
     calabazas=[(8704, -500, -3328), (6656, -500, 1280), (10496, -500, 1280), (8704, 0, -512), (11008, -260, -1024),
                (7424, 0, 512)],
     manzanas=[(9216, 0, 0), (8192, -500, -3328)],
     fantasmas=[(8704, 0, -1536), (9728, 0, 512)],
     murcielagos=[(7680, -700, -1024), (9728, -700, -1024)],
     saltarinas=[(8192, 0, 0), (9984, 0, -2304)],
     portal=(8704, 0, -1024))

# ==================================================================== 3. la torre embrujada
Z3 = (13312, -3584, 15360, -1536)
suelo("torre_suelo", *Z3, color=PIEDRA_NOCHE, tex_tapa=PIEDRA5)
recinto("torre", *Z3, 3400, color=(80, 75, 95), tex_tapa=PIEDRA, tex_lado=VETEADA)
# el tejado conico de la torre: tres pisos que se achican (se ve desde todo el castillo)
for k, (m, alto) in enumerate(((0, 300), (384, 300), (768, 300))):
    pared(f"torre_tejado{k}", Z3[0] - 256 + m, Z3[1] - 256 + m, Z3[2] + 256 - m, Z3[3] + 256 - m, alto,
          base=3400 + 300 * k, color=(70, 40, 80), tex_tapa=TEJAS, tex_lado=TEJAS)
# las plataformas en espiral, pegadas a los muros por dentro, subiendo 250 cada una: ocho sitios (esquinas y mitades de
# cada lado, separados 192, que se saltan) y la vuelta y media llega hasta 2750, junto a la cima del centro (3000)
ox, oz = Z3[0] + 64, Z3[1] + 64
anillo = [(ox + 704 * a, oz + 704 * b) for a, b in ((0, 0), (1, 0), (2, 0), (2, 1), (2, 2), (1, 2), (0, 2), (0, 1))]
plataformas = []
for k in range(11):
    x, z = anillo[(k + 1) % 8]
    alto = 250 * (k + 1)
    losa(f"peldano{k}", x, z, x + 512, z + 512, alto, color=(110, 95, 120), tex_tapa=PIEDRA3, tex_lado=VETEADA)
    plataformas.append((x + 256, alto, z + 256))
losa("torre_cima", ox + 576, oz + 576, ox + 1344, oz + 1344, 3000, 160, color=(130, 110, 60), tex_tapa=ORO,
     tex_lado=BANDA_ORO)
zona((14336 + 37, -2560 + 53, 0x400),
     calabazas=[(x, -a, z) for (x, a, z) in plataformas[1:11:2]],
     manzanas=[(plataformas[5][0], -plataformas[5][1], plataformas[5][2])],
     murcielagos=[(14336, -900, -2560), (14336, -1700, -2560), (14336, -2500, -2560), (13824, -1300, -3072)],
     portal=(ox + 960, -3000, oz + 960))

# ==================================================================== 4. la mazmorra del Rey Calabaza
Z4 = (6144, 4096, 10240, 8192)
suelo("mazmorra", *Z4, color=(90, 60, 60), tex_tapa=PIEDRA5)
recinto("mazmorra", *Z4, 900, color=(75, 60, 70), tex_tapa=PIEDRA, tex_lado=VETEADA)
for k, (x, z) in enumerate(((6912, 4864), (8960, 4864), (6912, 6912), (8960, 6912))):
    pared(f"pilar{k}", x, z, x + 384, z + 384, 900, color=(95, 80, 90), tex_tapa=PIEDRA, tex_lado=VETEADA)
    pared(f"brasero{k}", x + 64, z + 64, x + 320, z + 320, 120, base=900, color=(255, 120, 30), tex_tapa=TELA_ROJA,
          tex_lado=ORO)
zona((6656 + 37, 6144 + 53, 0x400), calabazas=[], manzanas=[(7168, 0, 7680), (9216, 0, 4608), (9216, 0, 7680)])
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
    return all(any(q["x0"] <= x < q["x1"] and q["z0"] <= z < q["z1"] and q["h"] <= p["h"] and not q.get("techo")
                   for q in otros) for x, z in puntos)


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
    maxs = {k: max(1, max(len(z[k]) for z in zonas)) for k in ("calabazas", "manzanas", "fantasmas", "murcielagos",
                                                                 "saltarinas")}
    with open(ruta, "w", encoding="utf-8", newline="\n") as f:
        f.write("/* Generado por scripts/mapa_halloween.py: no editar a mano. El castillo de Halloween (niveles/halloween.json).\n"
                " * Por zona: la salida (x, z, rumbo), cuantas calabazas, y las posiciones (x, y, z; y hacia abajo) de las\n"
                " * calabazas, las manzanas, los fantasmas, los murcielagos y las calabazas saltarinas; el portal; el jefe. */\n")
        f.write(f"#define HW_ZONAS {len(zonas)}\n")
        for k, v in maxs.items():
            f.write(f"#define HW_MAX_{k.upper()} {v}\n")
        f.write("static const s16 hw_salida[HW_ZONAS][3] = {" + ", ".join("{%d, %d, %d}" % z["salida"] for z in zonas) + "};\n")
        for k in ("calabazas", "manzanas", "fantasmas", "murcielagos", "saltarinas"):
            f.write(f"static const u8 hw_n_{k}[HW_ZONAS] = {{" + ", ".join(str(len(z[k])) for z in zonas) + "};\n")
        for k in ("calabazas", "manzanas", "fantasmas", "murcielagos", "saltarinas"):
            lista(f"hw_{k}", k, maxs[k])
        f.write("static const s16 hw_portal[HW_ZONAS][3] = {" + ", ".join(
            "{%d, %d, %d}" % (z["portal"] or (0, 0, 0)) for z in zonas) + "};\n")
        f.write(f"#define HW_JEFE_X {JEFE[0]}\n#define HW_JEFE_Z {JEFE[1]}\n")


if __name__ == "__main__":
    errores, avisos = n.validar(bloques)
    print(len(bloques), "bloques; errores:", errores)
    for a in avisos:
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
