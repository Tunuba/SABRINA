"""Pone nombre a las animaciones de cada .ANI y comprueba cada una contra su modelo.

En el ejecutable, antes de cada "<Mundo>.ANI" esta la lista de nombres .MAO de sus animaciones, en orden.
Para cada animacion se busca el modelo del mismo personaje (el nombre del .MAO sin la accion) en el .INO
de un nivel de ese mundo, y se compara la cantidad de huesos con la de piezas del modelo.

Uso: python anims_nombres.py            resumen de todos los .ANI
     python anims_nombres.py STONE       detalle de uno
"""
import re
import sys

import ani
import ino

MUNDO_NIVEL = {"SABRINA": "H1W", "HUB": "H1W", "STONE": "S1W", "EGYPT": "E1W", "JAPAN": "J1W", "WEST": "W1W",
               "CHAOS": "C1W"}


# Tablas de punteros a los nombres, en el orden de las animaciones dentro de cada .ANI
TABLAS = {"SABRINA": (0x8006DA34, 47), "EGYPT": (0x8006DEC8, 43), "STONE": (0x8006E30C, 38),
          "JAPAN": (0x8006E774, 43), "WEST": (0x8006EC18, 44), "CHAOS": (0x8006ED94, 8), "HUB": (0x8006EE40, 6)}


def nombres_de(ani_nombre):
    inicio, n = TABLAS[ani_nombre]
    return [ino._cadena(ino._u32(inicio + 4 * k)) for k in range(n)]


def piezas(nodos):
    return sum(1 + piezas(n["hijos"]) for n in nodos)


def modelos_por_nombre(nivel):
    s = ino.leer_ino(nivel)
    res = {}
    for nom, nodos in s["modelos"]:
        base = nom.replace("\\", "/").split("/")[-1][:-4].lower()
        res.setdefault(base, piezas(nodos))
    return res


def revisar(mundo, detalle=False):
    anims, sobra = ani.leer_ani(mundo)
    nombres = nombres_de(mundo)[-len(anims):]
    mods = modelos_por_nombre(MUNDO_NIVEL[mundo])
    ok = mal = sin = 0
    for a, n in zip(anims, nombres):
        persona = re.sub(r"(stand|walk|run|attack|vanish|intro|guard|behit|idle|jump|die|hit|zap|swim|pre|throw|"
                         r"fly|land|launch|shoot|dance|fall|react|spin|talk|wave|sit|laugh|point|push|roll).*$", "",
                         n.split("\\")[-1][:-4], flags=re.I).lower()
        if persona.startswith("sab1"):
            persona = "sabdefault1"          # torso de Sabrina
        elif persona.startswith("sab"):
            persona = "sabdefault"
        elif persona.startswith("sal"):
            persona = "salwaist"             # Salem
        cand = [m for m in mods if persona and (m == persona or persona in m)]
        if persona in mods:
            cand = [persona]
        huesos = a["cuadros"]
        match = [m for m in cand if mods[m] == huesos]
        if match:
            ok += 1
        elif cand:
            mal += 1
        else:
            sin += 1
        if detalle:
            estado = "ok " + match[0] if match else ("NO " + ",".join(f"{m}:{mods[m]}" for m in cand) if cand else "sin modelo")
            print(f"  {n:34s} {len(a['pistas']):3d} cuadros {huesos:2d} huesos  {estado}")
    print(f"{mundo}: {len(anims)} animaciones, {len(nombres)} nombres, huesos iguales al modelo en {ok}, "
          f"distintos en {mal}, sin modelo en {sin}")


if __name__ == "__main__":
    if len(sys.argv) > 1:
        revisar(sys.argv[1].upper(), True)
    else:
        for m in MUNDO_NIVEL:
            revisar(m)
