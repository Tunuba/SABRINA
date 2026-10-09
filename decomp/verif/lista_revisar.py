# 05-10: las funciones contadas (reales y sinteticas) que hay que repetir con el verificador nuevo (argumentos de la
# BIOS, GTE, cop0): las que en la original llaman directo a una envoltura de la BIOS, o tienen cop2 o mtc0.
# uso: py verif/lista_revisar.py > build/revisar.txt   (desde decomp; lineas "real|sint<TAB>src:func")
import csv, os, re, subprocess
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))


def leer(p):
    with open(p, encoding="utf-8") as f:
        return list(csv.DictReader(f, delimiter="\t"))


REAL = {"IGUAL", "IGUAL_V0"}
SINT = {"IGUAL_SINT", "IGUAL_V0_SINT"}
fuente, tipo = {}, {}
for r in leer("progreso_sint.tsv"):
    if r["estado"] in SINT:
        fuente[r["funcion"]], tipo[r["funcion"]] = f"src/auto/{r['funcion']}.c", "sint"
for r in leer("progreso.tsv"):
    if r["estado"] in REAL:
        fuente[r["funcion"]], tipo[r["funcion"]] = f"src/auto/{r['funcion']}.c", "real"
for r in leer("../notas/fases/auditoria.tsv"):
    if r["estado"] in REAL or r["estado"] in SINT:
        fuente[r["funcion"]] = r["archivo"]
        tipo[r["funcion"]] = "real" if r["estado"] in REAL else "sint"

dis = subprocess.run(["wsl.exe", "-d", "Ubuntu-24.04", "--", "mipsel-linux-gnu-objdump", "-d",
                      "/mnt/c/Proyectos/SABRINA/decomp/build/slus_012.08.elf"],
                     capture_output=True, text=True).stdout
# envolturas de la BIOS: "li t2,0xa0/0xb0/0xc0; jr t2"
cuerpos, actual = {}, None
for l in dis.splitlines():
    m = re.match(r"^[0-9a-f]+ <(\w+)>:", l)
    if m:
        actual = m.group(1)
        cuerpos[actual] = []
    elif actual and "\t" in l:
        p = l.split("\t")
        if len(p) >= 3:
            cuerpos[actual].append((p[2].strip(), p[3].strip() if len(p) > 3 else ""))
envolturas = {f for f, c in cuerpos.items()
              if len(c) <= 4 and any(mn in ("li", "addiu") and re.search(r"t2,(zero,)?(0xa0|0xb0|0xc0|160|176|192)$", ops)
                                     for mn, ops in c)}
for f in sorted(fuente):
    c = cuerpos.get(f, [])
    if (any(mn == "jal" and ops.split(" <")[-1].rstrip(">") in envolturas for mn, ops in c)
            or any(mn in ("mtc0", "mtc2", "mfc2", "ctc2", "cfc2", "lwc2", "swc2", "c2") for mn, _ in c)):
        print(f"{tipo[f]}\t{fuente[f]}:{f}")
