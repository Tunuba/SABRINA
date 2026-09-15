"""Comprueba si un archivo .TEX es una copia directa de una zona de la VRAM del juego.

Uso: python tex_vs_vram.py <estado> <archivo.TEX>
Carga el estado, saca la VRAM y busca cada fila del TEX (probando anchos de 256, 512 y 1024 pixeles)
dentro de las filas de la VRAM. Si casi todas las filas aparecen en el mismo sitio y en orden,
el TEX se sube tal cual a ese rectangulo.
"""
import os
import sys
from collections import Counter

from emu import RAIZ, Emu
from vram_png import vram_a_imagen

CUE = os.path.join(RAIZ, r"disco\Sabrina the Teenage Witch - A Twitch in Time! (USA).cue")

estado, tex_ruta = sys.argv[1], sys.argv[2]
tex = open(tex_ruta, "rb").read()
with Emu(iso=CUE, log="tex_vs_vram.log", extra=("-fastboot",)) as e:
    e.cargar(os.path.join(RAIZ, "estados", estado + ".estado"))
    e.esperar(10)
    vram = e.vram()
salida = os.path.join(RAIZ, "notas", f"vram_{estado}.png")
vram_a_imagen(vram).save(salida)
print("vram en", salida)

filas_vram = [vram[y * 2048:(y + 1) * 2048] for y in range(512)]
for ancho in (256, 512, 1024):
    bpf = ancho * 2
    n = len(tex) // bpf
    sitios = Counter()
    probadas = 0
    for r in range(0, n, max(1, n // 64)):
        fila = tex[r * bpf:(r + 1) * bpf]
        if fila.count(0) > bpf * 0.9:
            continue        # filas casi vacias no dicen nada
        probadas += 1
        for y in range(512):
            x = filas_vram[y].find(fila)
            if x >= 0 and x % 2 == 0:
                sitios[(x // 2, y - r)] += 1
                break
    mejor = sitios.most_common(3)
    print(f"ancho {ancho:4d} ({n} filas): {probadas} filas probadas, coincidencias por origen {mejor}")
