"""Capturas para las funciones que no tienen: parte de un estado (o del arranque del disco), pone una
captura en cada una de la lista y juega un recorrido. Un solo emulador, sin ventana.

Uso: py capt_sin.py <estado|arranque> <lista.txt> <recorrido> [n]
"""
import os
import sys
import time
import urllib.error

sys.path.insert(0, r"C:\Proyectos\SABRINA\scripts")
from emu import RAIZ, Emu
from explorar import CUE, estado, recorrer

inicio, lista, pasos = sys.argv[1], sys.argv[2], sys.argv[3]
n = int(sys.argv[4]) if len(sys.argv) > 4 else 2
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
with Emu(iso=CUE, log="capt_sin.log", extra=("-fastboot",), depurar=True) as e:
    if inicio != "arranque":
        e.cargar(estado(inicio))
        e.esperar(2)
    malas = 0
    for d, nom in funcs:
        if antes[nom] >= n:
            continue
        os.makedirs(os.path.join(CAPT, nom), exist_ok=True)
        try:
            e.lua("capturar", a=d, n=n - antes[nom], dir=os.path.join(CAPT, nom), inicio=antes[nom], geo=1)
        except urllib.error.HTTPError:
            malas += 1
    print(f"{len(funcs) - malas} puestas, {malas} fallidas, {time.time() - t0:.0f} s", flush=True)
    recorrer(e, "sin_" + inicio, pasos)
nuevas = [nom for _, nom in funcs if antes[nom] == 0 and cuantas(nom) > 0]
print(f"{len(nuevas)} funciones capturadas por primera vez ({time.time() - t0:.0f} s): {' '.join(nuevas)}")
