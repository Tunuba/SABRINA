"""Cuanto del codigo de cada funcion tocan sus capturas y las variantes.

Corre la original desde cada captura (y con las mismas variantes de argumentos y de memoria que usa
verificar.py) anotando que instrucciones se ejecutan. Una funcion verificada donde las capturas solo
recorren la mitad de sus instrucciones es un IGUAL flojo: la otra mitad nadie la probo.

Deja decomp/cobertura.tsv: funcion, instrucciones, tocadas, por ciento.
Uso: python3 cobertura.py [--solo A,B] [--variantes 30]
"""
import glob
import os
import random
import sys

import verificar
from unicorn import UC_HOOK_CODE


def cobertura_de(f, n_variantes=30):
    sim = verificar.simbolos()
    ini, fin = sim[f], verificar.fin_de(f)
    total = (fin - ini) // 4
    tocadas = set()
    orig = verificar.Uc.emu_start

    def emu_start(self, *a, **k):
        self.hook_add(UC_HOOK_CODE, lambda u, d, t, _: tocadas.add(d), begin=ini, end=fin - 1)
        return orig(self, *a, **k)

    verificar.Uc.emu_start = emu_start
    try:
        caps = sorted(glob.glob(os.path.join(verificar.AQUI, "capturas", f, "*.regs")))
        rnd = random.Random(1234)
        pool = verificar.constantes_de(f)
        for cap in caps:
            base = cap[:-5]
            verificar.ejecutar(base, ini, None)
            regs = [int(x, 16) for x in open(base + ".regs").read().split()]
            for r in verificar.variantes(regs, pool, n_variantes, rnd):
                verificar.ejecutar(base, ini, None, r)
    finally:
        verificar.Uc.emu_start = orig
    return total, len(tocadas)


def main():
    solo = sys.argv[sys.argv.index("--solo") + 1].split(",") if "--solo" in sys.argv else None
    n = int(sys.argv[sys.argv.index("--variantes") + 1]) if "--variantes" in sys.argv else 30
    funcs = []
    for l in open(os.path.join(verificar.AQUI, "progreso.tsv")):
        p = l.rstrip("\n").split("\t")
        if len(p) > 2 and p[2] in ("IGUAL", "IGUAL_V0", "YA_HECHA") and (not solo or p[0] in solo):
            funcs.append(p[0])
    filas = []
    for f in funcs:
        try:
            total, tocadas = cobertura_de(f, n)
        except Exception as ex:
            print(f"{f}: {ex}")
            continue
        filas.append((f, total, tocadas, 100 * tocadas // max(total, 1)))
        print(f"{f}: {tocadas} de {total} instrucciones ({100 * tocadas // max(total, 1)} %)", flush=True)
    with open(os.path.join(verificar.AQUI, "cobertura.tsv"), "w") as g:
        g.write("funcion\tinstrucciones\ttocadas\tporciento\n")
        for fila in filas:
            g.write("\t".join(str(x) for x in fila) + "\n")
    completas = sum(1 for x in filas if x[3] >= 100)
    print(f"{completas} de {len(filas)} funciones se recorren enteras")


if __name__ == "__main__":
    main()
