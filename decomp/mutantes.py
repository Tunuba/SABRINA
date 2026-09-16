"""Prueba con mutantes: ¿el verificador se daria cuenta si el C de una funcion estuviera mal?

Hace copias del C con un cambio chico en el cuerpo de la funcion (un numero mas uno, una comparacion al
reves, && por ||, una suma por una resta, una linea borrada) y verifica cada copia. Un mutante que pasa
como IGUAL es una parte de la funcion que las capturas no prueban: o hace falta otra captura, o el cambio
no altera nada (mutante equivalente, pasa a veces con las lineas borradas que no hacen nada).

Uso: python3 mutantes.py src/X.c Funcion [--max 16]
"""
import contextlib
import io
import os
import random
import re
import sys
import tempfile

import verificar

AQUI = os.path.dirname(os.path.abspath(__file__))


def cuerpo(texto, funcion):
    """(inicio, fin) del cuerpo de la funcion entre sus llaves."""
    m = re.search(r"^(?!extern\b)\w[\w\s\*]*?\b" + funcion + r"\s*\([^;{]*\)\s*\{", texto, re.M)
    if not m:
        raise SystemExit(f"no encuentro {funcion}")
    i, prof = m.end(), 1
    while prof:
        prof += {"{": 1, "}": -1}.get(texto[i], 0)
        i += 1
    return m.end(), i - 1


def mutantes(texto, funcion):
    ini, fin = cuerpo(texto, funcion)
    c = texto[ini:fin]
    res = []

    def cambio(a, b, nuevo, que):
        res.append((texto[:ini] + c[:a] + nuevo + c[b:] + texto[fin:], que))

    for m in re.finditer(r"(?<![\w.])(0x[0-9A-Fa-f]+|\d+)(?![\w.])", c):
        v = int(m.group(1), 0)
        cambio(m.start(), m.end(), str(v + 1), f"{m.group(1)} por {v + 1}")
    for m in re.finditer(r"<=|>=|==|!=|(?<![<>-])<(?![<=])|(?<![<>-])>(?![>=])", c):
        otro = {"<=": "<", ">=": ">", "==": "!=", "!=": "==", "<": "<=", ">": ">="}[m.group(0)]
        cambio(m.start(), m.end(), otro, f"{m.group(0)} por {otro}")
    for m in re.finditer(r"&&|\|\|", c):
        otro = "||" if m.group(0) == "&&" else "&&"
        cambio(m.start(), m.end(), otro, f"{m.group(0)} por {otro}")
    for m in re.finditer(r"(?<=\w|\))\s*([+-])\s*(?=[\w(])", c):
        otro = "-" if m.group(1) == "+" else "+"
        cambio(m.start(1), m.end(1), otro, f"{m.group(1)} por {otro}")
    lineas = c.split("\n")
    pos = 0
    for l in lineas:
        s = l.strip()
        if s.endswith(";") and not re.match(r"^(return\b|\w[\w\s\*]*\s\**\w+(\[\w*\])?\s*(=.*)?;$)", s):
            cambio(pos, pos + len(l), "", f"sin la linea `{s}`")
        pos += len(l) + 1
    return res


def main():
    c, funcion = sys.argv[1], sys.argv[2]
    maximo = int(sys.argv[sys.argv.index("--max") + 1]) if "--max" in sys.argv else 16
    texto = open(c).read()
    todos = mutantes(texto, funcion)
    random.Random(7).shuffle(todos)
    todos = todos[:maximo]
    vivos = []
    for texto_m, que in todos:
        tmp = os.path.join(tempfile.mkdtemp(), os.path.basename(c))
        open(tmp, "w").write(texto_m)
        salida = io.StringIO()
        try:
            with contextlib.redirect_stdout(salida):
                verificar.verificar(tmp, [funcion], n_variantes=60)
            estado = salida.getvalue().strip().split("\n")[-1].rsplit("-> ", 1)[-1]
        except SystemExit:
            estado = "NO_COMPILA"
        if estado in ("IGUAL", "IGUAL_V0"):
            vivos.append(que)
        print(f"  {'VIVO ' if estado in ('IGUAL', 'IGUAL_V0') else 'muerto'} {que} ({estado})", flush=True)
    print(f"{funcion}: {len(todos) - len(vivos)} de {len(todos)} mutantes muertos")
    return vivos, len(todos)


if __name__ == "__main__":
    main()
