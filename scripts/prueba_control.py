"""Prueba el control remoto con el ejemplo padtest: pulsa botones y guarda capturas.

Uso: python prueba_control.py
Deja en notas\\logs las capturas padtest_suelto.png y padtest_pulsado.png, y un estado guardado.
"""
import os
import time

from emu import LOGS, RAIZ, Emu

EXE = os.path.join(RAIZ, r"herramientas\nugget\psyqo\examples\padtest\padtest.ps-exe")

with Emu(exe=EXE, log="padtest.log") as e:
    t0, f0 = time.time(), e.frames()
    e.esperar(120)
    print(f"velocidad {(e.frames() - f0) / (time.time() - t0):.1f} frames por segundo")
    e.captura(os.path.join(LOGS, "padtest_suelto.png"))
    e.lua("boton", b="CROSS,UP", f=60)
    e.esperar(20)
    e.captura(os.path.join(LOGS, "padtest_pulsado.png"))
    e.esperar(60)
    print("eval", e.eval("return 6*7"))
    print("ram", len(e.ram()), "vram", len(e.vram()))
    print("guardar", e.guardar(os.path.join(LOGS, "padtest.estado")),
          os.path.getsize(os.path.join(LOGS, "padtest.estado")), "bytes")
    print("cargar", e.cargar(os.path.join(LOGS, "padtest.estado")))
print("cerrado")
