"""Bucle desatendido: arma con todo el C, prueba que el juego arranque de verdad; si no, bisecta la funcion
que lo rompe, la anota en decomp/armar_c_excluir.txt y vuelve a empezar. Termina cuando arranca (o a las N vueltas).
Uso: python lazo_armado_c.py [vueltas]    Registro en decomp/build/lazo_armado_c.txt"""
import os
import subprocess
import sys
import time

import biseccion_c as b
from emu import RAIZ

VUELTAS = int(sys.argv[1]) if len(sys.argv) > 1 else 10
LOG = os.path.join(RAIZ, "decomp", "build", "lazo_armado_c.txt")
EXCL = os.path.join(RAIZ, "decomp", "armar_c_excluir.txt")


def log(*a):
    t = time.strftime("%H:%M:%S ") + " ".join(str(x) for x in a)
    print(t, flush=True)
    with open(LOG, "a", encoding="utf-8") as f:
        f.write(t + "\n")


def armar_todo():
    r = subprocess.run(["wsl", "-d", "Ubuntu", "--", "bash", "-lc",
                        f"cd '{b.WSLDIR}' && python3 armar_c.py | tail -2 && cp build/armado_c.txt build/armado_c_completo.txt"],
                       capture_output=True, text=True)
    log("armado:", r.stdout.strip().replace("\n", " | "), r.stderr.strip()[-200:])


def culpable(fs, ok_base):
    lo, hi = 0, len(fs)
    while hi - lo > 1:
        mid = (lo + hi) // 2
        ok, m = b.prueba(fs[mid:])
        log(f"  sin las primeras {mid}: {ok} {m}")
        if ok:
            hi = mid
        else:
            lo = mid
    return fs[hi - 1]


for v in range(VUELTAS):
    armar_todo()
    fs = b.lista()
    ok, m = b.prueba(fs)
    log(f"vuelta {v}: {len(fs)} funciones en C ->", ok, m)
    if ok:
        log("ARRANCA con", len(fs), "funciones en C")
        break
    f = culpable(fs, ok)
    log("  rompe el arranque:", f)
    with open(EXCL, "a", encoding="utf-8") as fh:
        fh.write(f"{f}\tbisecta automatica {time.strftime('%d-%m')}: con C el juego no arranca ({m}); por investigar\n")
