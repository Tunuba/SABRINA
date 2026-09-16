"""Corre la prueba de mutantes sobre todas las funciones escritas a mano (src/, sin src/auto).

Para cada una dice cuantos mutantes mueren. Los que sobreviven son partes que las capturas no prueban.
Deja decomp/mutantes.tsv: funcion, archivo, muertos, total, sobrevivientes.

Uso: python3 mutantes_todos.py [--max 12] [--solo Funcion,...]
"""
import glob
import os
import re
import sys

import mutantes

AQUI = os.path.dirname(os.path.abspath(__file__))


def main():
    maximo = int(sys.argv[sys.argv.index("--max") + 1]) if "--max" in sys.argv else 12
    solo = set(sys.argv[sys.argv.index("--solo") + 1].split(",")) if "--solo" in sys.argv else None
    filas = []
    for c in sorted(glob.glob(os.path.join(AQUI, "src", "*", "*.c"))):
        if os.sep + "auto" + os.sep in c:
            continue
        texto = open(c).read()
        for f in re.findall(r"^(?!extern\b)\w[\w\s\*]*?\b(\w+)\([^;]*$", texto, re.M):
            if solo and f not in solo:
                continue
            sys.argv = [sys.argv[0], c, f, "--max", str(maximo)]
            print(f"== {f} ({os.path.relpath(c, AQUI)})", flush=True)
            try:
                vivos, total = mutantes.main()
            except SystemExit as ex:
                print(f"  {f}: {ex}")
                continue
            filas.append((f, os.path.relpath(c, AQUI), total - len(vivos), total, "; ".join(vivos)))
    with open(os.path.join(AQUI, "mutantes.tsv"), "w") as g:
        g.write("funcion\tarchivo\tmuertos\ttotal\tsobrevivientes\n")
        for fila in filas:
            g.write("\t".join(str(x) for x in fila) + "\n")
    print(f"{sum(1 for f in filas if f[2] == f[3])} de {len(filas)} funciones matan todos sus mutantes")


if __name__ == "__main__":
    main()
