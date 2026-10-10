"""Genera niveles\\kart.json y decomp\\src\\objetos\\kart_pista.h: la pista de SABRINA KART, la Copa del Tiempo.

Un circuito cerrado de carreras hecho con los bloques del motor (nivel_plataformas.py) y las texturas del juego,
pensado como si fuera un nivel escondido de A Twitch in Time: cada tramo es una de las epocas del juego.

- Recta de Greendale (la salida): marmol, la linea de meta dorada bajo el arco con el letrero, la casa Spellman con
  su torreon detras del muro.
- Curva y recta de Egipto: arena dorada, la piramide escalonada y los obeliscos detras del muro, la puerta de
  jeroglificos sobre la pista y la cinta de hechizos.
- El Oeste: tablones, el deposito de agua y el saloon detras del muro, cactus sobre los setos y el puente del rio
  Sweetwater.
- La Edad de Piedra: la horquilla que entra al centro del circuito, el dintel de piedra (como Stonehenge) sobre la
  pista y los menhires.
- El Vortice del tiempo: azulejo turquesa, el portal del tiempo sobre la pista, la segunda cinta de hechizos y el
  ultimo turbo.

Todo es plano, sin rampas ni saltos ni escalones: los turbos y las cintas de hechizo van a ras de la pista (la pista
se parte alrededor de ellos; un bloque levantado, aunque sea 64, es una pared para el kart). Por dentro, el centro
del circuito son setos macizos de 450 de alto (con menos de ~370 Sabrina se sube sola) y por fuera un muro igual de
alto: no hay por donde salirse. Los lados que nadie ve (los de la pista contra los setos y los muros, y los de dos
setos que se tocan) no se generan ('sin_lados'): ahorran triangulos para el decorado.
La salida del juego (128, -896) queda en la recta de Greendale, antes de la linea de meta.

El .h dice al codigo del kart (decomp/src/objetos/kart.inc, SABRINA_KART) donde estan los puntos de control (en
orden, el 0 es la meta), los turbos y las cintas de hechizo, en unidades del modelo (x0, z0, x1, z1).

Uso: python mapa_kart.py      (escribe los dos archivos y dice cuanto ocupa el .INO, con el carrito incluido)
"""
import os

import nivel_plataformas as n

# texturas (galeria del editor, PALETA en nivel_plataformas)
PIEDRA, VETEADA, LISA, PIEDRA3, PIEDRA4, PIEDRA5 = 16, 1, 13, 67, 71, 98
MARMOL, AGUA, LADRILLO, TEJAS, TABLONES = 69, 66, 88, 96, 97
VALLA, HIERBA, ORO, AZULEJO, GLIFO = 100, 81, 77, 78, 79
PUERTA_ORO, JEROGLIFOS, MURAL, BANDA_ORO = 90, 76, 75, 70
TELA_ROJA, TELA_VERDE, REMOLINO, LETRERO, LETRERO2 = 106, 107, 101, 94, 95
PANELES, PUERTA, ARCO, OXIDO, ZODIACO = 110, 108, 109, 89, 2

ANCHO = 1536                     # ancho de la pista
MEDIO = ANCHO // 2
PROF_PISTA = 136                 # cuanto baja la pista (no se ve: todos sus lados estan contra setos o muros)
MURO_H = 450                     # alto de setos y muros: con menos de ~370 Sabrina se sube sola
HONDO = 600                      # cuanto bajan los setos, los muros y el decorado (por debajo no hay nada)
RIO = (8320, 8704)               # el rio Sweetwater cruza el mapa de norte a sur

# el recorrido (en el sentido de la carrera): Greendale al este, Egipto al sur, el Oeste al oeste, la horquilla de
# piedra hacia el centro y el vortice de vuelta a la salida
A, B, C, D = (-3072, -896), (10240, -896), (10240, 7168), (6144, 7168)
E, F, G, H = (6144, 3584), (2048, 3584), (2048, 7168), (-3072, 7168)
X0, Z0 = A[0] - MEDIO, A[1] - MEDIO           # borde de fuera de la pista
X1, Z1 = B[0] + MEDIO, C[1] + MEDIO

bloques = []
pista = []                       # los trozos de suelo, antes de partirlos alrededor de turbos y cintas
cp, turbos, cajas, especiales = [], [], [], []


def bloque(nombre, x0, z0, x1, z1, **kw):
    """Un trozo de pista plano a altura 0."""
    kw.setdefault("prof", PROF_PISTA)
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 1024)
    kw.setdefault("tex_lado", PIEDRA)
    pista.append(n.nueva(nombre, x0, z0, x1, z1, 0, **kw))


def pared(nombre, x0, z0, x1, z1, alto=MURO_H, base=0, **kw):
    """Un bloque macizo de 'alto' sobre 'base' (los setos, los muros, columnas y edificios); baja HONDO por debajo de
    la pista salvo que se pida otro 'extra'."""
    kw.setdefault("color", (110, 105, 100))
    kw.setdefault("tex_tapa", PIEDRA)
    kw.setdefault("tex_lado", PIEDRA)
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 1024)
    extra = kw.pop("extra", HONDO if base == 0 else 0)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -(base + alto), pared=True, prof=alto + extra, **kw))


def losa(nombre, x0, z0, x1, z1, base, alto, **kw):
    """Una losa que flota (dintel, letrero, alero): se ve tambien desde abajo."""
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 512)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -(base + alto), pared=True, prof=alto, techo=True, **kw))


def esquina(p):
    return p[0] - MEDIO, p[1] - MEDIO, p[0] + MEDIO, p[1] + MEDIO


def punto_control(x0, z0, x1, z1, rumbo):
    """rumbo: hacia donde mira el kart al reaparecer ahi (0 = +z, 0x400 = +x, 0x800 = -z, 0xC00 = -x)."""
    cp.append((x0, z0, x1, z1, (x0 + x1) // 2, (z0 + z1) // 2, rumbo))


def turbo(x0, z0, x1, z1):
    turbos.append((x0, z0, x1, z1))
    especiales.append(("turbo", (x0, z0, x1, z1), dict(color=(150, 170, 255), tex_tapa=REMOLINO)))


def cinta(x0, z0, x1, z1):
    """Una cinta dorada de lado a lado de la pista y, encima, tres cajas de hechizo que flotan y giran (kart.inc):
    una en el centro y una a cada lado, a 512."""
    cx, cz = (x0 + x1) // 2, (z0 + z1) // 2
    for k in (-512, 0, 512):
        cajas.append((cx + k, cz) if x1 - x0 > z1 - z0 else (cx, cz + k))
    especiales.append(("cinta", (x0, z0, x1, z1), dict(color=(210, 175, 90), tex_tapa=GLIFO)))


def linea(x0, z0, x1, z1, **kw):
    """Una franja de otro color a ras del suelo (la linea de meta)."""
    especiales.append(("linea", (x0, z0, x1, z1), kw))


def arco(nombre, eje, centro, desde, hasta, alto, base_dintel, **kw):
    """Un arco sobre la pista: dos columnas fuera de ella (en los setos o los muros) y un dintel por encima.
    eje "x": la pista va en x y el arco la cruza en z (desde..hasta es el ancho a cubrir); "z" al reves."""
    col = dict(color=kw.get("color_col", (150, 130, 90)), tex_tapa=kw.get("tex_col", ORO),
               tex_lado=kw.get("tex_col", BANDA_ORO), paso_lado=512)
    din = dict(color=kw.get("color", (150, 140, 120)), tex_tapa=kw.get("tex_tapa", TELA_ROJA),
               tex_lado=kw.get("tex_lado", LETRERO))
    g = kw.get("grueso", 512)
    if eje == "x":
        pared(nombre + "_c1", centro - g // 2, desde - 256, centro + g // 2, desde, alto=base_dintel, **col)
        pared(nombre + "_c2", centro - g // 2, hasta, centro + g // 2, hasta + 256, alto=base_dintel, **col)
        losa(nombre, centro - g // 2, desde - 256, centro + g // 2, hasta + 256, base_dintel, alto - base_dintel, **din)
    else:
        pared(nombre + "_c1", desde - 256, centro - g // 2, desde, centro + g // 2, alto=base_dintel, **col)
        pared(nombre + "_c2", hasta, centro - g // 2, hasta + 256, centro + g // 2, alto=base_dintel, **col)
        losa(nombre, desde - 256, centro - g // 2, hasta + 256, centro + g // 2, base_dintel, alto - base_dintel, **din)


# ============================================================ los setos y el rio
# Todo lo que no es pista dentro del muro de fuera: el centro del circuito partido por el rio, los dos lados de la
# horquilla y el hueco del sur entre las curvas G y D. Son setos macizos: sus lados son los muros de dentro.
color_hierba = (78, 112, 64)
for nombre, x0, z0, x1, z1 in (("seto_centro_o", A[0] + MEDIO, A[1] + MEDIO, RIO[0], E[1] - MEDIO),
                               ("seto_centro_e", RIO[1], A[1] + MEDIO, B[0] - MEDIO, E[1] - MEDIO),
                               ("seto_oeste", A[0] + MEDIO, E[1] - MEDIO, F[0] - MEDIO, G[1] - MEDIO),
                               ("seto_este_o", E[0] + MEDIO, E[1] - MEDIO, RIO[0], C[1] - MEDIO),
                               ("seto_este_e", RIO[1], E[1] - MEDIO, B[0] - MEDIO, C[1] - MEDIO),
                               ("seto_horquilla", F[0] + MEDIO, E[1] + MEDIO, E[0] - MEDIO, C[1] + MEDIO)):
    pared(nombre, x0, z0, x1, z1, color=color_hierba, tex_tapa=HIERBA, tex_lado=VALLA)
bloques.append(n.nueva("rio", RIO[0], A[1] + MEDIO + 256, RIO[1], C[1] - MEDIO - 256, 400, color=(70, 110, 140),
                       tex_tapa=AGUA, tex_lado=PIEDRA, prof=200, paso=512, paso_lado=1024, pared=True))
# barandas de los puentes del lado del rio que no tiene seto
for nombre, z0 in (("baranda_n", A[1] + MEDIO), ("baranda_s", C[1] - MEDIO - 256)):
    pared(nombre, RIO[0], z0, RIO[1], z0 + 256, color=(120, 100, 80), tex_tapa=TABLONES, tex_lado=TABLONES)

# ============================================================ recta de Greendale (la salida)
GREEN = dict(color=(150, 150, 170), tex_tapa=MARMOL)
bloque("salida_a", A[0] + MEDIO, A[1] - MEDIO, RIO[0], A[1] + MEDIO, **GREEN)
bloque("puente_rio", RIO[0], A[1] - MEDIO, RIO[1], A[1] + MEDIO, color=(120, 100, 80), tex_tapa=TABLONES)
bloque("salida_b", RIO[1], A[1] - MEDIO, B[0] - MEDIO, A[1] + MEDIO, **GREEN)
punto_control(768, A[1] - MEDIO, 1280, A[1] + MEDIO, 0x400)            # 0: la meta
linea(768, A[1] - MEDIO, 1280, A[1] + MEDIO, color=(230, 200, 120), tex_tapa=BANDA_ORO)
arco("meta", "x", 1024, Z0, A[1] + MEDIO, 1100, 840, color=(150, 140, 120), tex_tapa=TELA_ROJA, tex_lado=LETRERO)
turbo(4096, A[1] - 256, 4608, A[1] + 256)
# la casa Spellman detras del muro norte: casa, tejado, torreon con su punta y el porche
pared("casa", 2048, -3840, 3840, -2432, alto=1000, color=(150, 120, 110), tex_tapa=TEJAS, tex_lado=LADRILLO)
pared("tejado", 2304, -3584, 3584, -2688, alto=280, base=1000, color=(120, 80, 72), tex_tapa=TEJAS, tex_lado=TEJAS)
pared("torreon", 3584, -3328, 4352, -2560, alto=1600, color=(150, 120, 110), tex_tapa=TEJAS, tex_lado=LADRILLO)
pared("torreon_punta", 3712, -3200, 4224, -2688, alto=400, base=1600, color=(110, 72, 66), tex_tapa=TEJAS,
      tex_lado=TEJAS)
pared("porche", 2304, -2432, 3584, -2176, alto=420, color=(200, 190, 175), tex_tapa=TABLONES, tex_lado=PANELES)

# ============================================================ Egipto: curva B y recta hacia el sur
EGIPTO = dict(color=(170, 150, 105), tex_tapa=ORO, tex_lado=JEROGLIFOS)
bloque("curva_b", *esquina(B), **EGIPTO)
bloque("egipto", B[0] - MEDIO, B[1] + MEDIO, B[0] + MEDIO, C[1] - MEDIO, **EGIPTO)
punto_control(B[0] - MEDIO, 2560, B[0] + MEDIO, 3072, 0)               # 1
turbo(B[0] - 256, 512, B[0] + 256, 1024)
cinta(B[0] - MEDIO, 4608, B[0] + MEDIO, 4864)
arco("puerta_egipto", "z", 1792, B[0] - MEDIO, B[0] + MEDIO, 1200, 900, color=(180, 160, 110), tex_tapa=ORO,
     tex_lado=JEROGLIFOS, color_col=(180, 160, 110), tex_col=MURAL)
# la piramide escalonada y los obeliscos detras del muro este
for i, (lado, alto) in enumerate(((2048, 500), (1280, 500), (512, 500))):
    cx, cz = 12800, 2304
    pared(f"piramide{i}", cx - lado // 2, cz - lado // 2, cx + lado // 2, cz + lado // 2, alto=alto, base=500 * i,
          extra=HONDO if i == 0 else 0, color=(200, 170, 110), tex_tapa=ORO if i == 2 else GLIFO, tex_lado=ORO)
for i, z in enumerate((-256, 5376)):
    pared(f"obelisco{i}", 11520, z, 11776, z + 256, alto=1500, color=(180, 160, 110), tex_tapa=ORO,
          tex_lado=JEROGLIFOS, paso_lado=512)

# ============================================================ el Oeste: curva C y el puente del rio
OESTE = dict(color=(140, 110, 85), tex_tapa=TABLONES, tex_lado=VALLA)
bloque("curva_c", *esquina(C), **OESTE)
bloque("oeste", RIO[1], C[1] - MEDIO, C[0] - MEDIO, C[1] + MEDIO, **OESTE)
bloque("puente_oeste", RIO[0], C[1] - MEDIO, RIO[1], C[1] + MEDIO, color=(120, 100, 80), tex_tapa=TABLONES)
bloque("llegada", D[0] + MEDIO, C[1] - MEDIO, RIO[0], C[1] + MEDIO, **OESTE)
punto_control(7168, C[1] - MEDIO, 7680, C[1] + MEDIO, 0xC00)           # 2
# el deposito de agua y el saloon detras del muro sur
for i, (x, z) in enumerate(((9472, 8960), (10240, 9216))):
    pared(f"deposito_pata{i}", x, z, x + 256, z + 256, alto=900, color=(110, 85, 65), tex_tapa=TABLONES,
          tex_lado=TABLONES, paso_lado=512)
pared("deposito", 9216, 8448, 10752, 9984, alto=700, base=900, color=(130, 100, 75), tex_tapa=TEJAS, tex_lado=PANELES)
pared("saloon", 6656, 8448, 8192, 9472, alto=900, color=(160, 120, 85), tex_tapa=TABLONES, tex_lado=PUERTA)
pared("saloon_letrero", 6912, 8448, 7936, 8704, alto=300, base=900, color=(170, 140, 100), tex_tapa=TABLONES,
      tex_lado=LETRERO2)
# cactus sobre el seto del Oeste (tronco y dos brazos)
for i, (x, z) in enumerate(((9216, 5632), (7168, 5376), (9728, 4096))):
    pared(f"cactus{i}", x, z, x + 256, z + 256, alto=600, base=MURO_H, color=(70, 140, 70), tex_tapa=TELA_VERDE,
          tex_lado=TELA_VERDE)
    pared(f"cactus{i}_brazo", x - 256, z, x + 512, z + 256, alto=128, base=MURO_H + 256, color=(70, 140, 70),
          tex_tapa=TELA_VERDE, tex_lado=TELA_VERDE)

# ============================================================ Edad de Piedra: la horquilla D-E-F-G
PIEDRA_K = dict(color=(135, 128, 118), tex_tapa=PIEDRA3, tex_lado=PIEDRA)
bloque("curva_d", *esquina(D), **PIEDRA_K)
bloque("piedra_sube", D[0] - MEDIO, E[1] + MEDIO, D[0] + MEDIO, D[1] - MEDIO, **PIEDRA_K)
bloque("curva_e", *esquina(E), **PIEDRA_K)
bloque("piedra_cruza", F[0] + MEDIO, E[1] - MEDIO, E[0] - MEDIO, E[1] + MEDIO, **PIEDRA_K)
punto_control(3584, E[1] - MEDIO, 4096, E[1] + MEDIO, 0xC00)           # 3
bloque("curva_f", *esquina(F), **PIEDRA_K)
bloque("piedra_baja", F[0] - MEDIO, F[1] + MEDIO, F[0] + MEDIO, G[1] - MEDIO, **PIEDRA_K)
turbo(F[0] - 256, 4864, F[0] + 256, 5376)
arco("dintel_piedra", "x", 4864, E[1] - MEDIO, E[1] + MEDIO, 1150, 850, color=(130, 125, 115), tex_tapa=PIEDRA,
     tex_lado=VETEADA, color_col=(130, 125, 115), tex_col=VETEADA)
# menhires en el centro de la horquilla, sobre el seto
for i, (x, z, alto) in enumerate(((3328, 5120, 700), (4352, 5632, 550), (3840, 6400, 800))):
    pared(f"menhir{i}", x, z, x + 384, z + 384, alto=alto, base=MURO_H, color=(120, 115, 105), tex_tapa=PIEDRA,
          tex_lado=VETEADA, paso_lado=512)

# ============================================================ el Vortice del tiempo: G-H-A
VORTICE = dict(color=(120, 150, 190), tex_tapa=AZULEJO, tex_lado=AZULEJO)
bloque("curva_g", *esquina(G), **VORTICE)
bloque("vortice", H[0] + MEDIO, G[1] - MEDIO, G[0] - MEDIO, G[1] + MEDIO, **VORTICE)
punto_control(-1024, G[1] - MEDIO, -512, G[1] + MEDIO, 0xC00)          # 4
cinta(256, G[1] - MEDIO, 512, G[1] + MEDIO)
arco("portal_tiempo", "x", -1792, G[1] - MEDIO, Z1, 1300, 1000, color=(120, 140, 230), tex_tapa=REMOLINO,
     tex_lado=REMOLINO, color_col=(110, 120, 200), tex_col=AZULEJO)
bloque("curva_h", *esquina(H), **VORTICE)
bloque("vortice_norte", H[0] - MEDIO, A[1] + MEDIO, H[0] + MEDIO, H[1] - MEDIO, **VORTICE)
punto_control(H[0] - MEDIO, 2560, H[0] + MEDIO, 3072, 0x800)            # 5
turbo(H[0] - 256, 4096, H[0] + 256, 4608)
bloque("curva_a", *esquina(A), **GREEN)
# ============================================================ el muro de fuera
pared("muro_n", X0 - 256, Z0 - 256, X1 + 256, Z0, tex_lado=LADRILLO, color=(150, 120, 110))
pared("muro_s", X0 - 256, Z1, X1 + 256, Z1 + 256, tex_lado=TABLONES, color=(140, 110, 85))
pared("muro_o", X0 - 256, Z0, X0, Z1, tex_lado=AZULEJO, color=(120, 150, 190))
pared("muro_e", X1, Z0, X1 + 256, Z1, tex_lado=JEROGLIFOS, color=(170, 150, 105))


# ============================================================ partir la pista alrededor de turbos, cintas y meta
def partir(p, r):
    """Los trozos de p que quedan alrededor del rectangulo r (que esta dentro de p), mas r con los datos de p."""
    x0, z0, x1, z1 = p["x0"], p["z0"], p["x1"], p["z1"]
    a0, b0, a1, b1 = r
    trozos = [(x0, z0, a0, z1), (a1, z0, x1, z1), (a0, z0, a1, b0), (a0, b1, a1, z1)]
    salida = []
    for i, (q0, w0, q1, w1) in enumerate(trozos):
        if q1 > q0 and w1 > w0:
            assert q1 - q0 >= 256 and w1 - w0 >= 256, (p["nombre"], r, (q0, w0, q1, w1))
            salida.append(dict(p, nombre=f"{p['nombre']}_{i}", x0=q0, z0=w0, x1=q1, z1=w1))
    return salida


# pianos rojos y blancos en el vertice de dentro de cada curva: la esquina del cuadro de la curva que da en diagonal
# a un seto, y desde ahi 512 a lo largo del borde de dentro de las dos rectas que llegan
setos = [b for b in bloques if b["nombre"].startswith("seto")]
ROJO, BLANCO = dict(color=(220, 50, 50), tex_tapa=TELA_ROJA), dict(color=(235, 235, 235), tex_tapa=LISA)


def piano(r, k):
    """Un cuadro de piano, si cae entero en un trozo de pista y no deja tiras de menos de 256 (el puente es mas angosto)."""
    if any(e[1] == r for e in especiales):
        return
    for q in pista:
        if q["x0"] <= r[0] and r[2] <= q["x1"] and q["z0"] <= r[1] and r[3] <= q["z1"]:
            if all(d == 0 or d >= 256 for d in (r[0] - q["x0"], q["x1"] - r[2], r[1] - q["z0"], q["z1"] - r[3])):
                especiales.append(("piano", r, ROJO if k % 2 == 0 else BLANCO))
            return


for nombre in ("curva_b", "curva_c", "curva_d", "curva_e", "curva_f", "curva_g", "curva_h", "curva_a"):
    q = next(p for p in pista if p["nombre"] == nombre)
    for sx in (-1, 1):
        for sz in (-1, 1):
            cx = q["x1"] if sx > 0 else q["x0"]
            cz = q["z1"] if sz > 0 else q["z0"]
            if not any(t["x0"] <= cx + 32 * sx < t["x1"] and t["z0"] <= cz + 32 * sz < t["z1"] for t in setos):
                continue
            bx = (cx - 256, cx) if sx > 0 else (cx, cx + 256)      # la franja de 256 de este lado del vertice
            bz = (cz - 256, cz) if sz > 0 else (cz, cz + 256)
            piano((bx[0], bz[0], bx[1], bz[1]), 0)
            for k in range(1, 3):
                # por la recta que sigue en x (borde z = cz) y por la que sigue en z (borde x = cx)
                x0 = cx + 256 * (k - 1) if sx > 0 else cx - 256 * k
                z0 = cz + 256 * (k - 1) if sz > 0 else cz - 256 * k
                piano((x0, bz[0], x0 + 256, bz[1]), k)
                piano((bx[0], z0, bx[1], z0 + 256), k)

for tipo, r, datos in especiales:
    # una cinta puede cruzar varios trozos (los que dejo un turbo): se parte cada uno por su parte de la cinta
    tocados = [q for q in pista if q["x0"] < r[2] and r[0] < q["x1"] and q["z0"] < r[3] and r[1] < q["z1"]]
    assert tocados, (tipo, r)
    for p in tocados:
        c = (max(r[0], p["x0"]), max(r[1], p["z0"]), min(r[2], p["x1"]), min(r[3], p["z1"]))
        pista.remove(p)
        pista.extend(partir(p, c))
        pista.append(dict(p, nombre=f"{tipo}_{len(pista)}", x0=c[0], z0=c[1], x1=c[2], z1=c[3], **datos))


# ============================================================ lados que no se ven
def cubierto(p, lado, otros):
    """Si el lado de p lo tapa entero algun bloque de otros (que no sea mas bajo que p)."""
    x0, z0, x1, z1 = p["x0"], p["z0"], p["x1"], p["z1"]
    if lado in ("x0", "x1"):
        x = x0 - 32 if lado == "x0" else x1 + 32
        puntos = [(x, z) for z in range(z0 + 32, z1, 64)]
    else:
        z = z0 - 32 if lado == "z0" else z1 + 32
        puntos = [(x, z) for x in range(x0 + 32, x1, 64)]
    return all(any(q["x0"] <= x < q["x1"] and q["z0"] <= z < q["z1"] and q["h"] <= p["h"] for q in otros)
               for x, z in puntos)


# la pista no tiene ni un lado a la vista (todo el borde es seto, muro, baranda u otro trozo de pista)
for p in pista:
    p["sin_lados"] = ["x0", "x1", "z0", "z1"]
macizos = [b for b in bloques if b["nombre"].startswith(("seto", "muro", "baranda"))]
for p in macizos:
    p["sin_lados"] = [l for l in ("x0", "x1", "z0", "z1") if cubierto(p, l, [q for q in macizos if q is not p])]
bloques = pista + bloques

cielo = dict(cenit=[40, 30, 110], horizonte=[250, 170, 120], nadir=[60, 40, 90])    # atardecer magico


def medir():
    """(bytes del .INO con la pista, el cielo y el carrito, bytes que caben)."""
    import kart_modelo
    maximo = os.path.getsize(os.path.join(n.disco.RAIZ, "extraido", "GRAPHICS", "HUB", "H1W.INO"))
    try:
        n.nf.construir_bytes(n.nodo_de(bloques), n.CONSERVAR_PLAT, sin_objetos=True, paredes=True, callar=True,
                             reemplazos={n.INDICE_CIELO: n.nodo_cielo(dict(n.CIELO_DEFECTO, **cielo)),
                                         1: kart_modelo.armar, 11: kart_modelo.vacio, 17: kart_modelo.rival,
                                           20: kart_modelo.caja, 21: kart_modelo.pocion, 22: kart_modelo.bola,
                                           18: kart_modelo.reloj, 23: kart_modelo.llama, 24: kart_modelo.cristal})
    except ValueError:
        pass
    return n.nf.ULTIMO["tamano"], maximo


CHAFLAN = 600                    # cuanto se recorta cada curva en la linea del rival (sin salirse de la pista)


def ruta_rival():
    """La linea por donde corre el rival: el centro de la pista desde la meta, con cada curva cortada en diagonal
    (CHAFLAN antes y despues de la esquina). Devuelve [(x, z, rumbo, ux, uz, d)]: cada tramo con su rumbo, su
    direccion de largo 4096 y la distancia recorrida al empezarlo; y el largo de la vuelta."""
    import math
    esquinas = [B, C, D, E, F, G, H, A]
    puntos = [(1024, -896)]
    for i, c in enumerate(esquinas):
        ant = puntos[-1] if i == 0 else esquinas[i - 1]
        sig = esquinas[i + 1] if i + 1 < len(esquinas) else (1024, -896)
        for o in (ant, sig):
            lx, lz = o[0] - c[0], o[1] - c[1]
            lon = math.hypot(lx, lz)
            p = (round(c[0] + lx / lon * CHAFLAN), round(c[1] + lz / lon * CHAFLAN))
            puntos.append(p)
    tramos, d = [], 0
    for i, (x, z) in enumerate(puntos):
        nx, nz = puntos[(i + 1) % len(puntos)]
        lon = math.hypot(nx - x, nz - z)
        rumbo = round(math.atan2(nx - x, nz - z) * 4096 / (2 * math.pi)) & 0xFFF
        tramos.append((x, z, rumbo, round((nx - x) / lon * 4096), round((nz - z) / lon * 4096), d))
        d += round(lon)
    return tramos, d


def escribir_h(ruta):
    with open(ruta, "w", encoding="utf-8", newline="\n") as f:
        f.write("/* Generado por scripts/mapa_kart.py: no editar a mano. La pista de SABRINA KART (niveles/kart.json). */\n")
        f.write("/* Puntos de control en el orden de la carrera (el 0 es la meta): x0, z0, x1, z1, x y z donde se\n"
                " * reaparece, y el rumbo del kart ahi. Turbos: x0, z0, x1, z1. Cajas de hechizo: x, z. */\n")
        f.write(f"#define KART_NCP {len(cp)}\n#define KART_NTURBOS {len(turbos)}\n#define KART_NCAJAS {len(cajas)}\n")
        f.write(f"#define KART_SALIDA_X {n.SALIDA[0]}\n#define KART_SALIDA_Z {n.SALIDA[1]}\n")
        f.write(f"#define KART_SUELO_HIERBA {MURO_H}\n#define KART_FONDO 300\n")
        f.write("static const s16 kart_cp[KART_NCP][7] = {\n")
        for c in cp:
            f.write("    {" + ", ".join(str(v) for v in c) + "},\n")
        f.write("};\nstatic const s16 kart_turbos[KART_NTURBOS][4] = {\n")
        for t in turbos:
            f.write("    {" + ", ".join(str(v) for v in t) + "},\n")
        f.write("};\nstatic const s16 kart_cajas[KART_NCAJAS][2] = {\n")
        for t in cajas:
            f.write("    {" + ", ".join(str(v) for v in t) + "},\n")
        f.write("};\n")
        tramos, largo = ruta_rival()
        f.write("/* La linea del rival (ruta_rival en mapa_kart.py): cada tramo x, z, rumbo y direccion (ux, uz de largo\n"
                " * 4096); kart_ruta_d es la distancia al empezar cada tramo y KART_RUTA_LARGO la de una vuelta. */\n")
        f.write(f"#define KART_RUTA_N {len(tramos)}\n#define KART_RUTA_LARGO {largo}\n")
        f.write("static const s16 kart_ruta[KART_RUTA_N][5] = {\n")
        for t in tramos:
            f.write("    {" + ", ".join(str(v) for v in t[:5]) + "},\n")
        f.write("};\nstatic const s32 kart_ruta_d[KART_RUTA_N] = {" + ", ".join(str(t[5]) for t in tramos) + "};\n")


if __name__ == "__main__":
    errores, avisos = n.validar(bloques)
    print(len(bloques), "bloques; errores:", errores)
    for a in avisos:
        print("aviso:", a)
    tam, maximo = medir()
    print(f"tamano del .INO (con el carrito): {tam} de {maximo} bytes ({100 * tam / maximo:.1f} %)")
    if not errores and tam <= maximo:
        ruta = os.path.join(n.NIVELES, "kart.json")
        n.guardar(bloques, ruta, cielo)
        print("escrito", ruta)
        h = os.path.join(n.disco.RAIZ, "decomp", "src", "objetos", "kart_pista.h")
        escribir_h(h)
        print("escrito", h)
