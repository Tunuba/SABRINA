"""Nivel de plataformas: el HUB (H1W) vaciado y reemplazado por una ruta de plataformas flotantes que sube en
espiral, de la zona de salida (verde) hasta la meta (dorada), en un cuarto negro. Usa el mismo mecanismo que
mini_nivel.py (nivel_fantasma.construir_bytes), con varias piezas a distintas alturas.

Medido con observar_fantasma.py: Sabrina salta ~360 unidades de alto y, corriendo, cae a ~330 de distancia, asi
que la ruta usa saltos de 256 de hueco y subidas de 128 por plataforma. Si cae, reaparece en la salida.
Con UP Sabrina avanza hacia +X +Z (camara en diagonal).

Reglas que cumple cada plataforma (las mismas del mini nivel):
- bordes en multiplos de 256 y cuadros de 256 (512 en la salida): como la celda de colision mide 1024, ningun
  triangulo cruza el borde de dos celdas;
- solo las tapas (triangulos horizontales) entran en la colision; las paredes laterales son solo dibujo y no
  llevan fondo (seria un segundo suelo);
- la salida usa cuadros de 512 con la diagonal x + z = const: Sabrina aparece en (128, -896), el centro de un
  cuadro de 256, y justo sobre una diagonal es un caso limite para PuntoEnTriangulo.

Uso:
    python nivel_plataformas.py disco     arma disco\\sabrina_plataformas.cue (siempre de cero)
    python nivel_plataformas.py probar    lo arma y lo arranca con ventana para jugarlo
    python nivel_plataformas.py ver       lo arma, lo arranca sin ventana, teletransporta a Sabrina a cada
                                          plataforma, comprueba que pisa en la altura esperada y saca capturas
"""
import os
import struct
import sys

import disco
import nivel_fantasma as nf

# (x0, z0, x1, z1, altura de la tapa, color RGB, cuadro); la altura es la de la tapa en unidades del modelo
# (-Y es arriba, asi que "mas alto" = mas negativo); Sabrina aparece en (128, 0, -896) sobre la salida.
VERDE, GRIS, AZUL, DORADO = (70, 150, 70), (128, 128, 128), (90, 110, 170), (255, 200, 60)
PLATAFORMAS = [
    ("salida", -512, -1536, 1024, 0, 0, VERDE, 512),
    ("p1", 1280, -1536, 2048, -768, -128, GRIS, 256),
    ("p2", 2304, -1536, 3328, -768, -256, AZUL, 256),
    ("p3", 2304, -512, 3072, 256, -384, GRIS, 256),
    ("p4", 2304, 512, 3072, 1280, -512, AZUL, 256),
    ("p5", 1280, 512, 2048, 1280, -640, GRIS, 256),
    ("p6", 256, 512, 1024, 1280, -768, AZUL, 256),
    ("p7", 256, 1536, 1024, 2304, -896, GRIS, 256),
    ("p8", 1280, 1536, 2048, 2304, -1024, AZUL, 256),
    ("p9", 2304, 1536, 3584, 2304, -1152, GRIS, 256),
    ("meta", 3840, 1536, 5120, 2560, -1280, DORADO, 256),
]
PROFUNDO = 768             # cuanto cuelga cada plataforma por debajo de su tapa (solo dibujo)
PASO_PARED = nf.SPACING    # cuadros de 512 en las paredes (un triangulo muy grande no se dibuja)

CUE_PLAT = os.path.join(disco.DISCO, "sabrina_plataformas.cue")
PISTA_PLAT = os.path.join(disco.DISCO, "sabrina_plataformas (Track 01).bin")
CONSERVAR_PLAT = {1, 2, 11, 12, 19}   # Sabrina, su sombra y el cielo (ver mini_nivel.py)


def agregar_plataforma(verts, tris, plat, textura, uv, cola):
    """La tapa (cuadros de 'paso', diagonal p10-p01) y las 4 paredes de una plataforma. La cara que se ve es la de
    normal cross(b - a, c - a); cada cara lleva ejes u, v con cross(u, v) hacia afuera (en la PS1 -Y es arriba)."""
    _, x0, z0, x1, z1, h, (r, g, b), paso = plat
    lx, lz = x1 - x0, z1 - z0
    X, Y, Z = (1, 0, 0), (0, 1, 0), (0, 0, 1)
    sombra = lambda k: (r * k // 128, g * k // 128, b * k // 128)
    caras = [  # origen, u, largo de u, v, largo de v, color, tamano de cuadro
        ((x0, h, z0), X, lx, Z, lz, sombra(128), paso),            # tapa: cross(X, Z) = -Y
        ((x1, h, z0), Y, PROFUNDO, Z, lz, sombra(80), PASO_PARED),  # +X: cross(Y, Z) = +X
        ((x0, h, z0), Z, lz, Y, PROFUNDO, sombra(80), PASO_PARED),  # -X: cross(Z, Y) = -X
        ((x0, h, z1), X, lx, Y, PROFUNDO, sombra(100), PASO_PARED),  # +Z: cross(X, Y) = +Z
        ((x0, h, z0), Y, PROFUNDO, X, lx, sombra(100), PASO_PARED),  # -Z: cross(Y, X) = -Z
    ]
    for o, u, lu, v, lv, color, tam in caras:
        nu, nv = max(1, round(lu / tam)), max(1, round(lv / tam))
        base = len(verts)
        for i in range(nu + 1):
            for j in range(nv + 1):
                p = [o[k] + u[k] * lu * i // nu + v[k] * lv * j // nv for k in range(3)]
                verts.append(struct.pack("<3hh3Bx", *p, 0, *color))
        for i in range(nu):
            for j in range(nv):
                a, b_ = base + i * (nv + 1) + j, base + (i + 1) * (nv + 1) + j
                c, d = b_ + 1, a + 1                       # p00, p10, p11, p01
                tris.append((a, b_, d, textura) + uv + cola)
                tris.append((b_, c, d, textura) + uv + cola)


def nodo_plataformas(nodo_original):
    """Un nodo con todas las plataformas. Textura, UV y tipo de superficie se copian de un triangulo de piso real
    del HUB."""
    piso = next(t for t in nodo_original["tris"] if t[10] in (0, 1) and t[15] == 8)
    textura, uv, cola = piso[3], tuple(piso[4:10]), tuple(piso[10:16])
    verts, tris = [], []
    for plat in PLATAFORMAS:
        agregar_plataforma(verts, tris, plat, textura, uv, cola)
    return dict(nombre="PLATAF\0", matriz=nodo_original["matriz"], tras=nodo_original["tras"],
                hijos=[], tris=tris, verts=verts)


def armar_disco():
    nuevo = nf.construir_bytes(nodo_plataformas, CONSERVAR_PLAT, sin_objetos=True)
    disco.parchar({"GRAPHICS\\HUB\\H1W.INO": nuevo}, PISTA_PLAT)
    disco.cue_mod(CUE_PLAT, PISTA_PLAT)
    return CUE_PLAT


P_SABRINA = 0x8007CAF8     # puntero al objeto de Sabrina; +0x24 x, +0x28 y, +0x2C z (posicion = modelo * 256)


def ver():
    """Teletransporta a Sabrina sobre el centro de cada plataforma, la deja caer y comprueba que se queda en la
    altura de la tapa (la colision de cada plataforma funciona), con una captura por plataforma."""
    from emu import Emu
    from explorar import CAP, recorrer
    from hoja import hoja
    ruta = armar_disco()
    s = lambda v: v - (1 << 32) if v >= 1 << 31 else v
    capturas, fallos = [], 0
    with Emu(iso=ruta, log="nivel_plataformas.log", extra=("-fastboot",), puerto=8097) as e:
        recorrer(e, "plat_arranque", "w2160 CROSS w300 START w60 CROSS w240 w1300")
        p = int(float(e.eval(f"return rd32({P_SABRINA})")))
        for nombre, x0, z0, x1, z1, h, _, _ in PLATAFORMAS:
            cx, cz = ((x0 + x1) // 2 + 100) * 256, ((z0 + z1) // 2 + 100) * 256   # +100: no justo sobre una arista de cuadro
            e.eval(f"wr32({p + 0x24},{cx & 0xFFFFFFFF})")
            e.eval(f"wr32({p + 0x28},{(h - 200) * 256 & 0xFFFFFFFF})")
            e.eval(f"wr32({p + 0x2C},{cz & 0xFFFFFFFF})")
            e.esperar(90)
            y = s(int(float(e.eval(f"return rd32({p + 0x28})")))) / 256
            bien = abs(y - h) < 8
            fallos += not bien
            print(f"{nombre:7s} esperada y={h:6d}  medida y={y:8.1f}  {'ok' if bien else 'FALLA'}", flush=True)
            r = os.path.join(CAP, f"plat_{nombre}.png")
            e.captura(r)
            capturas.append(r)
    hoja(os.path.join(CAP, "plat_hoja.png"), 4, capturas)
    print("plataformas con fallo:", fallos)


if __name__ == "__main__":
    modo = sys.argv[1] if len(sys.argv) > 1 else ""
    if modo == "disco":
        print("disco plataformas:", armar_disco())
    elif modo == "probar":
        from emu import Emu
        from explorar import recorrer
        ruta = armar_disco()
        with Emu(iso=ruta, log="nivel_plataformas.log", extra=("-fastboot",), ui=True) as e:
            recorrer(e, "plat_arranque", "w2160 c CROSS w300 START w60 CROSS w240 c w1300 c")
            input("jugando el nivel de plataformas; Enter en esta consola para cerrar... ")
    elif modo == "ver":
        ver()
    else:
        print(__doc__)
