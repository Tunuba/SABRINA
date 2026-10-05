"""Capturas en cascada en lote: para cada funcion verificada solo con capturas sinteticas, busca en el asm quien la
llama; si alguno tiene capturas REALES, corre su original desde ellas y guarda la captura al entrar a la funcion
(argumentos de una partida de verdad en lugar de los inventados). Las deja en capturas_sint/F/NN con NN.MANO.

Uso: python3 verif/cascada_lote.py [--max-por-funcion 3] [--solo F1,F2] [--tope 20000000]
Escribe una linea por funcion: cuantas capturas nuevas salieron y de que padre.
"""
import glob
import os
import re
import sys
import collections

AQUI = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(AQUI)
sys.path.insert(0, AQUI)
import verificar as V
from unicorn import UC_HOOK_CODE
from unicorn.mips_const import UC_MIPS_REG_ZERO, UC_MIPS_REG_HI, UC_MIPS_REG_LO

args = sys.argv[1:]
maximo = int(args[args.index("--max-por-funcion") + 1]) if "--max-por-funcion" in args else 3
tope = int(float(args[args.index("--tope") + 1])) if "--tope" in args else 20_000_000
solo = set(args[args.index("--solo") + 1].split(",")) if "--solo" in args else None

# quien llama a quien (jal directos)
llamadores = collections.defaultdict(set)
for ruta in glob.glob(os.path.join(AQUI, "asm", "*.s")):
    actual = None
    with open(ruta, errors="replace") as asm:
        for l in asm:
            m = re.match(r"\s*glabel (\w+)\s*$", l)
            if m:
                actual = m.group(1)
                continue
            m = re.search(r"\bjal\s+(\w+)\s*$", l)
            if m and actual:
                llamadores[m.group(1)].add(actual)


def estados(ruta, col_estado):
    r = {}
    for l in open(ruta, encoding="utf-8", errors="replace"):
        p = l.rstrip("\n").split("\t")
        if len(p) > col_estado:
            r[p[0]] = p[col_estado]
    return r


aud = estados("../notas/fases/auditoria.tsv", 2)
prog = estados("progreso.tsv", 2)
psint = estados("progreso_sint.tsv", 2)
reales = {f for d in (aud, prog) for f, e in d.items() if e in ("IGUAL", "IGUAL_V0")}
sinteticas = sorted({f for d in (aud, psint) for f, e in d.items() if e.endswith("_SINT") and e.startswith("IGUAL")}
                    - reales)
if solo:
    sinteticas = [f for f in sinteticas if f in solo]
sim = V.simbolos()
orig_uc = V.Uc
estado = {}


def Uc2(*a):
    u = orig_uc(*a)
    es = u.emu_start

    def emu_start(*x, **k):
        def entrada(uu, d, t, _):
            if estado["hecho"]:
                return
            regs = [uu.reg_read(UC_MIPS_REG_ZERO + i) for i in range(32)]
            regs[0] = 0
            regs += [d, uu.reg_read(UC_MIPS_REG_HI), uu.reg_read(UC_MIPS_REG_LO)]
            base = estado["base"]
            open(base + ".ram", "wb").write(bytes(uu.mem_read(0, 0x200000)))
            open(base + ".spad", "wb").write(bytes(uu.mem_read(0x1F800000, 0x400)))
            open(base + ".regs", "w", newline="").write(" ".join("%08x" % r for r in regs))
            open(base + ".MANO", "w", newline="").write(
                f"en cascada: la primera entrada a {estado['hija']} corriendo la original de {estado['padre']} "
                f"desde su captura real {estado['cap']}\n")
            estado["hecho"] = True
            uu.emu_stop()
        u.hook_add(UC_HOOK_CODE, entrada, begin=sim[estado["hija"]], end=sim[estado["hija"]])
        return es(*x, **k)
    u.emu_start = emu_start
    return u


V.Uc = Uc2
for f in sinteticas:
    if f not in sim:
        continue
    destino = os.path.join(AQUI, "capturas_sint", f)
    ya = [x for x in glob.glob(os.path.join(destino, "*.MANO")) if "cascada" in open(x).read()
          and "captura real" in open(x).read()]
    if ya:
        print(f"{f}: ya tiene {len(ya)} en cascada", flush=True)
        continue
    nuevas, de = 0, set()
    for padre in sorted(llamadores.get(f, ())):
        if padre not in sim:
            continue
        for cap in sorted(glob.glob(os.path.join(AQUI, "capturas", padre, "*.regs")))[:6]:
            if nuevas >= maximo:
                break
            os.makedirs(destino, exist_ok=True)
            nn = len(glob.glob(os.path.join(destino, "*.regs")))
            estado.update(hecho=False, hija=f, padre=padre, cap=os.path.relpath(cap[:-5], AQUI),
                          base=os.path.join(destino, "%02d" % nn))
            try:
                V.ejecutar(cap[:-5], sim[padre], None, cuenta=tope)
            except Exception as e:
                print(f"  {f} desde {padre}: error {e}", flush=True)
            if estado["hecho"]:
                nuevas += 1
                de.add(padre)
        if nuevas >= maximo:
            break
    print(f"{f}: {nuevas} nuevas" + (f" (de {', '.join(sorted(de))})" if de else
          (" (ningun llamador con capturas reales llega)" if llamadores.get(f) else " (nadie la llama con jal)")),
          flush=True)
