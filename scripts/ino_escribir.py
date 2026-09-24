"""Escritor de .INO, inverso exacto de ino.py (ino.leer_ino): a partir de la misma estructura que
devuelve leer_ino (con o sin cambios), arma los bytes del archivo tal como los leeria el juego.

Comprobado con un viaje de ida y vuelta: leer H1W.INO, reescribirlo sin cambiar nada, y salio
identico byte a byte al original hasta donde el juego realmente lee (la cola que no lee nunca se
compara, no hace falta que coincida -ver 'Por descifrar' en notas/FORMATOS.md).

Uso: python ino_escribir.py H1W    viaje de ida y vuelta, para confirmar que el formato esta bien
"""
import os
import struct
import sys

import ino


def escribir_nodo(n):
    cabeza = struct.pack("<hhh", len(n["verts"]), len(n["tris"]), len(n["hijos"]))
    cabeza += struct.pack("<9h2x3i", *n["matriz"], *n["tras"])
    nombre_b = n["nombre"].encode("ascii")
    cabeza += struct.pack("<h", len(nombre_b)) + nombre_b
    hijos_b = b"".join(escribir_nodo(h) for h in n["hijos"])
    tris_b = b"".join(struct.pack("<4i6B6B", *t) for t in n["tris"])
    verts_b = b"".join(n["verts"])  # ya son los 12 bytes crudos
    return cabeza + hijos_b + tris_b + verts_b


def escribir_modelo(nodos):
    """Los hermanos de nivel superior de un modelo, con el marcador -1 de fin de lista."""
    return b"".join(escribir_nodo(n) for n in nodos) + struct.pack("<h", -1)


def escribir_ino(s):
    g = s["cuadricula"]
    out = struct.pack("<4hi", g["A"], g["B"], g["ancho"], g["alto"], g["C"])
    out += g["celdas"] + g["listas"] + g["indices"]
    out += struct.pack("<H", len(s["sec2"])) + b"".join(s["sec2"])
    out += struct.pack("<h", len(s["texturas"])) + b"".join(s["texturas"])
    out += s["tabla"]
    for _nombre, nodos in s["modelos"]:
        out += escribir_modelo(nodos)
    out += struct.pack("<H", len(s["sec6"])) + b"".join(s["sec6"])
    out += struct.pack("<H", len(s["particulas"])) + b"".join(s["particulas"])
    return out


if __name__ == "__main__":
    nivel = sys.argv[1] if len(sys.argv) > 1 else "H1W"
    s = ino.leer_ino(nivel)
    ruta = os.path.join(ino.RAIZ, "extraido", "GRAPHICS",
                         ino.CARPETA.get(nivel[:2]) or ino.CARPETA[nivel[0]], nivel + ".INO")
    original = open(ruta, "rb").read()
    reescrito = escribir_ino(s)
    hasta = len(reescrito)
    print(f"original {len(original)} bytes, reescrito {hasta} bytes (sin la cola de {s['sobra']} bytes)")
    if original[:hasta] == reescrito:
        print("IDENTICO byte a byte hasta donde el juego lee")
    else:
        for i in range(min(len(original), hasta)):
            if original[i] != reescrito[i]:
                print(f"DISTINTO en el byte {i} (0x{i:x}): original={original[i]:02x} reescrito={reescrito[i]:02x}")
                break
