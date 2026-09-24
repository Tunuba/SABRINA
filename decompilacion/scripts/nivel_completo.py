"""Arma un nivel completo: el mundo, cada objeto de WRLDDATA con su modelo, rotacion y escala, marcadores para
los objetos sin modelo (gemas y demas) y las rutas de patrulla. Lo exporta a OBJ con texturas y dibuja
una vista desde arriba y otra en perspectiva.

Transformacion de un objeto (CrearObjetoMundo + MatrizDesdeAngulos): M = Rx * Ry * Rz * escala, con angulos
de 4096 por vuelta y escala = escala de la clase * escala del objeto / 4096. La posicion de WRLDDATA esta en
unidades del mundo (coordenada del modelo * 256).

Uso: python nivel_completo.py S3W        deja notas\\modelos\\<nivel>\\nivel\\
"""
import os
import struct
import sys

import numpy as np

import ino
import wobj
from ino_obj import SAL, Texturas, aplanar, dibujar, guardar_obj


def rot4096(rx, ry, rz):
    def m(eje, a):
        a = a / 4096 * 2 * np.pi
        c, s = np.cos(a), np.sin(a)
        return {"x": np.array([[1, 0, 0], [0, c, -s], [0, s, c]]),
                "y": np.array([[c, 0, s], [0, 1, 0], [-s, 0, c]]),
                "z": np.array([[c, -s, 0], [s, c, 0], [0, 0, 1]])}[eje]
    return m("x", rx) @ m("y", ry) @ m("z", rz)


def escala_clase(nivel_i, tipo):
    tabla = wobj.u32(0x80074858 + 4 * nivel_i)
    reg = tabla + tipo * 0x54
    return np.array([wobj.s16(reg + 0x28), wobj.s16(reg + 0x2A), wobj.s16(reg + 0x2C)], dtype=float)


def marcador(pos, color, tam=150.0):
    """Octaedro chico para objetos sin modelo."""
    v = np.array([[tam, 0, 0], [-tam, 0, 0], [0, tam, 0], [0, -tam, 0], [0, 0, tam], [0, 0, -tam]]) + pos
    t = np.array([[0, 2, 4], [2, 1, 4], [1, 3, 4], [3, 0, 4], [2, 0, 5], [1, 2, 5], [3, 1, 5], [0, 3, 5]])
    return v, np.tile(color, (6, 1)).astype(float), t


def armar(nivel):
    nv = ino.NIVELES.index(nivel)
    s = ino.leer_ino(nivel)
    tex = Texturas(nivel, s["texturas"])
    lista = ino.modelos_del_nivel(nv)
    modelos = [h for _, h in s["modelos"]]
    partes = []           # (V, C, T, D)
    V, C, T, D = aplanar(modelos[0])
    partes.append((V, C, T, D))
    colores = {4: (255, 60, 60), 18: (60, 120, 255), 19: (60, 255, 90), 23: (255, 220, 40)}
    sin_modelo = 0
    for o in wobj.leer_nivel(nivel):
        fn, m = wobj.clase(nv, o["tipo"])
        pos = np.array([o["x"], o["y"], o["z"]], dtype=float) / 256
        if m and 0 < m <= len(modelos) and modelos[m - 1] and o["tipo"] != 1:
            esc = escala_clase(nv, o["tipo"]) * np.array(o["esc"], dtype=float) / 4096 / 4096
            esc[esc == 0] = 1
            R = rot4096(*o["rot"]) * esc
            Vm, Cm, Tm, Dm = aplanar(modelos[m - 1])
            partes.append((Vm @ R.T + pos, Cm, Tm, Dm))
        else:
            sin_modelo += 1
            col = colores.get(o["tipo"], (255, 255, 255))
            Vm, Cm, Tm = marcador(pos, col)
            partes.append((Vm, Cm, Tm, None))
    return partes, tex, sin_modelo


def juntar(partes):
    Vs, Cs, Ts, Ds, base = [], [], [], [], 0
    for V, C, T, D in partes:
        Vs.append(V)
        Cs.append(C)
        Ts.append(T + base)
        Ds.append(D if D is not None else np.full((len(T), 7), -1))
        base += len(V)
    return np.vstack(Vs), np.vstack(Cs), np.vstack(Ts), np.vstack(Ds)


if __name__ == "__main__":
    nivel = sys.argv[1]
    partes, tex, sin_modelo = armar(nivel)
    V, C, T, D = juntar(partes)
    carpeta = os.path.join(SAL, nivel, "nivel")
    os.makedirs(carpeta, exist_ok=True)
    con_tex = D[:, 0] >= 0
    guardar_obj(carpeta, nivel + "_completo", V, C, T[con_tex], D[con_tex], tex)
    # los marcadores (sin textura) van con color de vertice en el mismo OBJ, en un grupo aparte
    with open(os.path.join(carpeta, nivel + "_completo.obj"), "a") as f:
        f.write("usemtl marcadores\n")
        for a, b, c in T[~con_tex]:
            f.write(f"f {a + 1} {b + 1} {c + 1}\n")
    rutas = wobj.leer_rutas(nivel)
    with open(os.path.join(carpeta, nivel + "_rutas.obj"), "w") as f:
        for r in rutas:
            f.write(f"v {r['x'] / 256:.1f} {-r['y'] / 256:.1f} {r['z'] / 256:.1f}\n")
        for r in rutas:
            if r["siguiente"] > 0:
                f.write(f"l {r['num']} {r['siguiente']}\n")
    Dr = D.copy()
    img = dibujar(V, C, T, Dr if con_tex.all() else np.where(con_tex[:, None], D, -1), None, ancho=1000, alto=1000,
                  giro=0.0, inclinacion=-np.pi / 2)
    img.save(os.path.join(carpeta, "desde_arriba_sin_textura.png"))
    print(f"{nivel}: {len(partes) - 1} objetos ({sin_modelo} sin modelo, como marcadores), {len(V)} vertices, "
          f"{len(T)} triangulos, {len(rutas)} puntos de ruta -> {carpeta}")
