"""Decodifica los objetos de cada nivel (WRLDDATA\\*.BIN) y les pone nombre usando el ejecutable.

Formato de un objeto (0x9C bytes), leido de FUN_800246a0 (WobjCode.c):
  +0x00 +0x04 +0x08  posicion x y z (int32, las mismas unidades que Sabrina en su objeto +0x24)
  +0x0C              tipo (int16)
  +0x0E +0x10 +0x12  rotacion x y z (int16, 4096 = una vuelta)
  +0x14 +0x16 +0x18  escala x y z (int16, 4096 = 1.0)
  +0x1C              127 bytes de parametros propios del tipo
Los tipos 4, 0x12, 0x13 y 0x17 los trata aparte FUN_80047e48 (el 0x17 trae 44100 Hz: sonido).
El resto usa la tabla de clases del nivel: puntero en 0x80074858 + 4*nivel, registros de 0x54 bytes
por tipo; la primera palabra es la funcion que maneja el objeto y el int16 en +0x22 el modelo.

Uso: python wobj.py            resumen de todos los niveles en notas\\OBJETOS.md
     python wobj.py S3W        lista los objetos de un nivel
"""
import csv
import glob
import os
import struct
import sys
from collections import Counter, defaultdict

import ino

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = open(os.path.join(RAIZ, r"extraido\SLUS_012.08"), "rb").read()
NIVELES = ["FRW", "S1W", "S2W", "S3W", "E1W", "E2W", "E3W", "J1W", "J2W", "J3W", "W1W", "W2W", "W3W", "H1W", "C1W"]
ESPECIALES = {4: "especial 4", 0x12: "especial 0x12", 0x13: "especial 0x13", 0x17: "sonido"}


def u32(direccion):
    o = direccion - 0x80010000 + 0x800
    if not (0x800 <= o < len(EXE) - 4):
        return None
    return struct.unpack_from("<I", EXE, o)[0]


def s16(direccion):
    o = direccion - 0x80010000 + 0x800
    return struct.unpack_from("<h", EXE, o)[0]


def leer_nivel(nombre):
    carpeta = {"FR": "FRONT", "H1": "HUB", "C1": "CHAOS"}.get(nombre[:2], {"S": "STONE", "E": "EGYPT", "J": "JAPAN", "W": "WEST"}.get(nombre[0]))
    d = open(os.path.join(RAIZ, "extraido", "WRLDDATA", carpeta, nombre + ".BIN"), "rb").read()
    n = struct.unpack_from("<i", d, 0)[0]
    objs = []
    for k in range(n):
        o = 4 + k * 0x9C
        x, y, z = struct.unpack_from("<3i", d, o)
        tipo, rx, ry, rz, sx, sy, sz = struct.unpack_from("<7h", d, o + 0x0C)
        objs.append(dict(i=k, x=x, y=y, z=z, tipo=tipo, rot=(rx, ry, rz), esc=(sx, sy, sz),
                         params=d[o + 0x1C:o + 0x9C]))
    return objs


def leer_rutas(nombre):
    """Puntos de ruta de patrulla (segunda lista del .BIN, 24 bytes): x y z, int16 numero, anterior y
    siguiente (0 = ninguno), relleno. El juego los carga en 0x800D58A4."""
    carpeta = {"FR": "FRONT", "H1": "HUB", "C1": "CHAOS"}.get(nombre[:2], {"S": "STONE", "E": "EGYPT", "J": "JAPAN", "W": "WEST"}.get(nombre[0]))
    d = open(os.path.join(RAIZ, "extraido", "WRLDDATA", carpeta, nombre + ".BIN"), "rb").read()
    p = 4 + struct.unpack_from("<i", d, 0)[0] * 0x9C
    m = struct.unpack_from("<i", d, p)[0]
    res = []
    for k in range(m):
        x, y, z, num, ant, sig = struct.unpack_from("<3i3h", d, p + 4 + k * 0x18)
        res.append(dict(num=num, x=x, y=y, z=z, anterior=ant, siguiente=sig))
    return res


def params_enemigo(o):
    """Parametros de un enemigo (FUN_80044f50 y parecidas): +00 int16 primer punto de ruta (0 o -1 = quieto),
    +04 y +08 dos radios en 16.16 que el juego eleva al cuadrado (vista y ataque)."""
    ruta, r1, r2 = struct.unpack_from("<hxxii", o["params"], 0)
    return dict(ruta=ruta, radio1=r1 / 65536, radio2=r2 / 65536)


ENEMIGOS = (2, 14, 15, 16, 17, 22)


def textos_por_funcion():
    """{nombre de funcion: [textos que usa]} desde el export de Ghidra."""
    res = defaultdict(list)
    with open(os.path.join(RAIZ, r"notas\ghidra\textos.tsv"), encoding="utf-8") as f:
        for fila in csv.reader(f, delimiter="\t"):
            if len(fila) < 3:
                continue
            for quien in fila[2].split():
                res[quien.split("@")[0]].append(fila[1])
    return res


def clase(nivel, tipo):
    tabla = u32(0x80074858 + 4 * nivel)
    if not tabla:
        return None, None
    reg = tabla + tipo * 0x54
    return u32(reg), s16(reg + 0x22)


def nombre_tipo(nivel, tipo, textos):
    if tipo in ESPECIALES:
        return ESPECIALES[tipo]
    fn, modelo = clase(nivel, tipo)
    if fn is None:
        return "?"
    usados = [t for t in textos.get(f"FUN_{fn:08x}", []) if "." in t or "\\" in t]
    pista = ", ".join(sorted(set(usados))[:3])
    return f"funcion {fn:08x} modelo {modelo}" + (f" ({pista})" if pista else "")


if __name__ == "__main__":
    textos = textos_por_funcion()
    if len(sys.argv) > 1:
        nv = NIVELES.index(sys.argv[1])
        lista = ino.modelos_del_nivel(nv)
        for o in leer_nivel(sys.argv[1]):
            fn, m = clase(nv, o["tipo"])
            modelo = lista[m - 1].split("\\")[-1] if m and 0 < m <= len(lista) else "-"
            extra = ""
            if o["tipo"] in ENEMIGOS:
                p = params_enemigo(o)
                extra = f"  ruta {p['ruta']} radios {p['radio1']:.1f} {p['radio2']:.1f}"
            print(f"{o['i']:3d} tipo {o['tipo']:3d}  pos {o['x']:>9d} {o['y']:>8d} {o['z']:>9d}  {modelo}{extra}")
        rutas = leer_rutas(sys.argv[1])
        print(f"{len(rutas)} puntos de ruta")
        sys.exit()
    lineas = ["# Objetos de cada nivel (WRLDDATA)", "", "Generado por `scripts\\wobj.py`. Tipo, cantidad y quien lo maneja.", ""]
    for nv, nombre in enumerate(NIVELES):
        objs = leer_nivel(nombre)
        cuenta = Counter(o["tipo"] for o in objs)
        lineas.append(f"## {nombre} ({len(objs)} objetos)")
        lineas.append("")
        for tipo, c in sorted(cuenta.items()):
            lineas.append(f"- tipo {tipo}: {c}, {nombre_tipo(nv, tipo, textos)}")
        lineas.append("")
    open(os.path.join(RAIZ, r"notas\OBJETOS.md"), "w", encoding="utf-8").write("\n".join(lineas))
    print("\n".join(lineas[:60]))
