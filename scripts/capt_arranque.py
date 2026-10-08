"""Capturas de lo que corre al arrancar (08-10): el emulador arranca en pausa (sin -run), se ponen las capturas
de la lista y recien despues se suelta. Con capt_sin.py las capturas se ponian con el juego ya corriendo y lo que
solo corre al inicio (main, setjmp, el malloc de la BIOS al armar el monton) ya habia pasado. Un emulador, sin ventana.

Uso: py capt_arranque.py <lista.txt> <recorrido> [n]
"""
import os
import sys
import time
import urllib.error

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from emu import RAIZ, Emu
from explorar import CUE, recorrer

lista, pasos = sys.argv[1], sys.argv[2]
n = int(sys.argv[3]) if len(sys.argv) > 3 else 2
CAPT = os.path.join(RAIZ, "decomp", "capturas")
solo = set(open(lista).read().split())
funcs = []
for l in open(os.path.join(RAIZ, "decomp", "funciones_juego.tsv")):
    d, tam, nom = l.split()
    if nom in solo:
        funcs.append((int(d, 16), nom))


def cuantas(nom):
    c = os.path.join(CAPT, nom)
    return len([f for f in os.listdir(c) if f.endswith(".regs")]) if os.path.isdir(c) else 0


t0 = time.time()
antes = {nom: cuantas(nom) for _, nom in funcs}
with Emu(iso=CUE, log="capt_arranque.log", extra=("-fastboot",), depurar=True, pausado=True) as e:
    malas = 0
    for d, nom in funcs:
        if antes[nom] >= n:
            continue
        os.makedirs(os.path.join(CAPT, nom), exist_ok=True)
        try:
            e.lua("capturar", a=d, n=n - antes[nom], dir=os.path.join(CAPT, nom), inicio=antes[nom], geo=1)
        except urllib.error.HTTPError:
            malas += 1
    print(f"{len(funcs) - malas} puestas, {malas} fallidas, frame {e.frames()}", flush=True)
    e.eval("PCSX.resumeEmulator(); return 'ok'")
    recorrer(e, "arranque", pasos)
nuevas = [nom for _, nom in funcs if antes[nom] == 0 and cuantas(nom) > 0]
print(f"{len(nuevas)} funciones capturadas por primera vez ({time.time() - t0:.0f} s): {' '.join(nuevas)}")
