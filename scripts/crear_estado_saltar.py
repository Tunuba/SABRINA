"""Crea estados\\saltar.estado (HUB jugando), el estado de partida que usan mod_rosa.py probar,
mod_bruja.py probar, prueba_caida.py, capturar_mas.py, etc. Mismo camino que prueba_final.py:
titulo, nuevo juego, saltar el video de entrada, pantalla de carga y esperar a estar en el HUB.

Uso: python crear_estado_saltar.py
"""
from emu import RAIZ, Emu
from explorar import CUE, estado, recorrer

with Emu(iso=CUE, log="crear_estado_saltar.log", extra=("-fastboot",)) as e:
    recorrer(e, "saltar_estado", "w2160 c CROSS w300 START w60 CROSS w240 c w1300 c")
    e.guardar(estado("saltar"))
    print("guardado", estado("saltar"))
