"""Capturas para las funciones que no tienen, paseando a Sabrina por todo el nivel: en cada nivel la pone en
una cuadricula de puntos (escribe su x y su z) y espera un rato en cada uno, asi se activan los objetos de
todas las celdas. Un solo emulador, sin ventana.

Uso: py capt_paseo.py <lista.txt> [niveles separados por comas] [paso en celdas] [cuadros por punto] [n]
"""
import os
import sys
import time
import urllib.error

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from emu import RAIZ, Emu
from explorar import CUE, estado

lista = sys.argv[1]
niveles = [int(x) for x in sys.argv[2].split(",")] if len(sys.argv) > 2 else list(range(1, 15))
paso = int(sys.argv[3]) if len(sys.argv) > 3 else 8          # en celdas de la cuadricula (64 x 64)
cuadros = int(sys.argv[4]) if len(sys.argv) > 4 else 40
n = int(sys.argv[5]) if len(sys.argv) > 5 else 2
CAPT = os.path.join(RAIZ, "decomp", "capturas")
solo = set(open(lista).read().split())
funcs = [(int(d, 16), nom) for d, tam, nom in (l.split() for l in open(os.path.join(RAIZ, "decomp", "funciones_juego.tsv")))
         if nom in solo]


def cuantas(nom):
    c = os.path.join(CAPT, nom)
    return len([f for f in os.listdir(c) if f.endswith(".regs")]) if os.path.isdir(c) else 0


t0 = time.time()
antes = {nom: cuantas(nom) for _, nom in funcs}
with Emu(iso=CUE, log="capt_paseo.log", extra=("-fastboot",), depurar=True) as e:
    e.cargar(estado("saltar"))
    e.esperar(2)
    for d, nom in funcs:
        if antes[nom] < n:
            os.makedirs(os.path.join(CAPT, nom), exist_ok=True)
            try:
                e.lua("capturar", a=d, n=n - antes[nom], dir=os.path.join(CAPT, nom), inicio=antes[nom], geo=1)
            except urllib.error.HTTPError:
                pass
    for nivel in niveles:
        e.eval(f"wr8(0x8007CA00, {nivel}); wr16(0x8007C9FC, 0); return 'ok'")
        e.esperar(1300)
        # la celda es ((x >> 16) + 0x80) >> 2: de -0x80 a 0x7F en la parte alta de x y de z
        for cz in range(0, 64, paso):
            for cx in range(0, 64, paso):
                x = ((cx * 4) - 0x80 + 2) << 16
                z = (0x7F - (cz * 4) - 0x80 + 2) << 16
                e.eval(f"local s = rd32(0x8007CAF8); if s ~= 0 then wr32(s + 0x24, {x & 0xFFFFFFFF}); "
                       f"wr32(s + 0x2C, {z & 0xFFFFFFFF}) end; return 'ok'")
                e.esperar(cuadros)
        print(f"nivel {nivel} listo, {time.time() - t0:.0f} s", flush=True)
nuevas = [nom for _, nom in funcs if antes[nom] == 0 and cuantas(nom) > 0]
print(f"{len(nuevas)} funciones capturadas por primera vez ({time.time() - t0:.0f} s): {' '.join(nuevas)}")
