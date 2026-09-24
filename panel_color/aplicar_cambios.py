"""Toma un cambios_*.json exportado por panel_color.py y los aplica a los 14 .TEX del juego,
igual que hace mod_bruja.py disco. Cada cambio esta guardado como desplazamiento en bytes desde
el ancla de "piernas" (no como posicion de VRAM), asi que se puede aplicar a cualquier nivel: se
busca esa misma ancla (PIERNAS, comprobada identica en los 14 .TEX) y se escribe cada color ahi.

Uso: python aplicar_cambios.py cambios_20260919_153000.json
Arma disco\\sabrina_panel (Track 01).bin y mods\\sabrina_panel.ppf.
"""
import glob
import json
import os
import struct
import sys

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(RAIZ, "scripts"))

from mod_rosa import PIERNAS, FILA_DESDE  # noqa: E402


def cargar(ruta):
    with open(ruta, encoding="utf-8") as f:
        datos = json.load(f)
    return [(c["grupo"], c["indice"], c["delta"], int(c["nuevo"], 16)) for c in datos["cambios"]]


def recolorear_tex(datos, cambios):
    """Devuelve (datos nuevos, encontrado, aplicados)."""
    d = bytearray(datos)
    off = d.find(PIERNAS, FILA_DESDE * 1024)
    if off < 0:
        return bytes(d), False, 0
    aplicados = 0
    for _grupo, _indice, delta, nuevo in cambios:
        struct.pack_into("<H", d, off + delta, nuevo)
        aplicados += 1
    return bytes(d), True, aplicados


def cambios_disco(raiz, cambios):
    res = {}
    for ruta in sorted(glob.glob(os.path.join(raiz, "extraido", "GRAPHICS", "*", "*.TEX"))):
        nuevo, hecho, n = recolorear_tex(open(ruta, "rb").read(), cambios)
        if hecho:
            res[os.path.relpath(ruta, os.path.join(raiz, "extraido"))] = nuevo
            print(f"  {os.path.basename(ruta)}: {n} colores del panel")
    return res


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("uso: python aplicar_cambios.py cambios_AAAAMMDD_HHMMSS.json")
    ruta_json = sys.argv[1]
    if not os.path.isabs(ruta_json) and not os.path.exists(ruta_json):
        ruta_json = os.path.join(os.path.dirname(os.path.abspath(__file__)), ruta_json)
    cambios = cargar(ruta_json)
    print(f"{len(cambios)} colores en {ruta_json}")

    import disco
    import ppf

    salidas = cambios_disco(disco.RAIZ, cambios)
    if not salidas:
        sys.exit("no se encontro la paleta de piernas en ningun .TEX; hace falta extraido\\ (-Taller)")
    pista = os.path.join(disco.DISCO, "sabrina_panel (Track 01).bin")
    disco.parchar(salidas, pista)
    disco.cue_mod(os.path.join(disco.DISCO, "sabrina_panel.cue"), pista)
    salida = os.path.join(disco.RAIZ, "mods", "sabrina_panel.ppf")
    c, t = ppf.crear(disco.PISTA1, pista, salida, "Sabrina, colores del panel")
    print(f"disco {pista}")
    print(f"parche {salida}: {t} bytes, {c} bytes cambiados")
