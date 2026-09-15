"""Anima a Sabrina con las animaciones del juego y guarda un GIF.

Animaciones (.ANI, ver ani.py): cada cuadro trae 3 int16 (desplazamiento del cuerpo) y 3 bytes por hueso
(rotacion x y z, 256 = una vuelta). Los huesos van en el orden de las piezas del modelo recorridas en
profundidad. El juego arma la matriz de cada pieza como Rx * Ry * Rz (FUN_8001e364) y la traslacion es
la de la pieza en el modelo. Sabrina son dos modelos: piernas (8 huesos, animaciones SAB...) y torso
(9 huesos, SAB1...), que se animan juntos con el mismo numero de animacion + 21.

Uso: python animar.py SABRun [traje]      traje: default, egypt, japan, stone, west
     python animar.py todas               un GIF por cada animacion de Sabrina (traje default)
     python animar.py S3W RockTroll STONE TROLLtaunt     cualquier personaje: nivel, modelo, .ANI, animacion
Los nombres de las animaciones salen de las tablas de punteros del ejecutable (anims_nombres.py).
Salida: notas\\modelos\\animaciones\\<nombre>.gif
"""
import os
import re
import struct
import sys

import numpy as np

import ani
import ino
from ino_obj import SAL, Texturas, dibujar

OUT = os.path.join(SAL, "animaciones")


def nombres_sabrina():
    d = ino.EXE
    fin = d.find(b"Sabrina.ANI")
    ini = d.rfind(b"\0" * 8, 0, fin - 2000)
    return [m.group().decode() for m in re.finditer(rb"[A-Za-z0-9_]+\.(?:MAO|mao)", d[ini:fin]) if b"\\" not in m.group()]


def rot(bx, by, bz):
    def a(b):
        return (b if b < 128 else b - 256) / 256 * 2 * np.pi
    cx, sx, cy, sy, cz, sz = np.cos(a(bx)), np.sin(a(bx)), np.cos(a(by)), np.sin(a(by)), np.cos(a(bz)), np.sin(a(bz))
    rx = np.array([[1, 0, 0], [0, cx, -sx], [0, sx, cx]])
    ry = np.array([[cy, 0, sy], [0, 1, 0], [-sy, 0, cy]])
    rz = np.array([[cz, -sz, 0], [sz, cz, 0], [0, 0, 1]])
    return rx @ ry @ rz


def aplanar_anim(nodos, angulos, raiz_tras, cont=None, mat=np.eye(3), tras=np.zeros(3)):
    """Como ino_obj.aplanar, pero con la rotacion de cada pieza tomada del cuadro de animacion."""
    if cont is None:
        cont = [0]
    V, C, T, D = [], [], [], []
    base = 0
    for n in nodos:
        k = cont[0]
        cont[0] += 1
        m = rot(*angulos[k]) if k < len(angulos) else np.array(n["matriz"]).reshape(3, 3) / 4096
        t = np.array(n["tras"], dtype=float) + (raiz_tras if k == 0 else 0)
        mg, tg = mat @ m, mat @ t + tras
        if n["verts"]:
            raw = np.array([struct.unpack("<3hh3Bx", v) for v in n["verts"]], dtype=float)
            V.append(raw[:, :3] @ mg.T + tg)
            C.append(raw[:, 4:7])
            T.append(np.array([x[:3] for x in n["tris"]], dtype=int).reshape(-1, 3) + base)
            D.append(np.array([x[3:10] for x in n["tris"]], dtype=int).reshape(-1, 7))
            base += len(raw)
        hv, hc, ht, hd = aplanar_anim(n["hijos"], angulos, raiz_tras, cont, mg, tg)
        if len(hv):
            V.append(hv), C.append(hc), T.append(ht + base), D.append(hd)
            base += len(hv)
    if not V:
        return np.zeros((0, 3)), np.zeros((0, 3)), np.zeros((0, 3), dtype=int), np.zeros((0, 7), dtype=int)
    return np.vstack(V), np.vstack(C), np.vstack(T), np.vstack(D)


def cuadro(anim, f):
    p = anim["pistas"][f]
    ang = [tuple(p["datos"][k * 3:k * 3 + 3]) for k in range(anim["cuadros"])]
    return ang, np.array(p["cab"], dtype=float)


def animar(nombre, traje="default"):
    s = ino.leer_ino("H1W")
    tex = Texturas("H1W", s["texturas"])
    mods = {nom.replace("\\", "/").split("/")[-1][:-4].lower(): h for nom, h in s["modelos"]}
    piernas, torso = mods[f"sab{traje}"], mods[f"sab{traje}1"]
    nombres = nombres_sabrina()
    anims, _ = ani.leer_ani("SABRINA")
    i = nombres.index(nombre + (".MAO" if nombre + ".MAO" in nombres else ".mao"))
    j = nombres.index(re.sub(r"^SAB", "SAB1", nombres[i])) if nombres[i].startswith("SAB") else None
    a_p, a_t = anims[i], anims[j] if j is not None else None
    marcos = []
    for f in range(len(a_p["pistas"])):
        ang, tr = cuadro(a_p, f)
        V1, C1, T1, D1 = aplanar_anim(piernas, ang, tr)
        if a_t is not None:
            ang2, tr2 = cuadro(a_t, min(f, len(a_t["pistas"]) - 1))
            V2, C2, T2, D2 = aplanar_anim(torso, ang2, tr2)
            V1, C1, T1, D1 = np.vstack([V1, V2]), np.vstack([C1, C2]), np.vstack([T1, T2 + len(V1)]), np.vstack([D1, D2])
        marcos.append((V1, C1, T1, D1))
    todos = np.vstack([m[0] for m in marcos]) * np.array([1, -1, 1])
    centro = (todos.max(0) + todos.min(0)) / 2
    esc = 0.8 * 360 / max(np.ptp(todos[:, 1]), np.ptp(todos[:, 0]), 1)
    imgs = [dibujar(V, C, T, D, tex, ancho=320, alto=360, giro=2.4, inclinacion=0.15, centro=centro, esc=esc)
            for V, C, T, D in marcos]
    os.makedirs(OUT, exist_ok=True)
    ruta = os.path.join(OUT, f"{nombre}_{traje}.gif")
    imgs[0].save(ruta, save_all=True, append_images=imgs[1:], duration=66, loop=0)
    return ruta, imgs


def animar_personaje(nivel, modelo, mundo, anim, giro=2.4, inclinacion=0.15):
    """Anima un modelo de un solo cuerpo (enemigos, Salem, Chaos) con una animacion de <mundo>.ANI."""
    from anims_nombres import nombres_de
    s = ino.leer_ino(nivel)
    tex = Texturas(nivel, s["texturas"])
    mods = {nom.replace("\\", "/").split("/")[-1][:-4].lower(): h for nom, h in s["modelos"]}
    nodos = mods[modelo.lower()]
    anims, _ = ani.leer_ani(mundo)
    nombres = [n.split("\\")[-1][:-4].lower() for n in nombres_de(mundo.upper())]
    a = anims[nombres.index(anim.lower())]
    marcos = []
    for f in range(len(a["pistas"])):
        ang, tr = cuadro(a, f)
        marcos.append(aplanar_anim(nodos, ang, tr))
    todos = np.vstack([m[0] for m in marcos]) * np.array([1, -1, 1])
    centro = (todos.max(0) + todos.min(0)) / 2
    esc = 0.8 * 360 / max(np.ptp(todos[:, 1]), np.ptp(todos[:, 0]), np.ptp(todos[:, 2]), 1)
    imgs = [dibujar(V, C, T, D, tex, ancho=360, alto=360, giro=giro, inclinacion=inclinacion, centro=centro, esc=esc)
            for V, C, T, D in marcos]
    os.makedirs(OUT, exist_ok=True)
    ruta = os.path.join(OUT, f"{anim}.gif")
    imgs[0].save(ruta, save_all=True, append_images=imgs[1:], duration=66, loop=0)
    return ruta, imgs


if __name__ == "__main__":
    if len(sys.argv) == 5:           # nivel modelo mundo animacion
        ruta, imgs = animar_personaje(*sys.argv[1:5])
        print(ruta, len(imgs), "cuadros")
        sys.exit()
    if sys.argv[1] == "todas":
        for n in nombres_sabrina():
            if n.startswith("SAB") and not n.startswith("SAB1"):
                print(animar(n[:-4])[0])
    else:
        ruta, imgs = animar(sys.argv[1], *(sys.argv[2:3]))
        print(ruta, len(imgs), "cuadros")
