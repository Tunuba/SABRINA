"""Exporta modelos de un .INO a OBJ (con colores de vertice) y dibuja una vista previa en PNG.

Vertice (12 bytes): int16 x y z, int16 relleno, uint8 r g b, relleno. El escenario trae la luz
pintada en los colores; los personajes vienen en blanco (se iluminan al vuelo).
Triangulo (28 bytes): int32 v0 v1 v2, int32 textura, u0 v0 u1 v1 u2 v2, 6 bytes sin descifrar.
Nodo: MATRIX de la PS1 (int16 m[3][3] con 4096 = 1.0, int32 t[3]); se aplica de padre a hijo.

Uso: python ino_obj.py H1W                     todos los modelos del nivel
     python ino_obj.py H1W SABdefault          solo los que contengan ese texto
Salida: notas\\modelos\\<nivel>\\<modelo>.obj y .png, y una hoja con todos.
"""
import os
import struct
import sys

import numpy as np
from PIL import Image

import ino
from hoja import hoja

SAL = os.path.join(ino.RAIZ, "notas", "modelos")


def aplanar(nodos, mat=np.eye(3), tras=np.zeros(3)):
    """Devuelve (vertices Nx3, colores Nx3, triangulos Mx3) de un arbol de nodos en coordenadas del modelo."""
    V, C, T = [], [], []
    base = 0
    for n in nodos:
        m = np.array(n["matriz"], dtype=float).reshape(3, 3) / 4096.0
        t = np.array(n["tras"], dtype=float)
        mg = mat @ m
        tg = mat @ t + tras
        if n["verts"]:
            raw = np.array([struct.unpack("<3hh3Bx", v) for v in n["verts"]], dtype=float)
            V.append(raw[:, :3] @ mg.T + tg)
            C.append(raw[:, 4:7])
            T.append(np.array([t[:3] for t in n["tris"]], dtype=int).reshape(-1, 3) + base)
            base += len(raw)
        hv, hc, ht = aplanar(n["hijos"], mg, tg)
        if len(hv):
            V.append(hv)
            C.append(hc)
            T.append(ht + base)
            base += len(hv)
    if not V:
        return np.zeros((0, 3)), np.zeros((0, 3)), np.zeros((0, 3), dtype=int)
    return np.vstack(V), np.vstack(C), np.vstack(T)


def guardar_obj(ruta, V, C, T):
    with open(ruta, "w") as f:
        for (x, y, z), (r, g, b) in zip(V, C):
            f.write(f"v {x:.1f} {-y:.1f} {z:.1f} {r / 255:.3f} {g / 255:.3f} {b / 255:.3f}\n")
        for a, b, c in T:
            f.write(f"f {a + 1} {b + 1} {c + 1}\n")


def dibujar(V, C, T, ancho=480, alto=360, giro=0.6, inclinacion=0.45):
    """Render por software con z-buffer. Y de la PS1 apunta hacia abajo, por eso se invierte."""
    img = np.full((alto, ancho, 3), 30, dtype=float)
    if len(T) == 0:
        return Image.fromarray(img.astype(np.uint8))
    P = V.copy()
    P[:, 1] = -P[:, 1]
    P -= (P.max(0) + P.min(0)) / 2
    cg, sg, ci, si = np.cos(giro), np.sin(giro), np.cos(inclinacion), np.sin(inclinacion)
    P = P @ np.array([[cg, 0, -sg], [0, 1, 0], [sg, 0, cg]]).T
    P = P @ np.array([[1, 0, 0], [0, ci, si], [0, -si, ci]]).T
    esc = 0.9 * min(ancho, alto) / max(np.ptp(P[:, 0]), np.ptp(P[:, 1]), 1)
    sx = P[:, 0] * esc + ancho / 2
    sy = -P[:, 1] * esc + alto / 2
    z = P[:, 2]
    zbuf = np.full((alto, ancho), np.inf)
    col = C.copy()
    if (col > 250).all():
        col = np.full_like(col, 200.0)       # personajes sin luz pintada: gris
    for a, b, c in T:
        xs, ys = np.array([sx[a], sx[b], sx[c]]), np.array([sy[a], sy[b], sy[c]])
        x0, x1 = max(int(xs.min()), 0), min(int(xs.max()) + 1, ancho)
        y0, y1 = max(int(ys.min()), 0), min(int(ys.max()) + 1, alto)
        if x0 >= x1 or y0 >= y1:
            continue
        den = (ys[1] - ys[2]) * (xs[0] - xs[2]) + (xs[2] - xs[1]) * (ys[0] - ys[2])
        if abs(den) < 1e-9:
            continue
        gx, gy = np.meshgrid(np.arange(x0, x1) + 0.5, np.arange(y0, y1) + 0.5)
        w0 = ((ys[1] - ys[2]) * (gx - xs[2]) + (xs[2] - xs[1]) * (gy - ys[2])) / den
        w1 = ((ys[2] - ys[0]) * (gx - xs[2]) + (xs[0] - xs[2]) * (gy - ys[2])) / den
        w2 = 1 - w0 - w1
        dentro = (w0 >= 0) & (w1 >= 0) & (w2 >= 0)
        zz = w0 * z[a] + w1 * z[b] + w2 * z[c]
        zona = zbuf[y0:y1, x0:x1]
        ok = dentro & (zz < zona)
        if not ok.any():
            continue
        # sombreado plano segun la normal, para que se lea la forma aunque no haya texturas
        n = np.cross(P[b] - P[a], P[c] - P[a])
        luz = 0.45 + 0.55 * abs(n[2]) / (np.linalg.norm(n) + 1e-9)
        rgb = (w0[..., None] * col[a] + w1[..., None] * col[b] + w2[..., None] * col[c]) * luz
        zona[ok] = zz[ok]
        img[y0:y1, x0:x1][ok] = np.clip(rgb[ok] * 1.6, 0, 255)
    return Image.fromarray(img.astype(np.uint8))


if __name__ == "__main__":
    nivel = sys.argv[1]
    filtro = sys.argv[2] if len(sys.argv) > 2 else ""
    s = ino.leer_ino(nivel)
    carpeta = os.path.join(SAL, nivel)
    os.makedirs(carpeta, exist_ok=True)
    rutas = []
    vistos = set()
    for nom, nodos in s["modelos"]:
        base = os.path.splitext(os.path.basename(nom.replace("\\", "/")))[0]
        if filtro.lower() not in base.lower() or base in vistos or not nodos:
            continue
        vistos.add(base)
        V, C, T = aplanar(nodos)
        guardar_obj(os.path.join(carpeta, base + ".obj"), V, C, T)
        png = os.path.join(carpeta, base + ".png")
        dibujar(V, C, T).save(png)
        rutas.append(png)
        print(f"{base}: {len(V)} vertices, {len(T)} triangulos")
    if rutas:
        hoja(os.path.join(carpeta, "hoja.png"), 4, rutas)
