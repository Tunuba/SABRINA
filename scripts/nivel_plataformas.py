"""Motor de los niveles propios: el HUB (H1W) vaciado y reemplazado por bloques (plataformas, paredes, rampas) en un
cuarto con cielo propio (lo usa editor_nivel.py). Un nivel es un JSON en niveles\\*.json; este modulo lo valida, lo
convierte en geometria y arma el disco. Usa el mismo mecanismo que mini_nivel.py (nivel_fantasma.construir_bytes).

Un bloque es un dict: nombre, x0, z0, x1, z1 (rectangulo en unidades del modelo; Sabrina aparece en (128, -896)), h
(altura de la tapa; -Y es arriba, asi que "mas alto" = mas negativo) y color [r, g, b] (128 = neutro). Opcionales:
  prof       cuanto baja el bloque desde su tapa (por defecto PROFUNDO, o hasta el bloque de debajo)
  tex_tapa, tex_lado    textura (indice de la tabla del .INO, ver tabla_texturas); por defecto TEX_DEFECTO
  h2, eje    rampa: la tapa sube de h (en x0 o z0) a h2 (en x1 o z1) a lo largo de eje "x" o "z"
  pared      true: es un muro o columna, no hace falta poder subirse (no da aviso de "no alcanzable")
  techo      true: el bloque tambien tiene cara inferior (se ve desde abajo; no hace de suelo): para salas cubiertas
  paso       tamano de los cuadros de la tapa y el techo (256 por defecto, 512 para suelos grandes)
Nivel = {"cielo": {...}, "plataformas": [bloques]}; el cielo son tres colores (cenit, horizonte, nadir).

Colision (medida en el juego, ver la memoria niveles-propios-cuadricula-colision):
- el suelo es el triangulo mas cercano POR DEBAJO de un punto ~360 sobre los pies de Sabrina (AGARRE): con una
  tapa a menos de ~370 encima, la sube; a mas, se pisan las dos. Se sube saltando desde abajo hasta ~700.
- las paredes (todos los lados) chocan: cada triangulo lleva su normal en bytes (x 126), tipo 1 y ejes (4 o 9) como los
  del HUB real (cola_de_triangulo); el suelo las descarta porque su normal es horizontal. El choque de lado solo mira
  la celda donde empieza el segmento, asi que cada pared va en todas las celdas cercanas (nivel_fantasma).
- la tapa se parte en los multiplos de 256 (512 donde esta la salida) mas sus bordes: como la celda de colision mide
  1024, ningun triangulo del suelo cruza el borde de dos celdas;
- la salida no puede caer justo sobre un borde o diagonal de cuadro (Sabrina se cae); 'validar' lo detecta.

Uso:
    python nivel_plataformas.py disco [nivel.json]   arma disco\\sabrina_plataformas.cue
    python nivel_plataformas.py ver [nivel.json]     lo arma, lo arranca sin ventana, teletransporta a Sabrina a cada
                                                     bloque, comprueba que pisa en la altura esperada y saca capturas
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
PROFUNDO = 768                       # cuanto baja un bloque por defecto desde su tapa
PASO_PARED = nf.SPACING              # cuadros de 512 en las paredes (un triangulo muy grande no se dibuja)
SALTO_HUECO, SALTO_SUBIDA = 256, 250  # lo que se considera alcanzable (avisos de validar)
SEPARACION_MIN = 64                  # dos tapas que se pisan en planta tienen que diferir al menos esto de altura
AGARRE = 370                         # medido: una tapa hasta ~360 por encima de los pies de Sabrina la sube a ella
SEPARACION_AVISO = AGARRE + 10       # con menos separacion la de abajo no se puede pisar en la zona comun
SALTO_APILADA = 700                  # subiendo desde abajo: salto (~380) + agarre (~360)
PENDIENTE_MAX = 0.70                 # tan del angulo de una rampa: mas de ~35 grados (normal.y > -0.78) Sabrina resbala
CONSERVAR_PLAT = {1, 2, 11, 12}      # Sabrina y su sombra; el cielo (19) lo reemplaza nodo_cielo
INDICE_CIELO = 19
TEX_DEFECTO = 16                     # piedra gris de 64x64
CIELO_DEFECTO = dict(cenit=[40, 70, 190], horizonte=[190, 215, 255], nadir=[25, 35, 90])
TEX_CIELO = 88                       # el cielo muestrea UN texel casi gris (UV degenerado, como el suelo del HUB) de
UV_CIELO = (12, 2)                   # esa textura, asi el color lo ponen solo los vertices (degradado liso)
TEXEL_CIELO = (131, 123, 123)        # su color: un vertice (c) muestra texel * c / 128, se compensa en nodo_cielo


def rutas(nombre):
    return (os.path.join(disco.DISCO, f"sabrina_{nombre}.cue"),
            os.path.join(disco.DISCO, f"sabrina_{nombre} (Track 01).bin"))


CUE_PLAT, PISTA_PLAT = rutas("plataformas")

# ---------------------------------------------------------------- texturas

_TEX = {}


def tabla_texturas():
    """{indice: (W, H)}: el mayor u y v que usa algun triangulo real de H1W.INO con esa textura (el tamano de la
    ventana). Los UV de un triangulo son relativos a la ventana (pagina, paleta y desplazamiento del registro)."""
    if not _TEX:
        import ino
        s = ino.leer_ino("H1W")

        def recorre(nodos):
            for n in nodos:
                yield n
                yield from recorre(n["hijos"])
        for _, nodos in s["modelos"]:
            for n in recorre(nodos):
                for t in n["tris"]:
                    w, h = _TEX.get(t[3], (0, 0))
                    _TEX[t[3]] = (max(w, *t[4:10:2]), max(h, *t[5:10:2]))
    return _TEX


# Texturas que sirven para arquitectura (indice, nombre). Las demas (zodiaco 2-14, ropa de Sabrina...) existen pero
# no se ofrecen en la galeria del editor.
PALETA = [(16, "Piedra"), (1, "Piedra veteada"), (13, "Piedra lisa"), (67, "Piedra 3"), (71, "Piedra 4"),
          (98, "Piedra 5"), (69, "Marmol azul"), (66, "Agua turquesa"), (88, "Ladrillo claro"), (96, "Tejas"),
          (97, "Tablones"), (108, "Madera puerta"), (110, "Madera paneles"), (109, "Arco de madera"),
          (100, "Valla verde"), (81, "Hierba"), (77, "Oro bloques"), (78, "Azulejo turquesa"),
          (79, "Glifo dorado"), (90, "Puerta dorada"), (76, "Jeroglifos"), (75, "Mural"), (70, "Banda dorada"),
          (73, "Cuentas"), (80, "Vendas"), (89, "Disco rojo"), (106, "Tela roja"), (107, "Tela verde"),
          (101, "Remolino azul"), (94, "Letrero"), (95, "Letrero 2"), (2, "Zodiaco 1"), (14, "Zodiaco balanza")]

_IMG, _COL, _OBJ = {}, {}, []


def imagen_textura(k):
    """La ventana de la textura k (PIL RGB de (W+1)x(H+1)) o None si su pagina no esta en el .TEX."""
    if k not in _IMG:
        import numpy as np
        from PIL import Image
        import ino
        from ino_obj import Texturas
        if not _OBJ:
            s = ino.leer_ino("H1W")
            _OBJ.append(Texturas("H1W", s["texturas"]))
        tex = _OBJ[0]
        tpage, clut, uo, vo = tex.de_triangulo(k)
        W, H = tabla_texturas().get(k, (63, 63))
        pag = tex.pagina(tpage, clut)
        if pag is None:
            _IMG[k] = None
        else:
            rgb, _ = pag
            filas = [(vo + j) & 255 for j in range(H + 1)]
            cols = [(uo + i) & 255 for i in range(W + 1)]
            _IMG[k] = Image.fromarray(rgb[np.ix_(filas, cols)].astype("uint8"))
    return _IMG[k]


def color_medio(k):
    """El color medio de la textura k (para colorear el bloque en las vistas del editor)."""
    if k not in _COL:
        im = imagen_textura(k)
        if im is None:
            _COL[k] = (128, 128, 128)
        else:
            px = list(im.getdata())
            _COL[k] = tuple(sum(p[c] for p in px) // len(px) for c in range(3))
    return _COL[k]


# ---------------------------------------------------------------- datos

def nueva(nombre, x0, z0, x1, z1, h, color=(128, 128, 128), **extra):
    p = dict(nombre=nombre, x0=min(x0, x1), z0=min(z0, z1), x1=max(x0, x1), z1=max(z0, z1), h=h, color=list(color))
    p.update({k: v for k, v in extra.items() if v is not None})
    return p


def cargar_nivel(ruta=NIVEL_POR_DEFECTO):
    """(plataformas, cielo)."""
    with open(ruta, encoding="utf-8") as f:
        datos = json.load(f)
    plats = []
    for p in datos["plataformas"]:
        p = dict(p)
        plats.append(nueva(p.pop("nombre"), p.pop("x0"), p.pop("z0"), p.pop("x1"), p.pop("z1"), p.pop("h"),
                           p.pop("color"), **p))
    return plats, dict(CIELO_DEFECTO, **datos.get("cielo", {}))


def cargar(ruta=NIVEL_POR_DEFECTO):
    return cargar_nivel(ruta)[0]


def guardar(plats, ruta, cielo=None):
    """Un bloque por linea, para que el diff de git se lea."""
    os.makedirs(os.path.dirname(ruta), exist_ok=True)
    lineas = ",\n".join("  " + json.dumps(p, ensure_ascii=False) for p in plats)
    cielo_txt = f'"cielo": {json.dumps(cielo)},\n' if cielo else ""
    with open(ruta, "w", encoding="utf-8") as f:
        f.write("{" + cielo_txt + '"plataformas": [\n' + lineas + "\n]}\n")


def contiene_salida(p):
    return p["x0"] <= SALIDA[0] <= p["x1"] and p["z0"] <= SALIDA[1] <= p["z1"]


def y_tapa(p, x, z):
    """Altura de la tapa de p en (x, z): plana, o la de la rampa."""
    if p.get("h2") is None:
        return p["h"]
    t = (x - p["x0"]) / (p["x1"] - p["x0"]) if p.get("eje", "x") == "x" else (z - p["z0"]) / (p["z1"] - p["z0"])
    return round(p["h"] + (p["h2"] - p["h"]) * t)


def h_max(p):
    """La altura (y) mas baja de la tapa: la mayor y."""
    return max(p["h"], p["h2"]) if p.get("h2") is not None else p["h"]


# ---------------------------------------------------------------- geometria

def cortes(a, b, paso):
    """Cortes de la rejilla de una tapa entre a y b: los bordes y todos los multiplos de 'paso' de por medio. Asi
    ningun cuadro cruza un multiplo de 1024 (borde de celda de colision) aunque a o b no sean multiplos de 'paso'."""
    return [a] + [c for c in range((a // paso + 1) * paso, b, paso)] + [b]


def paso_tapa(p):
    """Tamano de los cuadros de la tapa. El bloque de la salida lleva 512 siempre (ver salida_en_limite)."""
    return 512 if contiene_salida(p) else p.get("paso", 256)


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


def profundidades(plats):
    """Cuanto baja cada bloque desde su tapa: su campo 'prof' si lo tiene; si no, PROFUNDO o menos si debajo (se
    pisan en planta) hay otro bloque, para que no lo atraviese."""
    res = []
    for p in plats:
        if p.get("prof"):
            res.append(p["prof"])
            continue
        debajo = [q["h"] - h_max(p) for q in plats if q is not p and se_pisan(p, q) and q["h"] > h_max(p)]
        res.append(min([PROFUNDO] + debajo))
    return res


def cola_de_triangulo(p0, p1, p2):
    """Los 6 bytes finales de un triangulo del .INO (tipo u16, normal x/y/z, ejes), como en los triangulos reales del
    HUB. La normal es la de cross(p1 - p0, p2 - p0) (hacia donde se ve la cara) en bytes con escala 126 (-Y = 130);
    tipo 0 en el suelo y 1 en las paredes; ejes = los dos que mira PuntoEnTriangulo (8 = x,z; 4 = x,y; 9 = y,z) sin
    el de la normal dominante. Con la normal horizontal el suelo (func_8003A524) descarta el triangulo, asi que una
    pared no hace de suelo; el choque de lado lo usa de frente."""
    u = [p1[k] - p0[k] for k in range(3)]
    v = [p2[k] - p0[k] for k in range(3)]
    n = [u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0]]
    largo = math.sqrt(sum(c * c for c in n)) or 1.0
    nx, ny, nz = (c / largo for c in n)
    suelo = abs(ny) >= max(abs(nx), abs(nz))
    ejes = 8 if suelo else 4 if abs(nz) >= abs(nx) else 9
    return (0 if abs(nx) + abs(nz) < 1e-6 or ny < -0.5 else 1, 0,
            round(nx * 126) & 255, round(ny * 126) & 255, round(nz * 126) & 255, ejes)


def malla(verts, tris, pt, cu, cv, color, tex, swap):
    """Una cara: rejilla de vertices pt(cu[i], cv[j]) y, por cada cuadro, dos triangulos (a,b,d) y (b,c,d) con la
    textura entera estirada al cuadro (swap: la u de la textura va por el eje v de la cara, para paredes verticales
    cuya u de cara es Y)."""
    W, H = tabla_texturas().get(tex, (63, 63))
    nu, nv = len(cu) - 1, len(cv) - 1
    base = len(verts)
    pts = []
    for i in range(nu + 1):
        for j in range(nv + 1):
            q = pt(cu[i], cv[j])
            pts.append(q)
            verts.append(struct.pack("<3hh3Bx", *q, 0, *color))
    esq = [(0, 0), (W, 0), (W, H), (0, H)] if not swap else [(0, 0), (0, H), (W, H), (W, 0)]   # p00 p10 p11 p01
    for i in range(nu):
        for j in range(nv):
            a, b, c, d = (base + i * (nv + 1) + j, base + (i + 1) * (nv + 1) + j,
                          base + (i + 1) * (nv + 1) + j + 1, base + i * (nv + 1) + j + 1)
            for tri, uvs in (((a, b, d), (esq[0], esq[1], esq[3])), ((b, c, d), (esq[1], esq[2], esq[3]))):
                cola = cola_de_triangulo(*(pts[k - base] for k in tri))
                tris.append(tri + (tex,) + tuple(c_ for uv in uvs for c_ in uv) + cola)


def agregar_bloque(verts, tris, p, profundo=PROFUNDO):
    """La tapa (plana o rampa) y los 4 lados de un bloque, cada cara con su textura y su color."""
    x0, z0, x1, z1 = p["x0"], p["z0"], p["x1"], p["z1"]
    r, g, b = p["color"]
    tex_t, tex_l = p.get("tex_tapa", TEX_DEFECTO), p.get("tex_lado", TEX_DEFECTO)
    sombra = lambda k: (min(255, r * k // 128), min(255, g * k // 128), min(255, b * k // 128))
    yb = h_max(p) + profundo                                      # el fondo del bloque (sin cara: no se ve ni choca)
    yt = lambda x, z: y_tapa(p, x, z)
    fr = lambda arriba, t: round(arriba + (yb - arriba) * t)      # t = 0 en la tapa, 1 en el fondo
    # la tapa: cortes en los multiplos de 'paso' (que lo son de 1024/4) mas los bordes
    malla(verts, tris, lambda x, z: (x, yt(x, z), z), cortes(x0, x1, paso_tapa(p)), cortes(z0, z1, paso_tapa(p)),
          sombra(128), tex_t, False)
    # los lados: t baja de la tapa al fondo; los cuadros son de unos 512 (un triangulo muy grande no se dibuja)
    nz_ = max(1, round((z1 - z0) / PASO_PARED))
    nx_ = max(1, round((x1 - x0) / PASO_PARED))
    alto = yb - min(p["h"], p["h2"]) if p.get("h2") is not None else profundo
    nt = max(1, round(max(256, alto) / PASO_PARED))
    ct = [i / nt for i in range(nt + 1)]
    cz = [z0 + (z1 - z0) * i // nz_ for i in range(nz_ + 1)]
    cx = [x0 + (x1 - x0) * i // nx_ for i in range(nx_ + 1)]
    # +X: cross(Y, Z) = +X   -X: cross(Z, Y) = -X   +Z: cross(X, Y) = +Z   -Z: cross(Y, X) = -Z
    malla(verts, tris, lambda t, z: (x1, fr(yt(x1, z), t), z), ct, cz, sombra(80), tex_l, True)
    malla(verts, tris, lambda z, t: (x0, fr(yt(x0, z), t), z), cz, ct, sombra(80), tex_l, False)
    malla(verts, tris, lambda x, t: (x, fr(yt(x, z1), t), z1), cx, ct, sombra(100), tex_l, False)
    malla(verts, tris, lambda t, x: (x, fr(yt(x, z0), t), z0), ct, cx, sombra(100), tex_l, True)
    if p.get("techo"):       # cara inferior: u = Z, v = X, cross(Z, X) = +Y (hacia abajo); el suelo la descarta
        malla(verts, tris, lambda z, x: (x, yb, z), cortes(z0, z1, paso_tapa(p)), cortes(x0, x1, paso_tapa(p)),
              sombra(90), tex_l, False)


def nodo_de(plats):
    def armar(nodo_original):
        verts, tris = [], []
        for p, prof in zip(plats, profundidades(plats)):
            agregar_bloque(verts, tris, p, prof)
        return dict(nombre="PLATAF\0", matriz=nodo_original["matriz"], tras=nodo_original["tras"],
                    hijos=[], tris=tris, verts=verts)
    return armar


def nodo_cielo(cielo, R=7000, lon=24, lat=16):
    """Una esfera de radio R (el juego dibuja este modelo, SkyDome1, como cielo) vista desde dentro, con el color
    de los vertices en degradado: cenit arriba, horizonte en el ecuador y nadir abajo (el color final es el del
    cielo del nivel, tal cual). Los triangulos miran hacia el centro."""
    def armar(nodo_original):
        verts, tris = [], []
        col = lambda a, b, t: [min(255, round((a[k] + (b[k] - a[k]) * t) * 128 / TEXEL_CIELO[k])) for k in range(3)]
        for j in range(lat + 1):
            th = math.pi * j / lat                                     # 0 = cenit, pi = nadir
            y = round(-R * math.cos(th))
            rr = R * math.sin(th)
            e = 1 - abs(j - lat / 2) / (lat / 2)                       # 0 en los polos, 1 en el ecuador
            c = col(cielo["horizonte"], cielo["cenit"], 1 - e) if j <= lat / 2 else col(cielo["horizonte"],
                                                                                          cielo["nadir"], 1 - e)
            for i in range(lon + 1):
                ph = 2 * math.pi * (i % lon) / lon
                verts.append(struct.pack("<3hh3Bx", round(rr * math.cos(ph)), y, round(rr * math.sin(ph)), 0, *c))
        pos = [struct.unpack_from("<3h", v) for v in verts]
        esq = [UV_CIELO] * 4
        for j in range(lat):
            for i in range(lon):
                a, b = j * (lon + 1) + i, j * (lon + 1) + i + 1
                d, c = (j + 1) * (lon + 1) + i, (j + 1) * (lon + 1) + i + 1
                for tri, uvs in (((a, b, d), (esq[0], esq[1], esq[3])), ((b, c, d), (esq[1], esq[2], esq[3]))):
                    p0, p1, p2 = (pos[k] for k in tri)
                    u = [p1[k] - p0[k] for k in range(3)]
                    v = [p2[k] - p0[k] for k in range(3)]
                    n = [u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0]]
                    centro = [sum(q[k] for q in (p0, p1, p2)) for k in range(3)]
                    if sum(n[k] * centro[k] for k in range(3)) > 0:    # mira hacia afuera: se invierte
                        tri, uvs = (tri[0], tri[2], tri[1]), (uvs[0], uvs[2], uvs[1])
                    if len({p0, p1, p2}) == 3:                         # los polos colapsan un triangulo de cada cuadro
                        tris.append(tri + (TEX_CIELO,) + tuple(c_ for uv in uvs for c_ in uv) + (0, 0, 0, 0, 126, 4))
        return dict(nombre="SkyDome1\0", matriz=nodo_original["matriz"], tras=nodo_original["tras"],
                    hijos=[], tris=tris, verts=verts)
    return armar


# ---------------------------------------------------------------- validacion

def hueco(a, b):
    """Distancia horizontal entre los rectangulos de dos bloques (0 si se tocan)."""
    dx = max(b["x0"] - a["x1"], a["x0"] - b["x1"], 0)
    dz = max(b["z0"] - a["z1"], a["z0"] - b["z1"], 0)
    return math.hypot(dx, dz)


def validar(plats):
    """(errores, avisos). Con errores el nivel no se puede armar o Sabrina se cae; los avisos son solo
    jugabilidad (bloques que no se alcanzan con el salto medido)."""
    errores, avisos = [], []
    if not plats:
        return ["no hay plataformas"], []
    tex = tabla_texturas()
    for p in plats:
        n = p["nombre"]
        if p["x1"] - p["x0"] < 256 or p["z1"] - p["z0"] < 256:
            errores.append(f"{n}: mide menos de 256 de lado")
        if max(abs(p[k]) for k in ("x0", "z0", "x1", "z1")) > LIMITE or abs(p["h"]) > LIMITE - PROFUNDO:
            errores.append(f"{n}: se sale del mapa (maximo {LIMITE})")
        if p.get("paso", 256) not in (256, 512):
            errores.append(f"{n}: paso {p['paso']} no vale (256 o 512)")
        for k in ("tex_tapa", "tex_lado"):
            if p.get(k, TEX_DEFECTO) not in tex:
                errores.append(f"{n}: {k} {p[k]} no existe (0 a {max(tex)})")
        if p.get("h2") is not None:
            largo = (p["x1"] - p["x0"]) if p.get("eje", "x") == "x" else (p["z1"] - p["z0"])
            if abs(p["h2"] - p["h"]) / largo > PENDIENTE_MAX:
                errores.append(f"{n}: la rampa sube {abs(p['h2'] - p['h'])} en {largo}: Sabrina resbalaria "
                               f"(maximo {PENDIENTE_MAX:.2f} de pendiente)")
    profs = profundidades(plats)
    for i, a in enumerate(plats):
        for j, b in enumerate(plats[i + 1:], i + 1):
            if not se_pisan(a, b) or a.get("h2") is not None or b.get("h2") is not None:
                continue                                  # una rampa se apoya en lo de debajo (su borde bajo lo toca)
            d = abs(a["h"] - b["h"])
            if d < SEPARACION_MIN:
                errores.append(f"{a['nombre']} y {b['nombre']} se pisan en planta y sus alturas difieren solo "
                               f"{d}: separalas al menos {SEPARACION_MIN} (una sobre otra)")
            elif d < SEPARACION_AVISO:
                arriba, k = (a, i) if a["h"] < b["h"] else (b, j)
                if profs[k] < d:                          # si su pared cubre el hueco no se puede entrar por el lado
                    avisos.append(f"{a['nombre']} y {b['nombre']}: una sobre otra con solo {d} de separacion y sin "
                                  f"pared entre las dos; en la zona comun Sabrina sube sola a {arriba['nombre']} "
                                  f"(hacen falta {SEPARACION_AVISO} para poder pisar las dos)")
    inicio = [p for p in plats if contiene_salida(p) and p["h"] == 0 and p.get("h2") is None]
    if not inicio:
        errores.append(f"ningun bloque plano a altura 0 cubre la salida {SALIDA}: Sabrina aparece en el vacio")
    for p in inicio:
        if salida_en_limite(p):
            errores.append(f"{p['nombre']}: la salida {SALIDA} cae justo en un borde o diagonal de cuadro; "
                           "mueve el borde del bloque")
    if errores:
        return errores, avisos
    # alcanzables desde la salida con un salto
    vistos, pila = set(), [i for i, p in enumerate(plats) if p in inicio]
    while pila:
        i = pila.pop()
        if i in vistos:
            continue
        vistos.add(i)
        for j, q in enumerate(plats):
            if j in vistos:
                continue
            a_, b_ = plats[i], q
            sube = h_max(a_) - min(b_["h"], b_["h2"] if b_.get("h2") is not None else b_["h"])
            if b_.get("h2") is not None or a_.get("h2") is not None:
                sube = min(sube, SALTO_SUBIDA)                    # una rampa es continua con lo que toca
            apilada = se_pisan(a_, b_)
            if (hueco(a_, b_) <= SALTO_HUECO and sube <= (SALTO_APILADA if apilada else SALTO_SUBIDA)):
                pila.append(j)
    for i, p in enumerate(plats):
        if i not in vistos and not p.get("pared"):
            avisos.append(f"{p['nombre']}: no se alcanza desde la salida (hueco > {SALTO_HUECO} o subida > "
                          f"{SALTO_SUBIDA} desde todas las vecinas)")
    return errores, avisos


# ---------------------------------------------------------------- disco

def armar_disco(plats=None, nombre="plataformas", cielo=None):
    """Arma disco\\sabrina_<nombre>.cue (siempre de cero). Por defecto: niveles\\plataformas.json."""
    if plats is None:
        plats, cielo_json = cargar_nivel()
        cielo = cielo or cielo_json
    cielo = dict(CIELO_DEFECTO, **(cielo or {}))
    errores, _ = validar(plats)
    if errores:
        raise ValueError("nivel invalido: " + "; ".join(errores))
    cue, pista = rutas(nombre)
    nuevo = nf.construir_bytes(nodo_de(plats), CONSERVAR_PLAT, sin_objetos=True, paredes=True,
                               reemplazos={INDICE_CIELO: nodo_cielo(cielo)})
    disco.parchar({"GRAPHICS\\HUB\\H1W.INO": nuevo}, pista)
    disco.cue_mod(cue, pista)
    return cue


P_SABRINA = 0x8007CAF8     # puntero al objeto de Sabrina; +0x24 x, +0x28 y, +0x2C z (posicion = modelo * 256)


def punto_de_prueba(p):
    """Un punto dentro del bloque, cerca del centro y que (casi siempre) no cae en un borde de cuadro, donde
    Sabrina se cae."""
    cx = min((p["x0"] + p["x1"]) // 2 + 37, p["x1"] - 64)
    cz = min((p["z0"] + p["z1"]) // 2 + 53, p["z1"] - 64)
    return cx, cz


def suelo_esperado(plats, p, cx, cz):
    """La altura a la que Sabrina se queda al caer sobre p en (cx, cz): si hay tapas hasta AGARRE por encima en
    ese punto, el juego la sube a la mas alta de ellas (y asi sucesivamente)."""
    h = y_tapa(p, cx, cz)
    while True:
        arriba = [y_tapa(q, cx, cz) for q in plats if q["x0"] <= cx <= q["x1"] and q["z0"] <= cz <= q["z1"]
                  and 0 < h - y_tapa(q, cx, cz) <= AGARRE - 10]
        if not arriba:
            return h
        h = min(arriba)


def teletransportar(e, p, plats=()):
    """Pone a Sabrina sobre el bloque p (un poco por encima: cae sola) en un emulador ya arrancado. Si otro bloque
    esta justo encima de ese punto, empieza casi a ras de suelo (si no, caeria sobre el de arriba)."""
    obj = int(float(e.eval(f"return rd32({P_SABRINA})")))
    cx, cz = punto_de_prueba(p)
    y0 = y_tapa(p, cx, cz)
    arriba = [y_tapa(q, cx, cz) for q in plats if q is not p and y_tapa(q, cx, cz) < y0
              and q["x0"] <= cx <= q["x1"] and q["z0"] <= cz <= q["z1"]]
    sube = 30 if arriba else 200       # a ras de suelo: mas arriba entraria en la zona de agarre (AGARRE) del de arriba
    e.eval(f"wr32({obj + 0x24},{cx * 256 & 0xFFFFFFFF})")
    e.eval(f"wr32({obj + 0x28},{(y0 - sube) * 256 & 0xFFFFFFFF})")
    e.eval(f"wr32({obj + 0x2C},{cz * 256 & 0xFFFFFFFF})")
    return obj


def ver(plats, cielo=None):
    """Teletransporta a Sabrina sobre cada bloque, la deja caer y comprueba que se queda en la altura de la tapa
    (la colision de cada bloque funciona), con una captura por bloque."""
    from emu import Emu
    from explorar import CAP, recorrer
    from hoja import hoja
    ruta = armar_disco(plats, cielo=cielo)
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
    print("bloques con fallo:", fallos)
    return fallos


if __name__ == "__main__":
    modo = sys.argv[1] if len(sys.argv) > 1 else ""
    nivel, cielo_ = cargar_nivel(sys.argv[2]) if len(sys.argv) > 2 else cargar_nivel()
    if modo == "disco":
        print("disco plataformas:", armar_disco(nivel, cielo=cielo_))
    elif modo == "ver":
        ver(nivel, cielo_)
    else:
        print(__doc__)
