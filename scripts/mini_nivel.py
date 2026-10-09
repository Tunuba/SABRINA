"""Mini nivel: el HUB (H1W) reducido a UN solo cubo flotante en una habitacion negra, nada mas.

Sabrina aparece encima del cubo (su punto de partida del HUB es x=128, z=-896, y=0). La tapa esta a y=0, la
altura donde aparece, y el cubo cuelga hacia abajo (en la PS1 +Y es abajo). Todo el resto del mundo (piso,
paredes, engranajes, ropero, cielo) se vacia; el mismo mecanismo que nivel_fantasma.py, pero:
- una sola pieza de geometria, alineada a la cuadricula de colision (celdas de 1024 unidades del modelo),
  asi que ningun triangulo cruza el borde de dos celdas (lo que hacia que Sabrina se hundiera);
- solo la tapa entra en la colision (los triangulos horizontales); las paredes y el fondo son solo dibujo;
- el cielo (SkyDome1) se conserva: es oscuro y tapa el fondo (sin el quedaba pegado un cuadro viejo).
La caida del nivel fantasma venia de que la colision (CeldaDePosicion: fila = (z + 0x800000) / 0x40000) usa la fila
DERECHA y el script repartia los triangulos con la fila invertida (la de rangos de suelo, objetos y zona): la
consulta de suelo miraba la celda espejo, vacia. nivel_fantasma.celdas_de_triangulos(invertida=False) lo arregla.

Uso:
    python mini_nivel.py disco     arma disco\\sabrina_mini.cue (siempre de cero)
    python mini_nivel.py probar    lo arma y lo arranca con ventana para jugarlo
    python mini_nivel.py ver       lo arma, lo arranca sin ventana y saca capturas + posiciones de Sabrina
"""
import os
import struct
import sys

import disco
import nivel_fantasma as nf

# La tapa va de (X0, Z0) a (X1, Z1); todos multiplos de 1024 (el ancho de una celda de colision) para que cada
# triangulo caiga entero en una sola celda. Sabrina aparece en (128, -896): dentro de la tapa.
X0, X1 = -1024, 1024
Z0, Z1 = -2048, 0
PROFUNDO = 2048           # cuanto cuelga el cubo por debajo de la tapa
PASO = nf.SPACING         # cuadros de 512, como el piso real (un triangulo muy grande no se dibuja)

CUE_MINI = os.path.join(disco.DISCO, "sabrina_mini.cue")
PISTA_MINI = os.path.join(disco.DISCO, "sabrina_mini (Track 01).bin")


def nodo_cubo(nodo_original):
    """Un nodo con las 6 caras del cubo. La cara que se ve de cada triangulo es la de normal cross(b - a,
    c - a) (asi estan los del piso real: normal -Y, o sea hacia arriba), asi que cada cara lleva sus ejes
    u, v con cross(u, v) apuntando hacia afuera. Textura, UV y tipo de superficie se copian de un triangulo
    de piso real del HUB."""
    piso = next(t for t in nodo_original["tris"] if t[10] in (0, 1) and t[15] == 8)
    textura, uv, cola = piso[3], tuple(piso[4:10]), tuple(piso[10:16])
    lx, lz = X1 - X0, Z1 - Z0
    X, Y, Z = (1, 0, 0), (0, 1, 0), (0, 0, 1)
    caras = [  # origen, u, largo de u, v, largo de v, brillo
        ((X0, 0, Z0), X, lx, Z, lz, 128),                 # tapa:   cross(X, Z) = -Y (arriba)
        ((X1, 0, Z0), Y, PROFUNDO, Z, lz, 80),            # +X:     cross(Y, Z) = +X
        ((X0, 0, Z0), Z, lz, Y, PROFUNDO, 80),            # -X:     cross(Z, Y) = -X
        ((X0, 0, Z1), X, lx, Y, PROFUNDO, 100),           # +Z:     cross(X, Y) = +Z
        ((X0, 0, Z0), Y, PROFUNDO, X, lx, 100),           # -Z:     cross(Y, X) = -Z
    ]   # sin fondo: es horizontal y entraria en la colision como un segundo suelo (ademas nadie lo ve)
    verts, tris = [], []
    for o, u, lu, v, lv, brillo in caras:
        nu, nv = max(1, round(lu / PASO)), max(1, round(lv / PASO))
        base = len(verts)
        for i in range(nu + 1):
            for j in range(nv + 1):
                p = [o[k] + u[k] * lu * i // nu + v[k] * lv * j // nv for k in range(3)]
                verts.append(struct.pack("<3hh3Bx", *p, 0, brillo, brillo, brillo))
        for i in range(nu):
            for j in range(nv):
                a, b = base + i * (nv + 1) + j, base + (i + 1) * (nv + 1) + j
                c, d = b + 1, a + 1                       # p00, p10, p11, p01
                # Diagonal p10-p01 (x + z = constante) y no la p00-p11: Sabrina aparece en (128, -896), justo sobre
                # la diagonal z = x - 1024 de la otra. Un punto exacto sobre el borde de dos triangulos es un caso
                # limite para PuntoEnTriangulo; asi se evita (no era la causa de la caida, ver mas abajo).
                tris.append((a, b, d, textura) + uv + cola)
                tris.append((b, c, d, textura) + uv + cola)
    return dict(nombre="CUBO\0", matriz=nodo_original["matriz"], tras=nodo_original["tras"],
                hijos=[], tris=tris, verts=verts)


# Sabrina (dos entradas del mismo traje), su sombra y SkyDome1 (19). El cielo se queda: es oscuro y es lo que
# tapa el fondo; sin el, en lo que nada dibuja se queda pegado un cuadro viejo (un cartel que parpadea).
CONSERVAR_MINI = {1, 2, 11, 12, 19}


def armar_disco():
    nuevo = nf.construir_bytes(nodo_cubo, CONSERVAR_MINI, sin_objetos=True)
    disco.parchar({"GRAPHICS\\HUB\\H1W.INO": nuevo}, PISTA_MINI)
    disco.cue_mod(CUE_MINI, PISTA_MINI)
    return CUE_MINI


if __name__ == "__main__":
    modo = sys.argv[1] if len(sys.argv) > 1 else ""
    if modo == "disco":
        print("disco mini:", armar_disco())
    elif modo == "probar":
        from emu import Emu
        from explorar import recorrer
        ruta = armar_disco()
        with Emu(iso=ruta, log="mini_nivel.log", extra=("-fastboot",), ui=True) as e:
            recorrer(e, "mini_arranque", "w2160 c CROSS w300 START w60 CROSS w240 c w1300 c")
            input("jugando el mini nivel; Enter en esta consola para cerrar... ")
    elif modo == "ver":
        import subprocess
        ruta = armar_disco()
        subprocess.run([sys.executable, os.path.join(os.path.dirname(__file__), "observar_fantasma.py"), ruta,
                        "w30 UP:30 w30 RIGHT:30 w30 DOWN:30 w30 CROSS w60"], check=True)
    else:
        print(__doc__)
