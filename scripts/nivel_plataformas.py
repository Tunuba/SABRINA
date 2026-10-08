"""Motor de los niveles de plataformas: el HUB (H1W) vaciado y reemplazado por plataformas flotantes en un cuarto
negro (lo usa editor_nivel.py). Un nivel es una lista de plataformas guardada en niveles\\*.json; este modulo la
valida, la convierte en geometria y arma el disco. Usa el mismo mecanismo que mini_nivel.py
(nivel_fantasma.construir_bytes).

Una plataforma es un dict: nombre, x0, z0, x1, z1 (rectangulo en unidades del modelo; Sabrina aparece en
(128, -896)), h (altura de la tapa; -Y es arriba, asi que "mas alto" = mas negativo) y color [r, g, b].

Medido con observar_fantasma.py: Sabrina salta ~380 unidades de alto pero corriendo solo avanza ~150-200 de
distancia (400 a toda carrera), asi que los avisos de 'validar' marcan huecos de mas de 256 y subidas de mas de
250. Si cae, reaparece en (128, 0, -896): ahi tiene que haber una plataforma a altura 0.
Con UP Sabrina avanza hacia +X +Z (camara en diagonal).

Reglas que cumple cada plataforma (las mismas del mini nivel):
- la tapa se parte en los multiplos de 256 (512 donde esta la salida) mas sus propios bordes: como la celda de
  colision mide 1024, ningun triangulo cruza el borde de dos celdas;
- solo las tapas (triangulos horizontales) entran en la colision; las paredes laterales son solo dibujo y no
  llevan fondo (seria un segundo suelo);
- la salida no puede caer justo sobre un borde o una diagonal de cuadro (caso limite de PuntoEnTriangulo: Sabrina
  se cae); 'validar' lo detecta;
- dos plataformas pueden estar una sobre otra (pisarse en planta) si sus tapas difieren al menos SEPARACION_MIN: el
  juego (func_8003AF9C) elige el triangulo mas cercano POR DEBAJO de un punto algo mas alto que los pies de Sabrina
  (medido: ~360), asi que se camina sobre la de abajo solo si la de arriba esta mas de ~370 por encima (con menos,
  Sabrina "sube" a la de arriba en la zona comun, como un escalon), se sube saltando desde abajo atravesando la de
  arriba (no hay techo) hasta ~700 de separacion, y se cae sobre la de arriba si se viene de mas alto. Las
  paredes de la de arriba solo cuelgan hasta la de abajo (profundidades()).

Uso:
    python nivel_plataformas.py disco [nivel.json]   arma disco\\sabrina_plataformas.cue (por defecto niveles\\plataformas.json)
    python nivel_plataformas.py ver [nivel.json]     lo arma, lo arranca sin ventana, teletransporta a Sabrina a cada
                                                     plataforma, comprueba que pisa en la altura esperada y saca capturas
"""
import json
import math
import os
import struct
import sys

import disco
import nivel_fantasma as nf

NIVELES = os.path.join(disco.RAIZ, "niveles")
NIVEL_POR_DEFECTO = os.path.join(NIVELES, "plataformas.json")
SALIDA = (128, -896)                 # donde aparece Sabrina (y reaparece al caer), a altura 0
LIMITE = 30000                       # coordenadas del modelo: int16 de los vertices y cuadricula de colision
PROFUNDO = 768                       # cuanto cuelga cada plataforma por debajo de su tapa (solo dibujo)
PASO_PARED = nf.SPACING              # cuadros de 512 en las paredes (un triangulo muy grande no se dibuja)
SALTO_HUECO, SALTO_SUBIDA = 256, 250  # lo que se considera alcanzable (avisos de validar)
SEPARACION_MIN = 64                  # dos tapas que se pisan en planta tienen que diferir al menos esto de altura
AGARRE = 370                         # medido en el juego: una tapa hasta ~360 por encima de los pies de Sabrina la
                                     # sube a ella (mismo cuadro de planta); a 376 o mas ya no
SEPARACION_AVISO = AGARRE + 10       # con menos separacion la de abajo no se puede pisar en la zona comun
SALTO_APILADA = 700                  # subiendo desde abajo: salto (~380) + agarre (~360)
CONSERVAR_PLAT = {1, 2, 11, 12, 19}  # Sabrina, su sombra y el cielo (ver mini_nivel.py)


def rutas(nombre):
    return (os.path.join(disco.DISCO, f"sabrina_{nombre}.cue"),
            os.path.join(disco.DISCO, f"sabrina_{nombre} (Track 01).bin"))


CUE_PLAT, PISTA_PLAT = rutas("plataformas")


# ---------------------------------------------------------------- datos

def nueva(nombre, x0, z0, x1, z1, h, color=(128, 128, 128)):
    return dict(nombre=nombre, x0=min(x0, x1), z0=min(z0, z1), x1=max(x0, x1), z1=max(z0, z1), h=h,
                color=list(color))


def cargar(ruta=NIVEL_POR_DEFECTO):
    with open(ruta, encoding="utf-8") as f:
        datos = json.load(f)
    return [nueva(p["nombre"], p["x0"], p["z0"], p["x1"], p["z1"], p["h"], p["color"])
            for p in datos["plataformas"]]


def guardar(plats, ruta):
    """Una plataforma por linea, para que el diff de git se lea."""
    os.makedirs(os.path.dirname(ruta), exist_ok=True)
    lineas = ",\n".join("  " + json.dumps(p, ensure_ascii=False) for p in plats)
    with open(ruta, "w", encoding="utf-8") as f:
        f.write('{"plataformas": [\n' + lineas + "\n]}\n")


def contiene_salida(p):
    return p["x0"] <= SALIDA[0] <= p["x1"] and p["z0"] <= SALIDA[1] <= p["z1"]


# ---------------------------------------------------------------- geometria

def cortes(a, b, paso):
    """Cortes de la rejilla de una tapa entre a y b: los bordes y todos los multiplos de 'paso' de por medio. Asi
    ningun cuadro cruza un multiplo de 1024 (borde de celda de colision) aunque a o b no sean multiplos de 'paso'."""
    return [a] + [c for c in range((a // paso + 1) * paso, b, paso)] + [b]


def paso_tapa(p):
    return 512 if contiene_salida(p) else 256


def salida_en_limite(p):
    """True si la salida cae justo en un borde de cuadro o en la diagonal (p10-p01) del cuadro de la tapa."""
    if not contiene_salida(p):
        return False
    cu, cv = cortes(p["x0"], p["x1"], paso_tapa(p)), cortes(p["z0"], p["z1"], paso_tapa(p))
    sx, sz = SALIDA
    if sx in cu or sz in cv:
        return True
    xa = max(c for c in cu if c < sx)
    xb = min(c for c in cu if c > sx)
    za = max(c for c in cv if c < sz)
    zb = min(c for c in cv if c > sz)
    # diagonal de (xb, za) a (xa, zb)
    return (sx - xb) * (zb - za) - (sz - za) * (xa - xb) == 0


def se_pisan(a, b):
    return a["x0"] < b["x1"] and b["x0"] < a["x1"] and a["z0"] < b["z1"] and b["z0"] < a["z1"]


def cola_cara(nx, ny, nz):
    """Los 6 bytes finales de un triangulo del .INO (tipo u16, normal x/y/z, ejes), como en los triangulos reales
    del HUB: la normal de salida (hacia donde se ve la cara) en bytes con escala 126 (-Y = 130), tipo 0 en el suelo y 1 en
    las paredes, y los dos ejes que mira PuntoEnTriangulo (8 = x,z en el suelo; 4 = x,y en paredes que miran a Z; 9 = y,z
    en las que miran a X). Con la normal horizontal el suelo (func_8003A524) descarta el triangulo, asi que una pared
    no hace de suelo; el choque de lado lo usa de frente."""
    suelo = ny != 0
    return (0 if suelo else 1, 0, round(nx * 126) & 255, round(ny * 126) & 255, round(nz * 126) & 255,
            8 if suelo else 4 if nz != 0 else 9)


def profundidades(plats):
    """Cuanto baja cada bloque desde su tapa: su campo 'prof' si lo tiene; si no, PROFUNDO o menos si debajo (se
    pisan en planta) hay otra plataforma, para que no la atraviese."""
    res = []
    for p in plats:
        if p.get("prof"):
            res.append(p["prof"])
            continue
        debajo = [q["h"] - p["h"] for q in plats if q is not p and se_pisan(p, q) and q["h"] > p["h"]]
        res.append(min([PROFUNDO] + debajo))
    return res


def agregar_plataforma(verts, tris, p, textura, uv, cola, profundo=PROFUNDO):
    """La tapa (diagonal p10-p01) y las 4 paredes de una plataforma. La cara que se ve es la de normal
    cross(b - a, c - a); cada cara lleva ejes u, v con cross(u, v) hacia afuera (en la PS1 -Y es arriba)."""
    x0, z0, x1, z1, h = p["x0"], p["z0"], p["x1"], p["z1"], p["h"]
    r, g, b = p["color"]
    lx, lz = x1 - x0, z1 - z0
    X, Y, Z = (1, 0, 0), (0, 1, 0), (0, 0, 1)
    sombra = lambda k: (min(255, r * k // 128), min(255, g * k // 128), min(255, b * k // 128))
    caras = [  # origen, u, largo de u, v, largo de v, color, normal de salida
        ((x0, h, z0), X, lx, Z, lz, sombra(128), (0, -1, 0)),           # tapa: cross(X, Z) = -Y
        ((x1, h, z0), Y, profundo, Z, lz, sombra(80), (1, 0, 0)),       # +X: cross(Y, Z) = +X
        ((x0, h, z0), Z, lz, Y, profundo, sombra(80), (-1, 0, 0)),      # -X: cross(Z, Y) = -X
        ((x0, h, z1), X, lx, Y, profundo, sombra(100), (0, 0, 1)),      # +Z: cross(X, Y) = +Z
        ((x0, h, z0), Y, profundo, X, lx, sombra(100), (0, 0, -1)),     # -Z: cross(Y, X) = -Z
    ]
    for n, (o, u, lu, v, lv, color, normal) in enumerate(caras):
        cola_c = cola_cara(*normal)
        if n == 0:     # la tapa: cortes en los multiplos de 'paso' (que lo son de 1024/4) mas los bordes
            cu = [c - x0 for c in cortes(x0, x1, paso_tapa(p))]
            cv = [c - z0 for c in cortes(z0, z1, paso_tapa(p))]
        else:
            nu, nv = max(1, round(lu / PASO_PARED)), max(1, round(lv / PASO_PARED))
            cu, cv = [lu * i // nu for i in range(nu + 1)], [lv * j // nv for j in range(nv + 1)]
        nu, nv = len(cu) - 1, len(cv) - 1
        base = len(verts)
        for i in range(nu + 1):
            for j in range(nv + 1):
                q = [o[k] + u[k] * cu[i] + v[k] * cv[j] for k in range(3)]
                verts.append(struct.pack("<3hh3Bx", *q, 0, *color))
        for i in range(nu):
            for j in range(nv):
                a, b_ = base + i * (nv + 1) + j, base + (i + 1) * (nv + 1) + j
                c, d = b_ + 1, a + 1                       # p00, p10, p11, p01
                tris.append((a, b_, d, textura) + uv + cola_c)
                tris.append((b_, c, d, textura) + uv + cola_c)


def nodo_de(plats):
    def armar(nodo_original):
        """Un nodo con todas las plataformas. Textura, UV y tipo de superficie se copian de un triangulo de piso
        real del HUB."""
        piso = next(t for t in nodo_original["tris"] if t[10] in (0, 1) and t[15] == 8)
        textura, uv, cola = piso[3], tuple(piso[4:10]), tuple(piso[10:16])
        verts, tris = [], []
        for p, prof in zip(plats, profundidades(plats)):
            agregar_plataforma(verts, tris, p, textura, uv, cola, prof)
        return dict(nombre="PLATAF\0", matriz=nodo_original["matriz"], tras=nodo_original["tras"],
                    hijos=[], tris=tris, verts=verts)
    return armar


# ---------------------------------------------------------------- validacion

def hueco(a, b):
    """Distancia horizontal entre los rectangulos de dos plataformas (0 si se tocan)."""
    dx = max(b["x0"] - a["x1"], a["x0"] - b["x1"], 0)
    dz = max(b["z0"] - a["z1"], a["z0"] - b["z1"], 0)
    return math.hypot(dx, dz)


def validar(plats):
    """(errores, avisos). Con errores el nivel no se puede armar o Sabrina se cae; los avisos son solo
    jugabilidad (plataformas que no se alcanzan con el salto medido)."""
    errores, avisos = [], []
    if not plats:
        return ["no hay plataformas"], []
    for p in plats:
        n = p["nombre"]
        if p["x1"] - p["x0"] < 256 or p["z1"] - p["z0"] < 256:
            errores.append(f"{n}: mide menos de 256 de lado")
        if max(abs(p[k]) for k in ("x0", "z0", "x1", "z1")) > LIMITE or abs(p["h"]) > LIMITE - PROFUNDO:
            errores.append(f"{n}: se sale del mapa (maximo {LIMITE})")
    for i, a in enumerate(plats):
        for b in plats[i + 1:]:
            if se_pisan(a, b):
                d = abs(a["h"] - b["h"])
                if d < SEPARACION_MIN:
                    errores.append(f"{a['nombre']} y {b['nombre']} se pisan en planta y sus alturas difieren solo "
                                   f"{d}: separalas al menos {SEPARACION_MIN} (una sobre otra)")
                elif d < SEPARACION_AVISO:
                    avisos.append(f"{a['nombre']} y {b['nombre']}: una sobre otra con solo {d} de separacion; "
                                  f"en la zona comun Sabrina sube sola a la de arriba (hacen falta {SEPARACION_AVISO} "
                                  f"para poder pisar las dos)")
    inicio = [p for p in plats if contiene_salida(p) and p["h"] == 0]
    if not inicio:
        errores.append(f"ninguna plataforma a altura 0 cubre la salida {SALIDA}: Sabrina aparece en el vacio")
    for p in inicio:
        if salida_en_limite(p):
            errores.append(f"{p['nombre']}: la salida {SALIDA} cae justo en un borde o diagonal de cuadro; "
                           "mueve el borde de la plataforma")
    if errores:
        return errores, avisos
    # alcanzables desde la salida con un salto
    vistos, pila = set(), [i for i, p in enumerate(plats) if contiene_salida(p) and p["h"] == 0]
    while pila:
        i = pila.pop()
        if i in vistos:
            continue
        vistos.add(i)
        for j, q in enumerate(plats):
            if j in vistos:
                continue
            a_, b_ = plats[i], q
            sube = a_["h"] - b_["h"]               # > 0: b esta mas alto
            apilada = se_pisan(a_, b_)
            if (hueco(a_, b_) <= SALTO_HUECO and sube <= (SALTO_APILADA if apilada else SALTO_SUBIDA)):
                pila.append(j)
    for i, p in enumerate(plats):
        if i not in vistos:
            avisos.append(f"{p['nombre']}: no se alcanza desde la salida (hueco > {SALTO_HUECO} o subida > "
                          f"{SALTO_SUBIDA} desde todas las vecinas)")
    return errores, avisos


# ---------------------------------------------------------------- disco

def armar_disco(plats=None, nombre="plataformas"):
    """Arma disco\\sabrina_<nombre>.cue (siempre de cero). plats por defecto: niveles\\plataformas.json."""
    plats = cargar() if plats is None else plats
    errores, _ = validar(plats)
    if errores:
        raise ValueError("nivel invalido: " + "; ".join(errores))
    cue, pista = rutas(nombre)
    nuevo = nf.construir_bytes(nodo_de(plats), CONSERVAR_PLAT, sin_objetos=True, paredes=True)
    disco.parchar({"GRAPHICS\\HUB\\H1W.INO": nuevo}, pista)
    disco.cue_mod(cue, pista)
    return cue


P_SABRINA = 0x8007CAF8     # puntero al objeto de Sabrina; +0x24 x, +0x28 y, +0x2C z (posicion = modelo * 256)


def punto_de_prueba(p):
    """Un punto dentro de la plataforma, cerca del centro y que (casi siempre) no cae en un borde de cuadro, donde
    Sabrina se cae."""
    cx = min((p["x0"] + p["x1"]) // 2 + 37, p["x1"] - 64)
    cz = min((p["z0"] + p["z1"]) // 2 + 53, p["z1"] - 64)
    return cx, cz


def suelo_esperado(plats, p, cx, cz):
    """La altura a la que Sabrina se queda al caer sobre p en (cx, cz): si hay tapas hasta AGARRE por encima en
    ese punto, el juego la sube a la mas alta de ellas (y asi sucesivamente)."""
    h = p["h"]
    while True:
        arriba = [q["h"] for q in plats if q["x0"] <= cx <= q["x1"] and q["z0"] <= cz <= q["z1"]
                  and 0 < h - q["h"] <= AGARRE - 10]
        if not arriba:
            return h
        h = min(arriba)


def teletransportar(e, p, plats=()):
    """Pone a Sabrina sobre la plataforma p (un poco por encima: cae sola) en un emulador ya arrancado. Si otra
    plataforma esta justo encima de ese punto, empieza casi a ras de suelo (si no, caeria sobre la de arriba)."""
    obj = int(float(e.eval(f"return rd32({P_SABRINA})")))
    cx, cz = punto_de_prueba(p)
    arriba = [q["h"] for q in plats if q is not p and q["h"] < p["h"] and q["x0"] <= cx <= q["x1"]
              and q["z0"] <= cz <= q["z1"]]
    sube = 30 if arriba else 200       # a ras de suelo: mas arriba entraria en la zona de agarre (AGARRE) de la de arriba
    e.eval(f"wr32({obj + 0x24},{cx * 256 & 0xFFFFFFFF})")
    e.eval(f"wr32({obj + 0x28},{(p['h'] - sube) * 256 & 0xFFFFFFFF})")
    e.eval(f"wr32({obj + 0x2C},{cz * 256 & 0xFFFFFFFF})")
    return obj


def ver(plats):
    """Teletransporta a Sabrina sobre cada plataforma, la deja caer y comprueba que se queda en la altura de la
    tapa (la colision de cada plataforma funciona), con una captura por plataforma."""
    from emu import Emu
    from explorar import CAP, recorrer
    from hoja import hoja
    ruta = armar_disco(plats)
    s = lambda v: v - (1 << 32) if v >= 1 << 31 else v
    capturas, fallos = [], 0
    with Emu(iso=ruta, log="nivel_plataformas.log", extra=("-fastboot",), puerto=8097) as e:
        recorrer(e, "plat_arranque", "w2160 CROSS w300 START w60 CROSS w240 w1300")
        for p in plats:
            obj = teletransportar(e, p, plats)
            e.esperar(90)
            y = s(int(float(e.eval(f"return rd32({obj + 0x28})")))) / 256
            esperada = suelo_esperado(plats, p, *punto_de_prueba(p))
            bien = abs(y - esperada) < 8
            fallos += not bien
            print(f"{p['nombre']:8s} esperada y={esperada:6d}  medida y={y:8.1f}  {'ok' if bien else 'FALLA'}", flush=True)
            r = os.path.join(CAP, f"plat_{p['nombre']}.png")
            e.captura(r)
            capturas.append(r)
    hoja(os.path.join(CAP, "plat_hoja.png"), 4, capturas)
    print("plataformas con fallo:", fallos)
    return fallos


if __name__ == "__main__":
    modo = sys.argv[1] if len(sys.argv) > 1 else ""
    nivel = cargar(sys.argv[2]) if len(sys.argv) > 2 else cargar()
    if modo == "disco":
        print("disco plataformas:", armar_disco(nivel))
    elif modo == "ver":
        ver(nivel)
    else:
        print(__doc__)
