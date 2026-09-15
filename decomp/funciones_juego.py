"""Lista de funciones del juego (sin las de la biblioteca de Sony), con su tamano, desde el ELF armado.

Uso: python3 funciones_juego.py      deja funciones_juego.tsv (direccion, tamano, nombre)
"""
import os
import subprocess

AQUI = os.path.dirname(os.path.abspath(__file__))
psyq = []
for l in open(os.path.join(AQUI, "..", "notas", "modulos.tsv")).read().split("\n")[1:]:
    if l and l.split("\t")[2] == "psyq":
        a, b = l.split("\t")[:2]
        psyq.append((int(a, 16), int(b, 16)))

sal = subprocess.run(["mipsel-linux-gnu-nm", "-n", "-S", os.path.join(AQUI, "build/slus_012.08.elf")],
                     capture_output=True, text=True).stdout
funcs = []
vistas = set()
for l in sal.splitlines():
    p = l.split()
    if len(p) == 4 and p[2] in "Tt" and "." not in p[3]:        # splat agrega alias .NON_MATCHING
        d, tam, nom = int(p[0], 16), int(p[1], 16), p[3]
        if d in vistas:
            continue
        if 0x80010000 <= d < 0x80060A80 and not any(a <= d < b for a, b in psyq):
            vistas.add(d)
            funcs.append((d, tam, nom))
with open(os.path.join(AQUI, "funciones_juego.tsv"), "w") as f:
    for d, tam, nom in funcs:
        f.write(f"{d:08x}\t{tam}\t{nom}\n")
print(len(funcs), "funciones del juego,", sum(t for _, t, _ in funcs) // 4, "instrucciones")
