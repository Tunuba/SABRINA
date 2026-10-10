"""Genera niveles\\kart.json y decomp\\src\\objetos\\kart_pista.h: la pista de SABRINA KART, la Copa del Tiempo.

Un circuito cerrado de carreras hecho con los bloques del motor (nivel_plataformas.py) y las texturas del juego,
pensado como si fuera un nivel escondido de A Twitch in Time: cada tramo es una de las epocas del juego.

- Recta de Greendale (la salida): marmol, el arco de meta con el letrero y el primer turbo.
- Curva y recta de Egipto: arena dorada, muros de jeroglificos, obeliscos y la fila de cajas de hechizo.
- El Oeste: tablones y el puente sobre el rio Sweetwater.
- La Edad de Piedra: la horquilla de piedra que entra al centro del circuito y vuelve a salir.
- El Vortice del tiempo: el remolino azul de la ultima recta, con otra fila de cajas y el ultimo turbo.

Por dentro, el centro del circuito son setos macizos de hierba (450 de alto, mas de lo que Sabrina sube sola) y
por fuera un muro igual de alto: no hay por donde salirse. Sin rampas ni saltos. Los dos puentes cruzan el rio
entre barandas.
La salida del juego (128, -896) queda en la recta de Greendale, antes de la linea de meta.

El .h dice al codigo del kart (decomp/src/objetos/camara_g08.c, SABRINA_KART) donde estan los puntos de control
(en orden, el 0 es la meta), los turbos y las cajas. Cuadrados en unidades del modelo (x0, z0, x1, z1).

Uso: python mapa_kart.py      (escribe los dos archivos y dice cuanto ocupa el .INO)
"""
import os

import nivel_plataformas as n

# texturas (galeria del editor, PALETA en nivel_plataformas)
PIEDRA, VETEADA, LISA, PIEDRA3, PIEDRA4, PIEDRA5 = 16, 1, 13, 67, 71, 98
MARMOL, AGUA, LADRILLO, TEJAS, TABLONES = 69, 66, 88, 96, 97
VALLA, HIERBA, ORO, AZULEJO, GLIFO = 100, 81, 77, 78, 79
PUERTA_ORO, JEROGLIFOS, MURAL, BANDA_ORO = 90, 76, 75, 70
TELA_ROJA, REMOLINO, LETRERO, LETRERO2 = 106, 101, 94, 95
PANELES = 110

ANCHO = 1536                     # ancho de la pista
MEDIO = ANCHO // 2
HIERBA_H = 96                    # la hierba queda 96 por debajo de la pista
MURO_H = 450                     # alto de los muros: con menos de ~370 Sabrina se sube sola
RIO = (8320, 8704)               # el rio Sweetwater cruza todo el mapa de norte a sur
GRANDE = (-4864, -2560, 11904, 8832)   # lo que cubre la hierba

# el recorrido (en el sentido de la carrera): Greendale al este, Egipto al sur, el Oeste al oeste, la horquilla de
# piedra hacia el centro y el vortice de vuelta a la salida
A, B, C, D = (-3072, -896), (10240, -896), (10240, 7168), (6144, 7168)
E, F, G, H = (6144, 3584), (2048, 3584), (2048, 7168), (-3072, 7168)

bloques = []
pista = []                       # los trozos de pista (para levantar los muros de dentro)
cp, turbos, cajas = [], [], []


def bloque(nombre, x0, z0, x1, z1, h=0, **kw):
    """Un trozo de pista plano a altura h (positiva = abajo, como en el juego)."""
    kw.setdefault("prof", HIERBA_H + 40)
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 1024)
    kw.setdefault("tex_lado", PIEDRA)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, h, **kw))
    pista.append(bloques[-1])


def pared(nombre, x0, z0, x1, z1, alto=MURO_H, base=0, **kw):
    kw.setdefault("color", (110, 105, 100))
    kw.setdefault("tex_tapa", PIEDRA)
    kw.setdefault("tex_lado", PIEDRA)
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 1024)
    extra = kw.pop("extra", HIERBA_H)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -(base + alto), pared=True, prof=alto + extra, **kw))


def esquina(p):
    return p[0] - MEDIO, p[1] - MEDIO, p[0] + MEDIO, p[1] + MEDIO


def punto_control(x0, z0, x1, z1, rumbo):
    """rumbo: hacia donde mira el kart al reaparecer ahi (0 = +z, 0x400 = +x, 0x800 = -z, 0xC00 = -x)."""
    cp.append((x0, z0, x1, z1, (x0 + x1) // 2, (z0 + z1) // 2, rumbo))


# ============================================================ los setos y el rio
# Todo lo que no es pista dentro del muro de fuera: el centro del circuito partido por el rio, los dos lados de la
# horquilla y el hueco del sur entre las curvas G y D. Son setos macizos: sus lados son los muros de dentro.
color_hierba = (78, 112, 64)
for nombre, x0, z0, x1, z1 in (("hierba_centro_o", A[0] + MEDIO, A[1] + MEDIO, RIO[0], E[1] - MEDIO),
                               ("hierba_centro_e", RIO[1], A[1] + MEDIO, B[0] - MEDIO, E[1] - MEDIO),
                               ("hierba_oeste", A[0] + MEDIO, E[1] - MEDIO, F[0] - MEDIO, G[1] - MEDIO),
                               ("hierba_este_o", E[0] + MEDIO, E[1] - MEDIO, RIO[0], C[1] - MEDIO),
                               ("hierba_este_e", RIO[1], E[1] - MEDIO, B[0] - MEDIO, C[1] - MEDIO),
                               ("hierba_horquilla", F[0] + MEDIO, E[1] + MEDIO, E[0] - MEDIO, C[1] + MEDIO)):
    pared(nombre, x0, z0, x1, z1, color=color_hierba, tex_tapa=HIERBA, tex_lado=VALLA)
bloques.append(n.nueva("rio", RIO[0], A[1] - MEDIO, RIO[1], C[1] + MEDIO, 900, color=(70, 110, 140), tex_tapa=AGUA,
                       tex_lado=PIEDRA, prof=200, paso=512, paso_lado=1024, pared=True))
# barandas de los puentes del lado del rio que no tiene seto
for nombre, z0 in (("baranda_n", A[1] + MEDIO), ("baranda_s", C[1] - MEDIO - 256)):
    pared(nombre, RIO[0], z0, RIO[1], z0 + 256, color=(120, 100, 80), tex_tapa=TABLONES, tex_lado=TABLONES, extra=900)

# ============================================================ recta de Greendale (la salida)
GREEN = dict(color=(150, 150, 170), tex_tapa=MARMOL)
bloque("salida_a", A[0] + MEDIO, A[1] - MEDIO, RIO[0], A[1] + MEDIO, **GREEN)
bloque("puente_rio", RIO[0], A[1] - MEDIO, RIO[1], A[1] + MEDIO, color=(120, 100, 80), tex_tapa=TABLONES,
       tex_lado=TABLONES)
bloque("salida_b", RIO[1], A[1] - MEDIO, B[0] - MEDIO, A[1] + MEDIO, **GREEN)
punto_control(768, A[1] - MEDIO, 1280, A[1] + MEDIO, 0x400)            # 0: la meta
# arco de meta: dos columnas fuera de la pista y el letrero por encima
pared("meta_col_n", 768, A[1] - MEDIO - 512, 1280, A[1] - MEDIO - 256, alto=900, color=(150, 130, 90),
      tex_tapa=ORO, tex_lado=BANDA_ORO, paso_lado=512)
pared("meta_col_s", 768, A[1] + MEDIO + 64, 1280, A[1] + MEDIO + 320, alto=900, color=(150, 130, 90),
      tex_tapa=ORO, tex_lado=BANDA_ORO, paso_lado=512)
bloques.append(n.nueva("meta_letrero", 768, A[1] - MEDIO - 512, 1280, A[1] + MEDIO + 320, -1100, color=(150, 140, 120),
                       tex_tapa=TELA_ROJA, tex_lado=LETRERO, prof=260, paso=512, paso_lado=512, techo=True,
                       pared=True))
turbos.append((4096, A[1] - 384, 4608, A[1] + 384))

# ============================================================ Egipto: curva B y recta hacia el sur
EGIPTO = dict(color=(170, 150, 105), tex_tapa=ORO, tex_lado=JEROGLIFOS)
bloque("curva_b", *esquina(B), **EGIPTO)
bloque("egipto", B[0] - MEDIO, B[1] + MEDIO, B[0] + MEDIO, C[1] - MEDIO, **EGIPTO)
punto_control(B[0] - MEDIO, 2560, B[0] + MEDIO, 3072, 0)               # 1
turbos.append((B[0] - 256, 512, B[0] + 256, 1024))
for i, x in enumerate((B[0] - 640, B[0] - 128, B[0] + 384)):
    cajas.append((x, 4608, x + 256, 4864))
# obeliscos fuera del muro este
for i, z in enumerate((-256, 1792, 3840, 5888)):
    pared(f"obelisco{i}", 11392, z, 11648, z + 256, alto=1400, color=(180, 160, 110), tex_tapa=ORO,
          tex_lado=JEROGLIFOS, paso_lado=512)

# ============================================================ el Oeste: curva C y el puente del rio
OESTE = dict(color=(140, 110, 85), tex_tapa=TABLONES, tex_lado=VALLA)
bloque("curva_c", *esquina(C), **OESTE)
bloque("oeste", RIO[1], C[1] - MEDIO, C[0] - MEDIO, C[1] + MEDIO, **OESTE)
bloque("puente_oeste", RIO[0], C[1] - MEDIO, RIO[1], C[1] + MEDIO, color=(120, 100, 80), tex_tapa=TABLONES,
       tex_lado=TABLONES)
bloque("llegada", D[0] + MEDIO, C[1] - MEDIO, RIO[0], C[1] + MEDIO, **OESTE)
punto_control(7168, C[1] - MEDIO, 7680, C[1] + MEDIO, 0xC00)           # 2

# ============================================================ Edad de Piedra: la horquilla D-E-F-G
PIEDRA_K = dict(color=(135, 128, 118), tex_tapa=PIEDRA3, tex_lado=PIEDRA)
bloque("curva_d", *esquina(D), **PIEDRA_K)
bloque("piedra_sube", D[0] - MEDIO, E[1] + MEDIO, D[0] + MEDIO, D[1] - MEDIO, **PIEDRA_K)
bloque("curva_e", *esquina(E), **PIEDRA_K)
bloque("piedra_cruza", F[0] + MEDIO, E[1] - MEDIO, E[0] - MEDIO, E[1] + MEDIO, **PIEDRA_K)
punto_control(3584, E[1] - MEDIO, 4096, E[1] + MEDIO, 0xC00)           # 3
bloque("curva_f", *esquina(F), **PIEDRA_K)
bloque("piedra_baja", F[0] - MEDIO, F[1] + MEDIO, F[0] + MEDIO, G[1] - MEDIO, **PIEDRA_K)
turbos.append((F[0] - 256, 4864, F[0] + 256, 5376))
# menhires en el centro de la horquilla
for i, (x, z) in enumerate(((3328, 4864), (4352, 5376), (3840, 6144))):
    pared(f"menhir{i}", x, z, x + 384, z + 384, alto=1000, color=(120, 115, 105), tex_tapa=PIEDRA,
          tex_lado=VETEADA, paso_lado=512)

# ============================================================ el Vortice del tiempo: G-H-A
VORTICE = dict(color=(110, 120, 175), tex_tapa=REMOLINO, tex_lado=AZULEJO)
bloque("curva_g", *esquina(G), **VORTICE)
bloque("vortice", H[0] + MEDIO, G[1] - MEDIO, G[0] - MEDIO, G[1] + MEDIO, **VORTICE)
punto_control(-1024, G[1] - MEDIO, -512, G[1] + MEDIO, 0xC00)          # 4
for i, z in enumerate((G[1] - 640, G[1] - 128, G[1] + 384)):
    cajas.append((256, z, 512, z + 256))
bloque("curva_h", *esquina(H), **VORTICE)
bloque("vortice_norte", H[0] - MEDIO, A[1] + MEDIO, H[0] + MEDIO, H[1] - MEDIO, **VORTICE)
punto_control(H[0] - MEDIO, 2560, H[0] + MEDIO, 3072, 0x800)            # 5
turbos.append((H[0] - 256, 4096, H[0] + 256, 4608))
bloque("curva_a", *esquina(A), **GREEN)

# ============================================================ el muro de fuera
X0, Z0 = A[0] - MEDIO, A[1] - MEDIO           # borde de fuera de la pista
X1, Z1 = B[0] + MEDIO, C[1] + MEDIO
pared("muro_n", X0 - 256, Z0 - 256, X1 + 256, Z0, tex_lado=LADRILLO)
pared("muro_s", X0 - 256, Z1, X1 + 256, Z1 + 256, tex_lado=TABLONES)
pared("muro_o", X0 - 256, Z0, X0, Z1, tex_lado=AZULEJO)
pared("muro_e", X1, Z0, X1 + 256, Z1, tex_lado=JEROGLIFOS)

# los turbos y las cajas se ven como losas un poco altas (el kart las pisa y sigue)
for i, (x0, z0, x1, z1) in enumerate(turbos):
    bloques.append(n.nueva(f"turbo{i}", x0, z0, x1, z1, -64, color=(150, 170, 255), tex_tapa=REMOLINO,
                           tex_lado=BANDA_ORO, prof=64, paso=512, paso_lado=512))
for i, (x0, z0, x1, z1) in enumerate(cajas):
    bloques.append(n.nueva(f"caja{i}", x0, z0, x1, z1, -96, color=(200, 170, 90), tex_tapa=GLIFO,
                           tex_lado=PUERTA_ORO, prof=96, paso=256, paso_lado=256))

cielo = dict(cenit=[40, 30, 110], horizonte=[250, 170, 120], nadir=[60, 40, 90])    # atardecer magico


def escribir_h(ruta):
    with open(ruta, "w", encoding="utf-8", newline="\n") as f:
        f.write("/* Generado por scripts/mapa_kart.py: no editar a mano. La pista de SABRINA KART (niveles/kart.json). */\n")
        f.write("/* Puntos de control en el orden de la carrera (el 0 es la meta): x0, z0, x1, z1, x y z donde se\n"
                " * reaparece, y el rumbo del kart ahi. Turbos y cajas de hechizo: x0, z0, x1, z1. */\n")
        f.write(f"#define KART_NCP {len(cp)}\n#define KART_NTURBOS {len(turbos)}\n#define KART_NCAJAS {len(cajas)}\n")
        f.write(f"#define KART_SALIDA_X {n.SALIDA[0]}\n#define KART_SALIDA_Z {n.SALIDA[1]}\n")
        f.write(f"#define KART_SUELO_HIERBA {HIERBA_H}\n#define KART_FONDO {HIERBA_H + 400}\n")
        f.write("static const s16 kart_cp[KART_NCP][7] = {\n")
        for c in cp:
            f.write("    {" + ", ".join(str(v) for v in c) + "},\n")
        f.write("};\nstatic const s16 kart_turbos[KART_NTURBOS][4] = {\n")
        for t in turbos:
            f.write("    {" + ", ".join(str(v) for v in t) + "},\n")
        f.write("};\nstatic const s16 kart_cajas[KART_NCAJAS][4] = {\n")
        for t in cajas:
            f.write("    {" + ", ".join(str(v) for v in t) + "},\n")
        f.write("};\n")


if __name__ == "__main__":
    errores, avisos = n.validar(bloques)
    print(len(bloques), "bloques; errores:", errores)
    for a in avisos:
        print("aviso:", a)
    tam, maximo = n.tamano_ino(bloques, cielo)
    print(f"tamano del .INO: {tam} de {maximo} bytes ({100 * tam / maximo:.1f} %)")
    if not errores and tam <= maximo:
        ruta = os.path.join(n.NIVELES, "kart.json")
        n.guardar(bloques, ruta, cielo)
        print("escrito", ruta)
        h = os.path.join(n.disco.RAIZ, "decomp", "src", "objetos", "kart_pista.h")
        escribir_h(h)
        print("escrito", h)
