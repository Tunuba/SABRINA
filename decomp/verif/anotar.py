# Pasa a notas/fases/auditoria.tsv lo que dejo un log de vmano.sh / vreal.sh ("== func src" y "func: ... -> ESTADO").
# uso: py verif/anotar.py log [--sint] [--solo f1,f2]   (desde decomp)
# Con --sint los estados quedan IGUAL_SINT / IGUAL_V0_SINT (capturas sinteticas, se cuentan aparte).
# Una funcion que ya estaba IGUAL no se baja a un estado peor.
import csv, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
log = sys.argv[1]
sint = "--sint" in sys.argv
solo = None
if "--solo" in sys.argv:
    solo = set(sys.argv[sys.argv.index("--solo") + 1].split(","))

tam = {}
with open("funciones_juego.tsv", encoding="utf-8") as f:
    for d, t, n in csv.reader(f, delimiter="\t"):
        tam[n] = t

RANGO = {"IGUAL": 3, "IGUAL_V0": 2, "IGUAL_SINT": 1, "IGUAL_V0_SINT": 0}
res = {}
src = None
for linea in open(log, encoding="utf-8", errors="replace"):
    m = re.match(r"== (\S+) (\S+)", linea)
    if m:
        src = m.group(2)
        continue
    m = re.match(r"(\w+): (.*) -> (\w+)\s*$", linea)
    if m and src:
        f, det, e = m.groups()
        if solo and f not in solo:
            continue
        if e == "IGUAL" and det.startswith("la original"):
            continue
        if sint and e in ("IGUAL", "IGUAL_V0"):
            e += "_SINT"
        res[f] = (e, src, det)

p = "../notas/fases/auditoria.tsv"
with open(p, encoding="utf-8", newline="") as f:
    filas = [l.rstrip("\r\n").split("\t") for l in f if l.strip()]
cab, filas = filas[0], filas[1:]
lugar = {r[0]: i for i, r in enumerate(filas)}
for f, (e, src, det) in res.items():
    nueva = [f, tam.get(f, "0"), e, src, det]
    if f in lugar:
        viejo = filas[lugar[f]]
        if RANGO.get(viejo[2], -1) > RANGO.get(e, -1):
            print(f"{f}: queda {viejo[2]} (salio {e})")
            continue
        filas[lugar[f]] = nueva
    else:
        lugar[f] = len(filas)
        filas.append(nueva)
    print(f"{f}\t{e}")
with open(p, "w", encoding="utf-8", newline="") as f:
    for r in [cab] + filas:
        f.write("\t".join(r) + "\n")
