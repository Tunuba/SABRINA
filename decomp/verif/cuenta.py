# Cuenta combinada: reales (auditoria + progreso IGUAL/IGUAL_V0) y sinteticas aparte.
# uso: py verif/cuenta.py [--pendientes]  (desde decomp)
import csv, sys, os
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
def leer(p, cab=True):
    with open(p, encoding="utf-8") as f:
        if not cab:
            return list(csv.DictReader(f, delimiter="\t", fieldnames=["dir", "tam", "nombre"]))
        return list(csv.DictReader(f, delimiter="\t"))
fj = leer("funciones_juego.tsv", False)
k = list(fj[0].keys())  # direccion, tamano, nombre
tam = {}
for r in fj:
    n = r[k[2]]
    # D_800609B0 es una tabla de datos (constructores y punteros del arranque), no codigo (04-10)
    if n.startswith(("caseD_", "switchD_", "LAB_", "D_")): continue
    tam[n] = int(r[k[1]])
REAL = {"IGUAL", "IGUAL_V0"}; SINT = {"IGUAL_SINT", "IGUAL_V0_SINT"}
real, sint, estado = set(), set(), {}
gpu = set()   # verificadas con el GPU modelado como desocupado (SABRINA_GPU_LISTA=1): aparte, sin aprobar
for r in leer("../notas/fases/auditoria.tsv"):
    e = r["estado"]; estado.setdefault(r["funcion"], "a:" + e)
    if e in REAL: real.add(r["funcion"])
    elif e in SINT: sint.add(r["funcion"])
    elif e.startswith("IGUAL") and e.endswith("_GPU"): gpu.add(r["funcion"])
for r in leer("progreso.tsv"):
    e = r["estado"]
    if r["funcion"] not in estado or e in REAL: estado[r["funcion"]] = "p:" + e
    if e in REAL: real.add(r["funcion"])
for r in leer("progreso_sint.tsv"):
    if r["estado"] in SINT: sint.add(r["funcion"])
    elif r["funcion"] not in estado: estado[r["funcion"]] = "s:" + r["estado"]
real &= set(tam); sint = (sint & set(tam)) - real; gpu = (gpu & set(tam)) - real - sint
tot = sum(tam.values())
br = sum(tam[f] for f in real); bs = sum(tam[f] for f in sint)
print(f"funciones {len(tam)}  bytes {tot}")
print(f"reales      {len(real)} fn  {br} bytes  {100*br/tot:.1f} %")
print(f"sinteticas  {len(sint)} fn  {bs} bytes  {100*bs/tot:.1f} %")
print(f"total       {len(real)+len(sint)} fn  {100*(br+bs)/tot:.1f} %")
if gpu:
    bg = sum(tam[f] for f in gpu)
    print(f"aparte, con el GPU modelado (sin aprobar): {len(gpu)} fn  {bg} bytes  {100*bg/tot:.1f} %")
if "--pendientes" in sys.argv:
    for f in sorted(set(tam) - real - sint - gpu, key=lambda f: -tam[f]):
        print(f"{f}\t{tam[f]}\t{estado.get(f, '-')}")
