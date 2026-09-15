"""Teletransporta a Sabrina junto al primer objeto de cada tipo de un nivel y captura, para ver que es.

Uso: python visitar.py <estado_en_el_nivel> <nivel, ej S3W> [dz]
  dz: cuanto se aleja Sabrina del objeto en z antes de capturar (por defecto -300000)
Posicion de Sabrina: objeto en 0x8007CAF8, +0x24 +0x28 +0x2C.
Hoja en notas\\capturas\\visita_<nivel>_hoja.png
"""
import os
import sys

from emu import RAIZ, Emu
from explorar import CUE, estado
from hoja import hoja
from wobj import leer_nivel

est, nivel = sys.argv[1], sys.argv[2]
dz = int(sys.argv[3]) if len(sys.argv) > 3 else -300000
objs = leer_nivel(nivel)
primeros = {}
for o in objs:
    primeros.setdefault(o["tipo"], o)
rutas = []
with Emu(iso=CUE, log="visitar.log", extra=("-fastboot",)) as e:
    for tipo, o in sorted(primeros.items()):
        e.cargar(estado(est))
        e.esperar(3)
        e.eval(f"local p = rd32(0x8007CAF8); wr32(p + 0x24, {o['x']}); wr32(p + 0x28, {o['y'] - 60000}); "
               f"wr32(p + 0x2c, {o['z'] + dz}); return 'ok'")
        e.esperar(40)
        r = os.path.join(RAIZ, r"notas\capturas", f"visita_{nivel}_tipo{tipo:02d}.png")
        e.captura(r)
        rutas.append(r)
        print(f"tipo {tipo:3d} objeto {o['i']:3d} en {o['x']} {o['y']} {o['z']}", flush=True)
hoja(os.path.join(RAIZ, r"notas\capturas", f"visita_{nivel}_hoja.png"), 5, rutas)
