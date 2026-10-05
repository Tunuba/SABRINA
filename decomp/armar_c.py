"""Armado movible: mete el C ya verificado dentro del ejecutable del juego.

El ejecutable no puede crecer (el disco se parcha sector a sector, ver scripts/disco.py), asi que el C
compilado se coloca en los huecos que dejan las propias funciones originales y en la entrada de cada una
queda un `j c__Nombre; nop`. Como el nombre original sigue siendo la direccion de la entrada, un puntero a
funcion o una llamada del resto del juego llegan al C igual que en la verificacion (verificar.py enlaza
con los mismos nombres: Nombre = direccion original, c__Nombre = el C).

Uso (en WSL, carpeta decomp):
  python3 armar_c.py [--solo A,B,C] [--sint] [--salida build/SLUS_C.exe] [--O Os]
    --solo   solo esas funciones (si no, todas las IGUAL / IGUAL_V0 de la auditoria y del lote)
    --sint   tambien las IGUAL_SINT / IGUAL_V0_SINT
Escribe la salida y build/armado_c.txt con lo que paso con cada funcion.
"""
import argparse
import csv
import os
import re
import struct
import subprocess
import sys
import tempfile

AQUI = os.path.dirname(os.path.abspath(__file__))
os.chdir(AQUI)
CC = ["mipsel-linux-gnu-gcc", "-c", "-O2", "-march=r3000", "-mabi=32", "-mno-abicalls", "-fno-pic", "-G0",
      "-fno-builtin", "-ffreestanding", "-fno-strict-aliasing", "-msoft-float", "-std=gnu89", "-w", "-fcommon",
      "-ffunction-sections", "-fdata-sections", "-mno-check-zero-division", "-I", os.path.join(AQUI, "include")]
BASE_EXE = 0x80010000
OFF_EXE = 0x800


def run(cmd, **k):
    return subprocess.run(cmd, capture_output=True, text=True, **k)


def simbolos():
    sim = {}
    for l in run(["mipsel-linux-gnu-nm", "build/slus_012.08.elf"]).stdout.splitlines():
        p = l.split()
        if len(p) == 3:
            sim[p[2]] = int(p[0], 16)
    return sim


def leer_tsv(p):
    with open(p, encoding="utf-8") as f:
        return list(csv.DictReader(f, delimiter="\t"))


def elegir(sint, solo):
    """{funcion: archivo}: auditoria a mano primero, despues los borradores de m2c que pasaron."""
    buenos = {"IGUAL", "IGUAL_V0"} | ({"IGUAL_SINT", "IGUAL_V0_SINT"} if sint else set())
    esc = {}
    for r in leer_tsv("../notas/fases/auditoria.tsv"):
        if r["estado"] in buenos and r["archivo"].endswith(".c"):
            esc.setdefault(r["funcion"], r["archivo"])
    for r in leer_tsv("progreso.tsv"):
        if r["estado"] in ("IGUAL", "IGUAL_V0") and r["funcion"] not in esc:
            f = f"src/auto/{r['funcion']}.c"
            if os.path.exists(f):
                esc[r["funcion"]] = f
    if solo:
        esc = {f: a for f, a in esc.items() if f in solo}
    return esc


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--solo")
    ap.add_argument("--sint", action="store_true")
    ap.add_argument("--salida", default="build/SLUS_C.exe")
    ap.add_argument("--O")
    a = ap.parse_args()
    cc = list(CC)
    if a.O:
        cc[cc.index("-O2")] = "-" + a.O
    solo = set(a.solo.split(",")) if a.solo else None
    sim = simbolos()
    sim["__muldi3"] = sim["func_80029214"]
    tam = {}
    for l in open("funciones_juego.tsv", encoding="utf-8"):
        p = l.rstrip("\n").split("\t")
        if len(p) == 3:
            tam[p[2]] = (int(p[0], 16), int(p[1]))
    exe = bytearray(open("SLUS_012.08", "rb").read())
    elegidas = elegir(a.sint, solo)
    informe = []
    tmp = tempfile.mkdtemp()

    # 1. compilar cada archivo una vez
    objs = {}
    for arch in sorted(set(elegidas.values())):
        o = os.path.join(tmp, re.sub(r"\W", "_", arch) + ".o")
        r = run(cc + ["-o", o, arch])
        if r.returncode:
            informe.append(f"NO_COMPILA\t{arch}\t{r.stderr.splitlines()[0] if r.stderr else ''}")
            continue
        objs[arch] = o

    # 2. funciones que define cada objeto. Las que no son las elegidas para ese archivo (versiones viejas o
    # distintas de otra funcion ya hecha en otro archivo) se quitan del objeto: sus llamadas quedan sin
    # resolver y van a la direccion original, como en la verificacion. Las elegidas ganan el alias c__Nombre (las otras se debilitan, el enlace deja el nombre en la direccion original).
    defin = {}          # nombre -> archivo
    for arch, o in list(objs.items()):
        extra, quitar = [], []
        for l in run(["mipsel-linux-gnu-objdump", "-t", o]).stdout.splitlines():
            p = l.split()
            if len(p) >= 6 and p[1] == "g" and p[2] == "F" and p[3].startswith(".text") and p[-1] in sim:
                if elegidas.get(p[-1]) == arch:
                    defin[p[-1]] = arch
                    extra += ["--add-symbol", f"c__{p[-1]}={p[3]}:0x{int(p[0], 16):x},global,function"]
                else:
                    quitar.append(p[-1])
        cmd = ["mipsel-linux-gnu-objcopy", *extra, *[f"--weaken-symbol={n_}" for n_ in sorted(set(quitar))], o]
        r = run(cmd)
        if r.returncode:
            informe.append(f"NO_PREPARA	{arch}	{r.stderr.strip().splitlines()[0] if r.stderr.strip() else ''}")
            del objs[arch]
            for n in [n for n, ar in defin.items() if ar == arch]:
                del defin[n]
    # solo se instalan las elegidas que el objeto defina de verdad
    instalar = [f for f in elegidas if f in defin and elegidas[f] in objs]
    for f in elegidas:
        if f not in instalar and elegidas[f] in objs:
            informe.append(f"NO_DEFINIDA	{f}	{elegidas[f]}")

    while True:
        # 2b. primer enlace de prueba con --gc-sections para saber que secciones sirven de verdad (lo que solo
        # usaba una funcion quitada, o una auxiliar sin llamar, no hace falta colocarlo)
        prueba = os.path.join(tmp, "prueba.ld")
        nombres0 = set()
        for o in objs.values():
            for u in run(["mipsel-linux-gnu-nm", "-u", o]).stdout.split():
                if u != "U":
                    nombres0.add(u)
        for n in nombres0 | set(defin):
            if n not in sim:
                sys.exit(f"simbolo desconocido: {n}")
        with open(prueba, "w") as fh:
            for n in sorted(nombres0 | set(defin)):
                fh.write(f"{n} = 0x{sim[n]:08X};\n")
            fh.write("SECTIONS { . = 0x80400000; .text : { *(.text*) } .rodata : { *(.rodata*) } "
                     ".data : { *(.data*) *(.sdata*) } .bss : { *(.bss*) *(.sbss*) *(COMMON) } }\n")
        mapa = os.path.join(tmp, "prueba.map")
        r = run(["mipsel-linux-gnu-ld", "-EL", "-T", prueba, "--gc-sections", "-nostdlib", "--no-check-sections",
                 "-Map", mapa, "-o", os.path.join(tmp, "prueba.elf"), *[x for f in instalar for x in ("-u", "c__" + f)],
                 *objs.values()])
        if r.returncode:
            sys.exit("no enlaza (prueba):\n" + r.stderr)
        descartadas = set()
        txt = open(mapa).read()
        ini = txt.index("Discarded input sections")
        fin = txt.index("Memory Configuration")
        cur = None
        for l in txt[ini:fin].splitlines()[1:]:
            m = re.match(r"^ (\S+)\s*$", l)
            m2 = re.match(r"^ (\S+)\s+0x[0-9a-f]+\s+0x[0-9a-f]+\s+(\S+)", l)
            if m:
                cur = m.group(1)
            elif m2:
                descartadas.add((m2.group(2), m2.group(1)))
            elif cur and re.match(r"^\s+0x[0-9a-f]+\s+0x[0-9a-f]+\s+(\S+)", l):
                descartadas.add((re.match(r"^\s+0x[0-9a-f]+\s+0x[0-9a-f]+\s+(\S+)", l).group(1), cur))
        if any(i.startswith("DUPLICADA") for i in informe):
            sys.exit("\n".join(informe))

        # 3. tamano de cada seccion de cada objeto
        secc = []           # (archivo, nombre, tam, alineacion, tipo)
        for arch, o in objs.items():
            for l in run(["mipsel-linux-gnu-objdump", "-h", o]).stdout.splitlines():
                m = re.match(r"\s*\d+\s+(\S+)\s+([0-9a-f]+)\s+[0-9a-f]+\s+[0-9a-f]+\s+[0-9a-f]+\s+2\*\*(\d+)", l)
                if m and int(m.group(2), 16) and not m.group(1).startswith((".comment", ".pdr", ".gnu", ".mdebug",
                                                                              ".reginfo", ".MIPS", ".note", ".debug")):
                    if (objs[arch], m.group(1)) in descartadas:
                        continue
                    secc.append((arch, m.group(1), int(m.group(2), 16), 1 << int(m.group(3))))

        # 4. huecos: el cuerpo de cada funcion que se instala, menos los 8 bytes del salto
        huecos = []
        for f in instalar:
            d, t = tam[f]
            if t > 8:
                huecos.append([d + 8, d + t])
        huecos.sort()

        # 5. colocar primero lo grande (first fit); las secciones de un mismo archivo pueden ir en huecos distintos
        colocadas = {}
        sin_sitio = []
        for arch, nom, t, al in sorted(secc, key=lambda s: -s[2]):
            for h in huecos:
                ini = (h[0] + al - 1) & ~(al - 1)
                if ini + t <= h[1]:
                    colocadas[(arch, nom)] = ini
                    h[0] = ini + t
                    break
            else:
                sin_sitio.append((arch, nom, t))
        if sin_sitio:
            total = sum(s[2] for s in secc)
            libre = sum(h[1] - h[0] for h in huecos)
            # lo que no cabe se deja con la funcion original: se quitan las que poseen esas secciones
            quitar = set()
            for arch_, nom_, t_ in sin_sitio:
                if nom_.startswith(".text."):
                    quitar.add(nom_[len(".text."):])
                else:
                    quitar |= {f for f in instalar if defin[f] == arch_}
            quitar &= set(instalar)
            if not quitar:
                sys.exit(f"no caben {len(sin_sitio)} secciones y no se sabe de quien: {sin_sitio[:3]}")
            for f in sorted(quitar):
                informe.append(f"SIN_SITIO	{f}	{elegidas[f]}")
            instalar = [f for f in instalar if f not in quitar]
            continue
        break

    # 6. script del enlazador con cada seccion en su sitio
    ld = os.path.join(tmp, "c.ld")
    with open(ld, "w") as fh:
        nombres = set()
        for o in objs.values():
            for u in run(["mipsel-linux-gnu-nm", "-u", o]).stdout.split():
                if u != "U":
                    nombres.add(u)
        for n in sorted(nombres | set(defin)):
            if n not in sim:
                sys.exit(f"simbolo desconocido: {n}")
            fh.write(f"{n} = 0x{sim[n]:08X};\n")
        fh.write("SECTIONS {\n")
        for i, ((arch, nom), dirc) in enumerate(sorted(colocadas.items(), key=lambda kv: kv[1])):
            fh.write(f'  .p{i} 0x{dirc:08X} : {{ "{objs[arch]}"({nom}) }}\n')
        fh.write("}\n")
    elf = os.path.join(tmp, "c.elf")
    r = run(["mipsel-linux-gnu-ld", "-EL", "-T", ld, "--no-check-sections", "-nostdlib", "-o", elf] +
             [x for f in instalar for x in ("-u", "c__" + f)] + list(objs.values()))
    if r.returncode:
        sys.exit("no enlaza:\n" + r.stderr)
    binario = os.path.join(tmp, "c.bin")
    run(["mipsel-linux-gnu-objcopy", "-O", "binary", elf, binario])
    plano = open(binario, "rb").read()

    # 7. volcar lo enlazado al ejecutable
    cab = run(["mipsel-linux-gnu-readelf", "-S", "-W", elf]).stdout
    secs = []
    for l in cab.splitlines():
        m = re.match(r"\s*\[\s*\d+\]\s+\.p\d+\s+(\w+)\s+([0-9a-f]+)\s+[0-9a-f]+\s+([0-9a-f]+)", l)
        if m:
            secs.append((int(m.group(2), 16), int(m.group(3), 16), m.group(1)))
    base = min(s[0] for s in secs)
    # primero se matan los cuerpos viejos (break) para que un salto perdido se note enseguida
    for f in instalar:
        d, t = tam[f]
        for x in range(d + 8, d + t, 4):
            struct.pack_into("<I", exe, x - BASE_EXE + OFF_EXE, 0x0000000D)
    for dirc, t, tipo in secs:
        if tipo == "NOBITS":
            exe[dirc - BASE_EXE + OFF_EXE: dirc - BASE_EXE + OFF_EXE + t] = bytes(t)
        else:
            exe[dirc - BASE_EXE + OFF_EXE: dirc - BASE_EXE + OFF_EXE + t] = plano[dirc - base: dirc - base + t]
    dirs = {}
    for l in run(["mipsel-linux-gnu-nm", elf]).stdout.splitlines():
        p = l.split()
        if len(p) == 3:
            dirs[p[2]] = int(p[0], 16)
    for f in instalar:
        d, t = tam[f]
        c = dirs["c__" + f]
        o = d - BASE_EXE + OFF_EXE
        struct.pack_into("<II", exe, o, 0x08000000 | ((c >> 2) & 0x03FFFFFF), 0)
        informe.append(f"OK\t{f}\t{elegidas[f]}\t{t}")
    open(a.salida, "wb").write(exe)
    with open("build/armado_c.txt", "w", encoding="utf-8") as fh:
        fh.write("\n".join(informe) + "\n")
    usado = sum(s[1] for s in secs)
    print(f"{len(instalar)} funciones en C, {usado} bytes de C colocados, salida {a.salida}")
    print("otros:", sum(1 for i in informe if not i.startswith("OK")), "(ver build/armado_c.txt)")


main()
