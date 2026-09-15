"""Cuenta cuantas veces pasa el juego por unas direcciones de codigo mientras se juega una secuencia.

Uso: python contar_paso.py <estado> "<pasos como en explorar.py>" 0xDIR1 0xDIR2 ...
Ejemplo: python contar_paso.py saltar "UP:60 CROSS w60" 0x8003401c 0x80031300
"""
import os
import sys

from emu import RAIZ, Emu
from explorar import CUE, estado, recorrer

est, pasos, dirs = sys.argv[1], sys.argv[2], sys.argv[3:]
with Emu(iso=CUE, log="contar.log", extra=("-fastboot",), depurar=True) as e:
    e.cargar(estado(est))
    e.esperar(2)
    for d in dirs:
        e.lua("contar", a=int(d, 16))
    recorrer(e, "contar", pasos)
    for d in dirs:
        print(f"{d}: {e.lua('cuenta', a=int(d, 16))} veces")
