"""Mide cuantos cuadros de juego dibuja de verdad un disco en el HUB: arranca de cero, llega jugando al HUB y
cuenta las vueltas del bucle de juego de BuclePrincipal (func_80019D80 y func_80021B4C, una vez por vuelta) durante N cuadros del emulador
(60 por segundo). 60 de 60 es fluido; si el juego se atrasa, dibuja menos y se siente trabado.

Uso: python medir_fps.py [disco.cue ...]     (sin argumentos: el original y disco\\sabrina_fantasma.cue)
"""
import os
import sys

from emu import RAIZ, Emu
from explorar import CUE, recorrer

# el bucle de juego de BuclePrincipal (.L80010460) llama a estas dos una vez por vuelta: una vuelta = un cuadro
CUADROS = {"func_80019D80": 0x80019D80, "func_80021B4C": 0x80021B4C}
N = 600

discos = sys.argv[1:] or [CUE, os.path.join(RAIZ, "disco", "sabrina_fantasma.cue")]
for i, cue in enumerate(discos):
    with Emu(iso=cue, log=f"medir_fps_{i}.log", extra=("-fastboot",), depurar=True, puerto=8099) as e:
        recorrer(e, f"fps_{i}_arranque", "w2160 CROSS w300 START w60 CROSS w240 w1300")
        for a in CUADROS.values():
            e.lua("contar", a=a)
        recorrer(e, f"fps_{i}", f"UP:120 LEFT:120 w{N - 240} c")
        for nom, a in CUADROS.items():
            n = int(e.lua("cuenta", a=a))
            print(f"{os.path.basename(cue)[:30]}  {nom}: {n} en {N} cuadros ({60 * n / N:.1f} por segundo)", flush=True)
