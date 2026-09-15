"""Exporta modelos de un .INO a OBJ con texturas y dibuja una vista previa en PNG.

Vertice (12 bytes): int16 x y z, int16 relleno, uint8 r g b, relleno. El escenario trae la luz
pintada en los colores; los personajes vienen en blanco (se iluminan al vuelo).
Triangulo (28 bytes): int32 v0 v1 v2, int32 textura (indice en la lista de texturas del .INO),
u0 v0 u1 v1 u2 v2 relativos a la textura, 6 bytes sin descifrar.
Registro de textura (32 bytes, 16 halfwords): h4 ancho, h5 alto, h6 TPAGE, h7 CLUT, h8 u,v de la textura
dentro de su pagina (el cargador los suma a cada triangulo), h9 h10 x,y en la VRAM, h11 h12 x,y de la
paleta, h13 cantidad de colores (16 o 256), h14 banderas.
Las texturas y paletas se leen del .TEX del nivel (la mitad derecha de la VRAM). La PS1 multiplica el
texel por el color del vertice con 128 = 1.0; el color 0x0000 es transparente.
Nodo: MATRIX de la PS1 (int16 m[3][3] con 4096 = 1.0, int32 t[3]); se aplica de padre a hijo.

Uso: python ino_obj.py H1W                     todos los modelos del nivel
     python ino_obj.py H1W SABdefault          solo los que contengan ese texto
Salida: notas\\modelos\\<nivel>\\<modelo>.obj/.mtl/.png, las paginas de textura pag_*.png y una hoja.
"""
import os
import struct
import sys

import numpy as np
from PIL import Image

import ino
from hoja import hoja

SAL = os.path.join(ino.RAIZ, "notas", "modelos")


class Texturas:
    """Decodifica paginas de textura (256x256) de un .TEX con su paleta, con cache por TPAGE y CLUT."""

    def __init__(self, nivel, registros):
        carpeta = ino.CARPETA.get(nivel[:2]) or ino.CARPETA[nivel[0]]
        ruta = os.path.join(ino.RAIZ, "extraido", "GRAPHICS", carpeta, nivel[:2] + ".TEX")
        # se rellena a la derecha para las paginas pegadas al borde (sus texturas no usan lo que sobra)
        self.vram = np.pad(np.frombuffer(open(ruta, "rb").read(), dtype="<u2").reshape(512, 512), ((0, 0), (0, 256)))
        self.regs = [struct.unpack("<16H", r) for r in registros]
        self.cache = {}

    def _rgb(self, v):
        r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
        return np.stack([r, g, b], -1).astype(float) * (255 / 31), v != 0

    def pagina(self, tpage, clut):
        """(rgb 256x256x3, alfa 256x256) de la pagina vista con esa paleta, o None si no esta en el .TEX."""
        clave = (tpage, clut)
        if clave in self.cache:
            return self.cache[clave]
        px, py, prof = (tpage & 0xF) * 64 - 512, ((tpage >> 4) & 1) * 256, (tpage >> 7) & 3
        cx, cy = (clut & 0x3F) * 16 - 512, (clut >> 6) & 0x1FF
        res = None
        if px >= 0:
            u = np.arange(256)
            if prof == 0:
                pal = self.vram[cy, cx:cx + 16]
                w = self.vram[py:py + 256, px:px + 64][:, u // 4]
                idx = (w >> ((u % 4) * 4)) & 0xF
                val = pal[idx] if cx >= 0 else w
            elif prof == 1:
                pal = self.vram[cy, cx:cx + 256]
                w = self.vram[py:py + 256, px:px + 128][:, u // 2]
                idx = (w >> ((u % 2) * 8)) & 0xFF
                val = pal[idx] if cx >= 0 else w
            else:
                val = self.vram[py:py + 256, px:px + 256]
            if val.shape == (256, 256):
                res = self._rgb(val)
        self.cache[clave] = res
        return res

    def de_triangulo(self, tex_idx):
        h = self.regs[tex_idx]
        return h[6], h[7], h[8] & 0xFF, h[8] >> 8


def aplanar(nodos, mat=np.eye(3), tras=np.zeros(3)):
    """(vertices Nx3, colores Nx3, triangulos Mx3, datos Mx7 = textura y 6 uv) de un arbol de nodos."""
    V, C, T, D = [], [], [], []
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
            D.append(np.array([t[3:10] for t in n["tris"]], dtype=int).reshape(-1, 7))
            base += len(raw)
        hv, hc, ht, hd = aplanar(n["hijos"], mg, tg)
        if len(hv):
            V.append(hv)
            C.append(hc)
            T.append(ht + base)
            D.append(hd)
            base += len(hv)
    if not V:
        return np.zeros((0, 3)), np.zeros((0, 3)), np.zeros((0, 3), dtype=int), np.zeros((0, 7), dtype=int)
    return np.vstack(V), np.vstack(C), np.vstack(T), np.vstack(D)


def uv_de_pagina(tex, d):
    """uv (3x2) del triangulo dentro de su pagina: los del archivo mas la posicion de la textura."""
    tpage, clut, uo, vo = tex.de_triangulo(d[0])
    uv = np.array(d[1:7], dtype=int).reshape(3, 2)
    uv[:, 0] = (uv[:, 0] + uo) & 0xFF
    uv[:, 1] = (uv[:, 1] + vo) & 0xFF
    return tpage, clut, uv


def guardar_obj(carpeta, base, V, C, T, D, tex):
    """OBJ + MTL; cada combinacion de pagina y paleta es un material con su PNG."""
    mtl = []
    grupos = {}
    for k, d in enumerate(D):
        tpage, clut, uv = uv_de_pagina(tex, d)
        grupos.setdefault((tpage, clut), []).append((k, uv))
    with open(os.path.join(carpeta, base + ".obj"), "w") as f:
        f.write(f"mtllib {base}.mtl\n")
        for (x, y, z), (r, g, b) in zip(V, C):
            f.write(f"v {x:.1f} {-y:.1f} {z:.1f} {r / 255:.3f} {g / 255:.3f} {b / 255:.3f}\n")
        nvt = 0
        for (tpage, clut), lista in grupos.items():
            nombre = f"pag_{tpage:04x}_{clut:04x}"
            pag = tex.pagina(tpage, clut)
            if pag is not None and not os.path.exists(os.path.join(carpeta, nombre + ".png")):
                rgb, alfa = pag
                img = np.dstack([rgb, alfa[..., None] * 255]).astype(np.uint8)
                Image.fromarray(img, "RGBA").save(os.path.join(carpeta, nombre + ".png"))
            mtl.append(f"newmtl {nombre}\nKd 1 1 1\n" + (f"map_Kd {nombre}.png\n" if pag is not None else ""))
            f.write(f"usemtl {nombre}\n")
            for k, uv in lista:
                for u, v in uv:
                    f.write(f"vt {(u + 0.5) / 256:.4f} {1 - (v + 0.5) / 256:.4f}\n")
                a, b, c = T[k]
                f.write(f"f {a + 1}/{nvt + 1} {b + 1}/{nvt + 2} {c + 1}/{nvt + 3}\n")
                nvt += 3
    open(os.path.join(carpeta, base + ".mtl"), "w").write("\n".join(mtl))


def dibujar(V, C, T, D=None, tex=None, ancho=480, alto=360, giro=0.6, inclinacion=0.45, centro=None, esc=None):
    """Render por software con z-buffer y texturas de la PS1. Y de la PS1 apunta hacia abajo.
    centro y esc fijos sirven para animaciones (si no, se encuadra cada imagen por separado)."""
    img = np.full((alto, ancho, 3), 30, dtype=float)
    if len(T) == 0:
        return Image.fromarray(img.astype(np.uint8))
    P = V.copy()
    P[:, 1] = -P[:, 1]
    P -= (P.max(0) + P.min(0)) / 2 if centro is None else centro
    cg, sg, ci, si = np.cos(giro), np.sin(giro), np.cos(inclinacion), np.sin(inclinacion)
    P = P @ np.array([[cg, 0, -sg], [0, 1, 0], [sg, 0, cg]]).T
    P = P @ np.array([[1, 0, 0], [0, ci, si], [0, -si, ci]]).T
    if esc is None:
        esc = 0.9 * min(ancho, alto) / max(np.ptp(P[:, 0]), np.ptp(P[:, 1]), 1)
    sx = P[:, 0] * esc + ancho / 2
    sy = -P[:, 1] * esc + alto / 2
    z = P[:, 2]
    zbuf = np.full((alto, ancho), np.inf)
    col = C.copy()
    sin_luz = (col > 250).all()
    if sin_luz:
        col = np.full_like(col, 128.0)       # personajes: la luz la pone el juego al vuelo
    for k, (a, b, c) in enumerate(T):
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
        vc = w0[..., None] * col[a] + w1[..., None] * col[b] + w2[..., None] * col[c]
        texel, alfa = None, None
        if tex is not None:
            tpage, clut, uv = uv_de_pagina(tex, D[k])
            pag = tex.pagina(tpage, clut)
            if pag is not None:
                u = np.clip((w0 * uv[0, 0] + w1 * uv[1, 0] + w2 * uv[2, 0]).astype(int), 0, 255)
                v = np.clip((w0 * uv[0, 1] + w1 * uv[1, 1] + w2 * uv[2, 1]).astype(int), 0, 255)
                texel, alfa = pag[0][v, u], pag[1][v, u]
                ok &= alfa
        if texel is not None:
            rgb = texel * vc / 128.0
            if sin_luz:
                n = np.cross(P[b] - P[a], P[c] - P[a])
                rgb *= 0.55 + 0.45 * abs(n[2]) / (np.linalg.norm(n) + 1e-9)
        else:
            n = np.cross(P[b] - P[a], P[c] - P[a])
            rgb = vc * (0.45 + 0.55 * abs(n[2]) / (np.linalg.norm(n) + 1e-9)) * 1.6
        zona[ok] = zz[ok]
        img[y0:y1, x0:x1][ok] = np.clip(rgb[ok], 0, 255)
    return Image.fromarray(img.astype(np.uint8))


if __name__ == "__main__":
    nivel = sys.argv[1]
    filtro = sys.argv[2] if len(sys.argv) > 2 else ""
    s = ino.leer_ino(nivel)
    tex = Texturas(nivel, s["texturas"])
    carpeta = os.path.join(SAL, nivel)
    os.makedirs(carpeta, exist_ok=True)
    rutas = []
    vistos = set()
    for nom, nodos in s["modelos"]:
        base = os.path.splitext(os.path.basename(nom.replace("\\", "/")))[0]
        if filtro.lower() not in base.lower() or base in vistos or not nodos:
            continue
        vistos.add(base)
        V, C, T, D = aplanar(nodos)
        guardar_obj(carpeta, base, V, C, T, D, tex)
        png = os.path.join(carpeta, base + ".png")
        dibujar(V, C, T, D, tex).save(png)
        rutas.append(png)
        print(f"{base}: {len(V)} vertices, {len(T)} triangulos")
    if rutas:
        hoja(os.path.join(carpeta, "hoja.png"), 4, rutas)
