"""Arranca Sabrina en el emulador sin ventana y captura la pantalla cada tantos segundos.

Uso: python arrancar_sabrina.py [segundos_totales] [--start]
  --start  pulsa START cada 5 segundos, para saltar el video de entrada y los menus
Las capturas quedan en notas\\capturas\\arranque_XXs.png
"""
import os
import sys

from emu import RAIZ, Emu

CUE = os.path.join(RAIZ, r"disco\Sabrina the Teenage Witch - A Twitch in Time! (USA).cue")
SAL = os.path.join(RAIZ, r"notas\capturas")
os.makedirs(SAL, exist_ok=True)

total = int(sys.argv[1]) if len(sys.argv) > 1 and sys.argv[1].isdigit() else 40
start = "--start" in sys.argv

with Emu(iso=CUE, log="sabrina.log", extra=("-fastboot",)) as e:
    for s in range(5, total + 1, 5):
        e.esperar(s * 60 - e.frames())
        e.captura(os.path.join(SAL, f"arranque_{s:02d}s.png"))
        pc = e.eval("return string.format('%08x', PCSX.getRegisters().pc)")
        print(f"{s:3d} s  pc {pc}", flush=True)
        if start:
            e.pulsar("START")
