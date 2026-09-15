"""Cambia en vivo una por una las paletas indicadas (rojo por azul) y captura, para ver que pinta cada una.

Uso: python probar_paletas.py <estado> x,y[,bpp] x,y ...     (bpp 4 u 8, por defecto 4)
Ejemplo: python probar_paletas.py saltar 832,472 896,472 512,473,8
Hoja en notas\\capturas\\probar_paletas_hoja.png (la primera captura es la original).
"""
import os
import struct
import sys

from emu import RAIZ, Emu
from explorar import CUE, estado
from hoja import hoja

CAP = os.path.join(RAIZ, r"notas\capturas")


def rojo_por_azul(v):
    return (v & 0x83E0) | ((v & 31) << 10) | ((v >> 10) & 31)


with Emu(iso=CUE, log="probar_paletas.log", extra=("-fastboot",)) as e:
    e.cargar(estado(sys.argv[1]))
    e.esperar(4)
    e.eval("PCSX.pauseEmulator(); return 'ok'")
    vram = e.vram()
    e.eval("PCSX.resumeEmulator(); return 'ok'")
    e.esperar(2)
    rutas = [e.captura(os.path.join(CAP, "probar_paletas_original.png"))]
    for arg in sys.argv[2:]:
        partes = [int(p) for p in arg.split(",")]
        x, y = partes[0], partes[1]
        n = 256 if len(partes) > 2 and partes[2] == 8 else 16
        pal = struct.unpack_from(f"<{n}H", vram, (y * 1024 + x) * 2)
        e.escribir_vram(x, y, n, 1, struct.pack(f"<{n}H", *[rojo_por_azul(v) if v else 0 for v in pal]))
        e.esperar(2)
        rutas.append(e.captura(os.path.join(CAP, f"probar_paletas_{x}_{y}.png")))
        e.escribir_vram(x, y, n, 1, struct.pack(f"<{n}H", *pal))
        e.esperar(2)
    hoja(os.path.join(CAP, "probar_paletas_hoja.png"), 4, rutas)
print("listo")
