"""Arranca un disco armado desde cero, llega al HUB jugando y prueba el dano con el laboratorio.

Uso: python prueba_final.py <nombre.cue>
Capturas en notas\\capturas\\final_*.png y un estado en estados\\final_hub.estado
"""
import os
import sys

from emu import RAIZ, Emu
from explorar import estado, recorrer

cue = os.path.join(RAIZ, "disco", sys.argv[1])
VIDA = "return rd8(rd32(0x8007CAF8) + 0x118)"

with Emu(iso=cue, log="final.log", extra=("-fastboot",), depurar=True) as e:
    # titulo, nuevo juego, saltar el video, pantalla de carga y HUB
    recorrer(e, "final", "w2160 c CROSS w300 START w60 CROSS w240 c w1300 c")
    e.guardar(estado("final_hub"))
    antes = int(e.eval(VIDA))
    e.lua("suelo", t=4, n=3)
    e.esperar(120)
    despues = int(e.eval(VIDA))
    print(f"vida en el HUB {antes} -> {despues} tras el suelo peligroso")
    print("instruccion en 0x8003431C:", e.eval("return string.format('%08x', rd32(0x8003431C))"))
