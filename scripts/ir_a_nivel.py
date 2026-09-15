"""Salta a cualquier nivel desde el juego en marcha, usando el ciclo principal (FUN_80010030).

El ciclo principal carga el nivel del byte 0x8007CA00 y juega mientras el halfword 0x8007C9FC no sea 0.
Si se escribe el nivel y se pone ese halfword en 0, el juego sale del nivel y carga el pedido.
Niveles: 0 menu, 1-3 Stone, 4-6 Egypt, 7-9 Japan, 10-12 West, 13 HUB, 14 Chaos.

Uso: python ir_a_nivel.py <estado_inicial> <nivel> [segundos] [--guardar nombre] [--cue disco.cue]
"""
import os
import sys

from emu import RAIZ, Emu
from explorar import CUE, estado
from hoja import hoja

NIVEL, JUGANDO = 0x8007CA00, 0x8007C9FC
NOMBRES = ["menu", "S1", "S2", "S3", "E1", "E2", "E3", "J1", "J2", "J3", "W1", "W2", "W3", "H1", "C1"]


def ir(e, nivel):
    e.eval(f"wr8({NIVEL}, {nivel}); wr16({JUGANDO}, 0); return 'ok'")


if __name__ == "__main__":
    ini, nivel = sys.argv[1], int(sys.argv[2])
    seg = int(sys.argv[3]) if len(sys.argv) > 3 and sys.argv[3].isdigit() else 30
    final = sys.argv[sys.argv.index("--guardar") + 1] if "--guardar" in sys.argv else None
    cue = os.path.join(RAIZ, "disco", sys.argv[sys.argv.index("--cue") + 1]) if "--cue" in sys.argv else CUE
    nombre = f"nivel_{NOMBRES[nivel]}"
    caps = []
    with Emu(iso=cue, log=nombre + ".log", extra=("-fastboot",)) as e:
        e.cargar(estado(ini))
        e.esperar(5)
        ir(e, nivel)
        for s in range(3, seg + 1, 3):
            e.esperar(180)
            r = os.path.join(RAIZ, r"notas\capturas", f"{nombre}_{s:02d}s.png")
            e.captura(r)
            caps.append(r)
            print(f"{s:3d} s  nivel {e.eval(f'return rd8({NIVEL})')} jugando {e.eval(f'return rd16({JUGANDO})')}",
                  flush=True)
        if final:
            e.guardar(estado(final))
    hoja(os.path.join(RAIZ, r"notas\capturas", nombre + "_hoja.png"), 5, caps)
