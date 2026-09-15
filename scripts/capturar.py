"""Captura llamadas reales a funciones del juego para verificar su descompilacion.

Carga un estado, pone una captura en cada funcion (control.lua, ruta capturar) y juega unos pasos. Cada
vez que el juego entra a la funcion guarda registros y memoria en decomp\\capturas\\<funcion>\\NN.*

Uso: python capturar.py <estado> "<pasos como en explorar.py>" Funcion[:n] [Funcion[:n] ...]
     python capturar.py saltar "w30" ir:3 RecogibleNoTomado:5 CeldaDePosicion:5
  ir:N en la lista de funciones salta antes al nivel N (ir_a_nivel.py), para capturar lo que pasa al cargar.
Las direcciones salen de decomp\\symbol_addrs.txt.
"""
import os
import re
import sys
import time

from emu import RAIZ, Emu
from explorar import CUE, estado, recorrer

SIMBOLOS = os.path.join(RAIZ, "decomp", "symbol_addrs.txt")
CAPT = os.path.join(RAIZ, "decomp", "capturas")


def direccion(nombre):
    for l in open(SIMBOLOS, encoding="utf-8"):
        m = re.match(r"(\w+) = 0x([0-9A-Fa-f]+);", l)
        if m and m.group(1) == nombre:
            return int(m.group(2), 16)
    if re.fullmatch(r"func_[0-9A-Fa-f]{8}", nombre):
        return int(nombre[5:], 16)
    raise KeyError(nombre)


if __name__ == "__main__":
    est, pasos, pedidas = sys.argv[1], sys.argv[2], sys.argv[3:]
    with Emu(iso=CUE, log="capturar.log", extra=("-fastboot",), depurar=True) as e:
        e.cargar(estado(est))
        e.esperar(2)
        nivel = None
        for p in pedidas:
            nombre, _, n = p.partition(":")
            if nombre == "ir":
                nivel = int(n)
                continue
            carpeta = os.path.join(CAPT, nombre)
            os.makedirs(carpeta, exist_ok=True)
            for f in os.listdir(carpeta):
                os.remove(os.path.join(carpeta, f))
            e.lua("capturar", a=direccion(nombre), n=int(n or 5), dir=carpeta)
        if nivel is not None:
            e.eval(f"wr8(0x8007CA00, {nivel}); wr16(0x8007C9FC, 0); return 'ok'")
        recorrer(e, "capturar", pasos)
    for p in pedidas:
        nombre = p.partition(":")[0]
        if nombre != "ir":
            n = len([f for f in os.listdir(os.path.join(CAPT, nombre)) if f.endswith(".regs")])
            print(f"{nombre}: {n} capturas")
