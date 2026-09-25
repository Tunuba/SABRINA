"""Arma un HUB alternativo ('nivel fantasma'): el .INO de H1W con el piso reemplazado por una grilla
de triangulos chicos (una malla plana, GRIDxGRID vertices) en vez de sus 349 triangulos originales,
cada uno repartido en su celda real de la cuadricula de colision (como en un nivel de verdad), y
todo lo que no sea Sabrina/su sombra/el skybox real (SkyDome1) vaciado (engranajes, ropero,
FashionDiva, iconos de traje).

**El piso SI se ve** (probado con un disco parchado real, arrancando de cero: colision y dibujo
funcionan). La primera version probaba un solo cuadrado gigante (2 triangulos de 32000 unidades de
lado) y quedaba invisible -junto con el skybox real, sin tocar-; leyendo `decomp\\src\\geometria\\
arbol.c` (func_8001FD50, compartido por un amigo) se confirmo en vivo que el nodo cargaba bien
(visible!=0, banderas sin bloquear), asi que el problema tenia que estar en el procesamiento por
triangulo. Esa funcion tiene una rama para "triangulo demasiado grande en pantalla" que lo manda a
partir (D_80068878/func_800598DC) en vez de dibujarlo directo -sospecha confirmada: con triangulos
del tamano real del piso (mediana ~571 unidades, medido en H1W.INO; SPACING=700 aca) en vez de dos
gigantes, se dibuja perfecto. El skybox real (SkyDome1, sin tocar) sigue sin verse -probablemente el
mismo problema, sus triangulos tambien deben ser grandes por naturaleza-, pendiente si se quiere un
cielo de verdad (habria que subdividirlo en triangulos chicos, como aca).

Dos correcciones despues de probarlo jugado (no solo con capturas automaticas): la primera version
dibujaba cada cuadrado con las 2 orientaciones de vertices ("por las dudas", cuando no se sabia si
se iba a ver nada) y eso parpadeaba -dos triangulos identicos compitiendo por los mismos pixeles
(z-fighting)-; ahora es una sola cara. Y la cuadricula de colision hacia que las 4096 celdas vieran
TODOS los triangulos del piso en vez de solo las cercanas -lento de verdad-; ahora cada triangulo se
reparte en su celda real (formula de FORMATOS.md, con la posicion pasada a la escala de Sabrina:
posicion = coordenada del modelo * 256), asi que la inmensa mayoria de las 4096 celdas quedan vacias,
como en un nivel real.

Uso:
    python nivel_fantasma.py disco     arma disco\\sabrina_fantasma.cue (+ el .bin), si no existe ya
    python nivel_fantasma.py probar    lo arma si hace falta y lo arranca con ventana para jugarlo
"""
import os
import struct
import sys

import disco
import ino
from ino_escribir import escribir_ino

NIVEL = "H1W"
# La malla va ALINEADA a la cuadricula de colision del juego (celdas de 0x40000 / 256 = 1024 unidades del
# modelo): con SPACING = 512 y el borde en -4096, cada celda tiene exactamente 2x2 cuadros y ningun
# triangulo cruza el borde entre dos celdas. Con SPACING = 700 los triangulos cruzaban bordes, cada uno
# quedaba solo en la celda de su centro, y donde Sabrina pisaba la mitad que caia en la celda vecina la
# consulta de suelo no encontraba nada y se caia (visto en vivo con observar_fantasma.py: aparece en
# (128, 0, -896), se desliza y se hunde).
GRID = 17       # vertices por lado -> 16x16 cuadros de 512 = 8192 de lado, de -4096 a 4096
SPACING = 512   # unidades locales entre vertices vecinos: la mediana real de los triangulos de piso
                # del HUB es ~571 y el maximo real ~6969 (medido en H1W.INO); un triangulo de
                # 32000 unidades (lo que se probo antes, un solo cuadrado gigante) es ~45000 de
                # diagonal, muy por encima de eso -sospecha: cae en la rama de "triangulo demasiado
                # grande en pantalla" (arbol.c func_8001FD50, D_80068878/func_800598DC) que puede no
                # estar hecha para algo tan extremo. Esta version usa muchos triangulos chicos, del
                # tamano real, en vez de dos gigantes. Con GRID=15 el piso mide 9800 unidades de
                # lado -parecido a los ~8192 del piso original del HUB-.
ESCALA_MUNDO = 256  # posicion de Sabrina = coordenada del modelo del mundo * 256 (FORMATOS.md);
                    # CeldaDePosicion trabaja en la escala de Sabrina, no en la del modelo
# modelos que quedan tal cual ademas del mundo (que se reemplaza): Sabrina default (dos entradas del
# mismo traje), su sombra, y el skybox real que ya trae el HUB (SkyDome1.bud)
CONSERVAR = {1, 2, 11, 12, 19}

CUE_FANTASMA = os.path.join(disco.DISCO, "sabrina_fantasma.cue")
PISTA_FANTASMA = os.path.join(disco.DISCO, "sabrina_fantasma (Track 01).bin")


def nodo_plano(nodo_original):
    """Un solo nodo: una grilla de GRIDxGRID vertices sobre el plano XZ (muchos triangulos chicos,
    del tamano real de un triangulo de piso, de una sola cara -dos caras hacia parpadear, dos
    triangulos identicos compitiendo por los mismos pixeles-), con la textura/UV/tipo-de-superficie
    copiados de un triangulo de piso real del HUB (no inventados)."""
    piso_real = next(t for t in nodo_original["tris"] if t[10] in (0, 1) and t[15] == 8)
    textura = piso_real[3]
    uv = tuple(piso_real[4:10])
    cola = tuple(piso_real[10:16])

    medio = (GRID - 1) * SPACING // 2
    verts = []
    for gx in range(GRID):
        for gz in range(GRID):
            x, z = gx * SPACING - medio, gz * SPACING - medio
            verts.append(struct.pack("<3hh3Bx", x, 0, z, 0, 128, 128, 128))

    def idx(gx, gz):
        return gx * GRID + gz

    tris = []
    for gx in range(GRID - 1):
        for gz in range(GRID - 1):
            v00, v10, v11, v01 = idx(gx, gz), idx(gx + 1, gz), idx(gx + 1, gz + 1), idx(gx, gz + 1)
            for a, b, c in [(v00, v10, v11), (v00, v11, v01)]:
                tris.append((a, b, c, textura) + uv + cola)

    return dict(nombre="PLANO\0", matriz=nodo_original["matriz"], tras=nodo_original["tras"],
                hijos=[], tris=tris, verts=verts)


CUBO = dict(x=1536, z=1536, lado=1024, alto=512)   # alineado: ocupa justo la celda de x, z en [1024, 2048)   # None para no ponerlo; centro en el plano, medidas en unidades del modelo


def agregar_cubo(nodo, x, z, lado, alto):
    """Agrega al nodo del mundo un cubo apoyado en el piso: la tapa y las 4 paredes (sin fondo), cada
    cara partida en cuadros de SPACING como el piso (un triangulo muy grande no se dibuja).
    En la PS1 -Y es arriba. La cara que se ve es la de normal cross(b - a, c - a) (asi estan los
    triangulos del piso: normal -Y), asi que cada cara lleva sus ejes u, v con cross(u, v) hacia afuera.
    Las paredes van mas oscuras (color de vertice) para que se note la forma."""
    piso = nodo["tris"][0]
    textura, uv, cola = piso[3], tuple(piso[4:10]), tuple(piso[10:16])
    m = lado // 2
    X, Y, Z = (1, 0, 0), (0, 1, 0), (0, 0, 1)
    caras = [  # origen, u, largo de u, v, largo de v, brillo
        ((x - m, -alto, z - m), X, lado, Z, lado, 128),   # tapa: cross(X, Z) = -Y
        ((x + m, -alto, z - m), Y, alto, Z, lado, 80),    # +X: cross(Y, Z) = +X
        ((x - m, -alto, z - m), Z, lado, Y, alto, 80),    # -X: cross(Z, Y) = -X
        ((x - m, -alto, z + m), X, lado, Y, alto, 100),   # +Z: cross(X, Y) = +Z
        ((x - m, -alto, z - m), Y, alto, X, lado, 100),   # -Z: cross(Y, X) = -Z
    ]
    for o, u, lu, v, lv, brillo in caras:
        nu, nv = max(1, round(lu / SPACING)), max(1, round(lv / SPACING))
        base = len(nodo["verts"])
        for i in range(nu + 1):
            for j in range(nv + 1):
                p = [o[k] + u[k] * lu * i // nu + v[k] * lv * j // nv for k in range(3)]
                nodo["verts"].append(struct.pack("<3hh3Bx", *p, 0, brillo, brillo, brillo))
        for i in range(nu):
            for j in range(nv):
                a, b = base + i * (nv + 1) + j, base + (i + 1) * (nv + 1) + j
                c, d = b + 1, a + 1                       # p00, p10, p11, p01
                nodo["tris"].append((a, b, c, textura) + uv + cola)
                nodo["tris"].append((a, c, d, textura) + uv + cola)


def celdas_de_triangulos(nodo, ancho, alto):
    """{(fila, columna): [indices de triangulo]} segun donde cae el centro de cada triangulo, con
    la posicion pasada a la escala de Sabrina (CeldaDePosicion trabaja en esa escala, no en la del
    modelo -confirmado con las pruebas de colision en vivo de antes)."""
    # (x, z) de cada vertice (x, y, z son los 3 primeros int16; antes se leian x e y, y como el piso
    # es plano todo caia en la fila de z = 0)
    verts_xyz = [struct.unpack_from("<3h", v, 0) for v in nodo["verts"]]
    verts_xz = [v[0::2] for v in verts_xyz]
    reparto = {}
    for i, t in enumerate(nodo["tris"]):
        v0, v1, v2 = t[0], t[1], t[2]
        # Solo triangulos horizontales (piso y tapa del cubo): uno vertical (pared) en la colision de
        # suelo hace que la altura calculada salga mal y Sabrina atraviese el piso y se caiga. Las
        # paredes quedan solo para dibujar.
        if len({verts_xyz[v][1] for v in (v0, v1, v2)}) != 1:
            continue
        cx = sum(verts_xz[v][0] for v in (v0, v1, v2)) / 3 * ESCALA_MUNDO
        cz = sum(verts_xz[v][1] for v in (v0, v1, v2)) / 3 * ESCALA_MUNDO
        x, z = int(cx), int(cz)
        fila = (~((z >> 16) + 0x80) & 0xFF) >> 2
        columna = ((x >> 16) + 0x80) >> 2
        if 0 <= fila < alto and 0 <= columna < ancho:
            reparto.setdefault((fila, columna), []).append(i)
    return reparto


def construir_bytes():
    """El H1W.INO modificado, del mismo tamano que el original (relleno con ceros al final, que el
    juego no llega a leer)."""
    s = ino.leer_ino(NIVEL)
    g = s["cuadricula"]

    idx_mundo = next(i for i, (nom, _nd) in enumerate(s["modelos"]) if nom.upper().endswith(NIVEL + ".BUD"))
    nombre_mundo, nodos_mundo = s["modelos"][idx_mundo]
    nodo = nodo_plano(nodos_mundo[0])
    if CUBO:
        agregar_cubo(nodo, **CUBO)
    s["modelos"][idx_mundo] = (nombre_mundo, [nodo])
    for i, (nom, nodos) in enumerate(s["modelos"]):
        if i != idx_mundo and i not in CONSERVAR:
            s["modelos"][i] = (nom, [])

    # Los triangulos van ordenados por celda, como en un nivel real: asi cada celda puede declarar su
    # tramo contiguo de suelo en 'celdas' (primer triangulo, cuantos).
    reparto = celdas_de_triangulos(nodo, g["ancho"], g["alto"])
    orden = sorted(reparto, key=lambda fc: fc[0] * g["ancho"] + fc[1])
    viejo_a_nuevo, tris = {}, []
    for fc in orden:
        for i in reparto[fc]:
            viejo_a_nuevo[i] = len(tris)
            tris.append(nodo["tris"][i])
    tris += [t for i, t in enumerate(nodo["tris"]) if i not in viejo_a_nuevo]   # las paredes, al final
    nodo["tris"] = tris
    reparto = {fc: [viejo_a_nuevo[i] for i in idxs] for fc, idxs in reparto.items()}

    # tabla de indices: cada celda con triangulos se lleva un tramo propio y contiguo
    indices = []
    listas = [None] * g["B"]  # (cantidad, inicio) por celda; el resto queda vacia (cantidad 0)
    for (fila, columna), idxs in reparto.items():
        orden = fila * g["ancho"] + columna
        listas[orden] = (len(idxs), len(indices))
        indices.extend(idxs)
    listas_bytes = b"".join(struct.pack("<hHi", l[0], 0, l[1]) if l else struct.pack("<hHi", 0, 0, 0)
                             for l in listas)
    indices_bytes = struct.pack(f"<{len(indices)}h", *indices) if indices else b""

    # celdas: 'listas' (arriba) es la colision (suelo.c). El rango de suelo de 'celdas' (primer
    # triangulo, cuantos; -1, 0 si no tiene) antes apuntaba en TODAS las 4096 celdas a todo el piso, y
    # eso trababa el juego: medido con medir_fps.py, 4.3 cuadros por segundo contra 31 del HUB real
    # (el juego procesa el suelo de las celdas cercanas cada cuadro, y cada una traia el piso entero).
    # Ahora cada celda declara solo su tramo, como el HUB real (32 celdas con suelo, 3 a 13 triangulos).
    # Se pisan solo esos 2 shorts; objetos/zona quedan del original.
    celdas = bytearray(g["celdas"])
    for i in range(g["A"]):
        struct.pack_into("<2h", celdas, i * 12, -1, 0)
    for (fila, columna), idxs in reparto.items():
        struct.pack_into("<2h", celdas, (fila * g["ancho"] + columna) * 12, min(idxs), len(idxs))

    s["cuadricula"] = dict(
        A=g["A"], B=g["B"], ancho=g["ancho"], alto=g["alto"], C=len(indices),
        celdas=bytes(celdas),
        listas=listas_bytes,
        indices=indices_bytes,
    )
    print(f"piso repartido en {len(reparto)} celda(s) reales de las {g['B']} de la cuadricula "
          f"({len(nodo['tris'])} triangulos en total)")

    nuevo = escribir_ino(s)
    tam_original = os.path.getsize(os.path.join(ino.RAIZ, "extraido", "GRAPHICS", "HUB", "H1W.INO"))
    if len(nuevo) > tam_original:
        raise ValueError("el .INO reescrito se paso del tamano original; disco.parchar() no lo va a aceptar")
    return nuevo + b"\0" * (tam_original - len(nuevo))


def armar_disco(forzar=False):
    """Arma disco\\sabrina_fantasma.cue si no existe todavia (o si forzar=True). Devuelve la ruta del .cue."""
    if not forzar and os.path.exists(CUE_FANTASMA) and os.path.exists(PISTA_FANTASMA):
        return CUE_FANTASMA
    nuevo = construir_bytes()
    disco.parchar({"GRAPHICS\\HUB\\H1W.INO": nuevo}, PISTA_FANTASMA)
    disco.cue_mod(CUE_FANTASMA, PISTA_FANTASMA)
    return CUE_FANTASMA


if __name__ == "__main__" and sys.argv[1:] == ["disco"]:
    ruta = armar_disco(forzar=True)
    print("disco fantasma:", ruta)
elif __name__ == "__main__" and sys.argv[1:] == ["probar"]:
    from emu import Emu
    from explorar import recorrer
    ruta = armar_disco()
    print("disco fantasma:", ruta)
    with Emu(iso=ruta, log="nivel_fantasma.log", extra=("-fastboot",), ui=True) as e:
        recorrer(e, "fantasma_arranque", "w2160 c CROSS w300 START w60 CROSS w240 c w1300 c")
        input("jugando el nivel fantasma; Enter en esta consola para cerrar... ")
