"""Mapa de modulos: a que archivo fuente del estudio pertenece cada funcion del ejecutable.

Las llamadas a Afirmar y Reservar llevan el nombre del archivo fuente ("modelLoader.c"). El enlazador
pone el codigo de cada archivo seguido, asi que entre dos funciones del mismo archivo todo es de ese
archivo. Las funciones de la biblioteca de Sony tienen su nombre (Ghidra las reconoce por firma).

Uso: python modulos.py      deja notas\\modulos.tsv (inicio, fin, modulo, funciones) y lo resume
"""
import os
import re

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
C = os.path.join(RAIZ, "notas", "ghidra", "decompilado.c")
FUNCS = os.path.join(RAIZ, "notas", "ghidra", "funciones.tsv")

texto = open(C, encoding="utf-8", errors="replace").read()
bloques = re.split(r"^// ==== ", texto, flags=re.M)[1:]
archivo_de = {}
for b in bloques:
    cab = b.split("\n", 1)[0]
    nombre, _, dir_ = cab.partition(" @ ")
    dir_ = int(dir_.strip(), 16)
    fuentes = re.findall(r'"([A-Za-z_]+\.(?:c|cpp))"', b)
    if fuentes:
        archivo_de[dir_] = max(set(fuentes), key=fuentes.count)

funciones = []
for l in open(FUNCS, encoding="utf-8"):
    d, tam, nom = l.rstrip("\n").split("\t")
    d = int(d, 16)
    if 0x80010000 <= d < 0x80060800:
        funciones.append((d, int(tam), nom))
funciones.sort()

# biblioteca de Sony: nombres reconocidos que no son FUN_ ni nuestros
propios = {l.split("\t")[2] for l in open(os.path.join(RAIZ, "notas", "simbolos.tsv"), encoding="utf-8").read().split("\n")[1:] if l.count("\t") >= 2}


def clase(d, nom):
    if d in archivo_de:
        return archivo_de[d]
    if not nom.startswith("FUN_") and nom not in propios and not nom.startswith(("thunk_", "caseD_", "LAB_")):
        return "psyq"
    return None


etiquetas = [clase(d, n) for d, _, n in funciones]
# rellenar: entre dos funciones del mismo modulo, todo es de ese modulo
# (solo para archivos del juego: las bibliotecas de Sony aparecen intercaladas en varios lugares)
ult = None
for i, e in enumerate(etiquetas):
    if e is not None and e != "psyq":
        if ult is not None and etiquetas[ult] == e:
            for j in range(ult + 1, i):
                if etiquetas[j] is None:
                    etiquetas[j] = e
        ult = i

tramos = []
for (d, tam, nom), e in zip(funciones, etiquetas):
    e = e or "?"
    if tramos and tramos[-1][2] == e:
        tramos[-1][1] = d + tam
        tramos[-1][3] += 1
    else:
        tramos.append([d, d + tam, e, 1])
with open(os.path.join(RAIZ, "notas", "modulos.tsv"), "w", encoding="utf-8") as f:
    f.write("inicio\tfin\tmodulo\tfunciones\n")
    for a, b, e, n in tramos:
        f.write(f"{a:08x}\t{b:08x}\t{e}\t{n}\n")
from collections import Counter
cuenta = Counter()
for e in etiquetas:
    cuenta[e or "?"] += 1
print(f"{len(funciones)} funciones de codigo, {len(tramos)} tramos")
for m, n in cuenta.most_common():
    print(f"  {m:22s} {n}")
