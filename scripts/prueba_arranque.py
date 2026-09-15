"""Arranca el disco de prueba y captura la pantalla a varios tiempos, con y sin -fastboot.

Uso: python prueba_arranque.py [ruta.cue]
"""
import os
import sys

from emu import RAIZ, Emu

CUE = sys.argv[1] if len(sys.argv) > 1 else os.path.join(RAIZ, r"prueba_disco\prueba.cue")
SAL = os.path.join(RAIZ, r"notas\logs")

for nombre, extra in (("normal", ()), ("fastboot", ("-fastboot",))):
    with Emu(iso=CUE, log=f"arranque_{nombre}.log", extra=extra) as e:
        for s in (3, 8, 15):
            e.esperar(s * 60 - e.frames())
            ruta = os.path.join(SAL, f"arranque_{nombre}_{s:02d}s.png")
            e.captura(ruta)
            pc = e.eval("return string.format('%08x', PCSX.getRegisters().pc)")
            print(nombre, s, "s  pc", pc)
