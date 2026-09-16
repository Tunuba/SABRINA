"""Segunda ronda de cobertura: suma capturas a las que ya hay, en situaciones distintas.

La primera ronda (capturar_todo.py) guardo las primeras llamadas de cada funcion, casi siempre al cargar el
nivel. Esta pone en cada funcion del juego una captura espaciada (las llamadas 1, 4, 16, 64...) que se suma
a las que ya tiene, y juega otro recorrido: chocar contra paredes, caer, atacar, pausar y los menus, en
niveles que la primera ronda no visito.

Uso: python capturar_mas.py [n por funcion] [niveles separados por comas] [--solo F1,F2]
     python capturar_mas.py 3 5,8,11,16
"""
import os
import sys
import time
import urllib.error

from emu import RAIZ, Emu
from explorar import CUE, estado, recorrer

args = [a for a in sys.argv[1:] if not a.startswith("--")]
n = int(args[0]) if args else 3
# 0 menu, 1-3 Stone, 4-6 Egypt, 7-9 Japan, 10-12 West, 13 HUB, 14 Chaos; la primera ronda vio 3, 4, 7, 10,
# 14 y el HUB
niveles = [int(x) for x in args[1].split(",")] if len(args) > 1 else [0, 1, 5, 8, 11]
solo = set(sys.argv[sys.argv.index("--solo") + 1].split(",")) if "--solo" in sys.argv else None
MAXIMO = 12                               # capturas por funcion como mucho (2 MB cada una)
CAPT = os.path.join(RAIZ, "decomp", "capturas")

funcs = []
for l in open(os.path.join(RAIZ, "decomp", "funciones_juego.tsv")):
    d, tam, nom = l.split()
    if not nom.startswith(("caseD_", "switchD_", "LAB_")) and (solo is None or nom in solo):
        funcs.append((int(d, 16), nom))

# contra las paredes (largo hacia cada lado), saltos, ataques, hechizos y los menus
JUGAR = ("UP:90 LEFT:60 UP:60 RIGHT:90 DOWN:60 CROSS w10 UP+CROSS:30 w30 SQUARE w20 CIRCLE w20 "
         "TRIANGLE w30 R1 w10 L1 w10 R2 w10 L2 w10 LEFT:90 UP:90 CROSS w40 START w30 DOWN w10 DOWN w10 "
         "CROSS w30 CIRCLE w20 START w40 SELECT w30 SELECT w30 RIGHT:120 UP:120 CROSS w40")


def cuantas(nom):
    carpeta = os.path.join(CAPT, nom)
    return len([f for f in os.listdir(carpeta) if f.endswith(".regs")]) if os.path.isdir(carpeta) else 0


t0 = time.time()
antes = {nom: cuantas(nom) for _, nom in funcs}
with Emu(iso=CUE, log="capturar_mas.log", extra=("-fastboot",), depurar=True) as e:
    e.cargar(estado("saltar"))
    e.esperar(2)
    puestas = 0
    for d, nom in funcs:
        ya = antes[nom]
        if ya >= MAXIMO:
            continue
        carpeta = os.path.join(CAPT, nom)
        os.makedirs(carpeta, exist_ok=True)
        try:
            e.lua("capturar", a=d, n=min(n, MAXIMO - ya), dir=carpeta, inicio=ya, geo=1)
            puestas += 1
        except urllib.error.HTTPError:
            pass
    print(f"{puestas} capturas puestas en {time.time() - t0:.0f} s", flush=True)
    recorrer(e, "mas_hub", JUGAR)
    for nivel in niveles:
        e.eval(f"wr8(0x8007CA00, {nivel}); wr16(0x8007C9FC, 0); return 'ok'")
        recorrer(e, f"mas_{nivel}", "w1300 " + JUGAR)
        print(f"nivel {nivel} listo, {time.time() - t0:.0f} s", flush=True)
nuevas = sum(cuantas(nom) - antes[nom] for _, nom in funcs)
primera = [nom for _, nom in funcs if antes[nom] == 0 and cuantas(nom) > 0]
sin = [nom for _, nom in funcs if cuantas(nom) == 0]
print(f"{nuevas} capturas nuevas; {len(primera)} funciones se capturan por primera vez; "
      f"{len(sin)} siguen sin capturas ({time.time() - t0:.0f} s)")
