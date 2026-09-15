"""Mide rasgos del compilador en cada tramo del mapa de modulos (notas\\modulos.tsv).

Cuenta instrucciones que GCC no genera (add, addi, sub: suman o restan con trampa de desbordamiento),
divisiones con y sin la comprobacion de division por cero que agrega el ensamblador de Sony (break 7),
y usos de $fp. Si el codigo del juego tiene esos rasgos y las bibliotecas de Sony no, el juego se compilo
con otro compilador.

Uso: python3 estilo_compilador.py
"""
import re
from collections import defaultdict

tramos = []
for l in open("../notas/modulos.tsv").read().split("\n")[1:]:
    if l:
        a, b, m, n = l.split("\t")
        tramos.append((int(a, 16), int(b, 16), "psyq" if m == "psyq" else "juego"))


def grupo(d):
    for a, b, m in tramos:
        if a <= d < b:
            return m
    return "?"


cuenta = defaultdict(lambda: defaultdict(int))
pat = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\S+)\s*(.*)")
for linea in open("asm/800.s", encoding="utf-8", errors="replace"):
    m = pat.search(linea)
    if not m:
        continue
    d, op, args = int(m.group(1), 16), m.group(2), m.group(3)
    g = grupo(d)
    c = cuenta[g]
    c["instrucciones"] += 1
    if op in ("add", "addi", "sub"):
        c["add/addi/sub"] += 1
    if op in ("addu", "addiu", "subu"):
        c["addu/addiu/subu"] += 1
    if op in ("div", "divu"):
        c["div"] += 1
    if op == "break":
        c["break"] += 1
    if "$fp" in args:
        c["usos de $fp"] += 1
for g, c in cuenta.items():
    print(g, dict(c))
