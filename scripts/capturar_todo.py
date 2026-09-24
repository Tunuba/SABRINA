"""Ronda de cobertura: pone una captura en cada funcion del juego y juega un recorrido por varios niveles.

Cada funcion guarda sus primeras n llamadas (memoria y registros) en decomp\\capturas\\<funcion>\\ y la
captura se apaga sola. Al final dice cuantas funciones se ejecutaron.

Uso: python capturar_todo.py [n] [estado] [--parte i/k] [--puerto P]

El emulador no acepta mas de ~896 puntos de interrupcion por sesion: con --parte se reparten las funciones
entre k emuladores a la vez (cada uno con su --puerto), y asi tambien se usan mas nucleos.
"""
import os
import sys
import time

from emu import RAIZ, Emu
from explorar import CUE, estado, recorrer

args = [a for i, a in enumerate(sys.argv[1:], 1) if not a.startswith("--") and not sys.argv[i - 1].startswith("--")]
n = int(args[0]) if args else 2
est = args[1] if len(args) > 1 else "saltar"
parte, partes = (int(x) for x in sys.argv[sys.argv.index("--parte") + 1].split("/")) if "--parte" in sys.argv else (0, 1)
puerto = int(sys.argv[sys.argv.index("--puerto") + 1]) if "--puerto" in sys.argv else 8091
CAPT = os.path.join(RAIZ, "decomp", "capturas")
funcs = []
for l in open(os.path.join(RAIZ, "decomp", "funciones_juego.tsv")):
    d, tam, nom = l.split()
    funcs.append((int(d, 16), nom))
funcs = funcs[parte::partes]

# recorrido: moverse, saltar, atacar, pausar, y saltar de nivel en nivel
JUGAR = ("UP:40 CROSS w20 UP:30 SQUARE w30 CIRCLE w30 TRIANGLE w30 LEFT:20 UP:40 CROSS w30 RIGHT:20 UP:60 "
         "SQUARE w30 R1 w20 L1 w20 START w40 DOWN w10 START w40 UP:90 CROSS w40")

t0 = time.time()
with Emu(iso=CUE, log=f"capturar_todo_{parte}.log", extra=("-fastboot",), depurar=True, puerto=puerto) as e:
    e.cargar(estado(est))
    e.esperar(2)
    import urllib.error
    fallidas = []
    for d, nom in funcs:
        carpeta = os.path.join(CAPT, nom)
        os.makedirs(carpeta, exist_ok=True)
        if len([f for f in os.listdir(carpeta) if f.endswith(".regs")]) >= n:
            continue                      # ya tiene sus capturas de una ronda anterior
        try:
            e.lua("capturar", a=d, n=n, dir=carpeta)
        except urllib.error.HTTPError as ex:
            fallidas.append((nom, ex.read().decode("utf-8", "replace")[:120]))
    if fallidas:
        print(f"{len(fallidas)} capturas no se pudieron poner, por ejemplo {fallidas[:3]}")
    print(f"{len(funcs)} capturas puestas en {time.time() - t0:.0f} s", flush=True)
    recorrer(e, "todo_hub", JUGAR)
    for nivel in (3, 4, 7, 10, 14):
        e.eval(f"wr8(0x8007CA00, {nivel}); wr16(0x8007C9FC, 0); return 'ok'")
        recorrer(e, f"todo_{nivel}", "w1300 " + JUGAR)
        print(f"nivel {nivel} listo, {time.time() - t0:.0f} s", flush=True)
cubiertas = [nom for _, nom in funcs if any(f.endswith(".regs") for f in os.listdir(os.path.join(CAPT, nom)))]
print(f"{len(cubiertas)} de {len(funcs)} funciones del juego se ejecutaron ({time.time() - t0:.0f} s)")
