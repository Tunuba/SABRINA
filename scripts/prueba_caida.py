"""Camina en una direccion desde el estado 'saltar' y registra vida, estado y posicion de Sabrina.

Uso: python prueba_caida.py BOTON segundos [--invencible]
Objeto de Sabrina: puntero en 0x8007CAF8. Vida +0x118 (byte), estado +0x70 (2 = muerta),
posicion +0x24 +0x28 +0x2C. Invencible: palabra en 0x8007CB74.
"""
import os
import sys

from emu import RAIZ, Emu
from hoja import hoja

CUE = os.path.join(RAIZ, r"disco\Sabrina the Teenage Witch - A Twitch in Time! (USA).cue")
CAP = os.path.join(RAIZ, r"notas\capturas")
boton, segundos = sys.argv[1], int(sys.argv[2])
inv = "--invencible" in sys.argv
nombre = f"caida_{boton}_{'inv' if inv else 'normal'}"

with Emu(iso=CUE, log=nombre + ".log", extra=("-fastboot",)) as e:
    e.cargar(os.path.join(RAIZ, r"estados\saltar.estado"))
    e.esperar(5)
    if inv:
        e.eval("wr32(0x8007CB74, 1); return 'ok'")
    caps = []
    for t in range(segundos * 2):
        e.lua("boton", b=boton, f=30)
        e.esperar(30)
        r = e.eval("local p = rd32(0x8007CAF8); return string.format('vida %d estado %d pos %d %d %d', "
                   "rd8(p + 0x118), rd16(p + 0x70), rd32(p + 0x24), rd32(p + 0x28), rd32(p + 0x2c))")
        print(f"{t / 2:4.1f} s  {r}", flush=True)
        if t % 2 == 1:
            c = os.path.join(CAP, f"{nombre}_{t // 2:02d}.png")
            e.captura(c)
            caps.append(c)
    hoja(os.path.join(CAP, nombre + "_hoja.png"), 4, caps)
