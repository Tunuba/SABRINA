"""Cosecha de capturas: corre la ORIGINAL de un padre desde sus capturas REALES con un gancho en la entrada de todas
las funciones verificadas solo con sinteticas, y guarda la primera entrada de cada una como captura sintetica
(capturas_sint/F/NN, con NN.MANO). Sirve para las que se llaman por puntero (el actualizar de cada objeto), que
no tienen padre en el grafo de llamadas: la actualizacion de un cuadro (func_80019D80) llama a todos los objetos
vivos de esa partida.

Uso: python3 verif/cosecha.py padre [--capturas 4] [--tope 300000000] [--por-funcion 2]
"""
import glob
import os
import sys

AQUI = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(AQUI)
sys.path.insert(0, AQUI)
import verificar as V
from unicorn import UC_HOOK_CODE
from unicorn.mips_const import UC_MIPS_REG_ZERO, UC_MIPS_REG_HI, UC_MIPS_REG_LO

args = sys.argv[1:]
padre = args[0]
ncap = int(args[args.index("--capturas") + 1]) if "--capturas" in args else 4
tope = int(float(args[args.index("--tope") + 1])) if "--tope" in args else 300_000_000
por_funcion = int(args[args.index("--por-funcion") + 1]) if "--por-funcion" in args else 2


def estados(ruta):
    r = {}
    for l in open(ruta, encoding="utf-8", errors="replace"):
        p = l.rstrip("\n").split("\t")
        if len(p) > 2:
            r[p[0]] = p[2]
    return r


aud, prog, psint = estados("../notas/fases/auditoria.tsv"), estados("progreso.tsv"), estados("progreso_sint.tsv")
reales = {f for d in (aud, prog) for f, e in d.items() if e in ("IGUAL", "IGUAL_V0")}
sinteticas = {f for d in (aud, psint) for f, e in d.items() if e.endswith("_SINT") and e.startswith("IGUAL")} - reales
sim = V.simbolos()
por_dir = {sim[f]: f for f in sinteticas if f in sim}


def cosechadas(f):
    return [x for x in glob.glob(os.path.join(AQUI, "capturas_sint", f, "*.MANO"))
            if "cosecha" in open(x).read()]


cuenta = {f: len(cosechadas(f)) for f in por_dir.values()}
nuevas = {}
estado = {}
orig_uc = V.Uc


def Uc2(*a):
    u = orig_uc(*a)
    es = u.emu_start

    def emu_start(*x, **k):
        def entrada(uu, d, t, _):
            f = por_dir.get(d)
            if f is None or f in estado["vistas"] or cuenta[f] >= por_funcion:
                return
            estado["vistas"].add(f)
            destino = os.path.join(AQUI, "capturas_sint", f)
            os.makedirs(destino, exist_ok=True)
            base = os.path.join(destino, "%02d" % len(glob.glob(os.path.join(destino, "*.regs"))))
            regs = [uu.reg_read(UC_MIPS_REG_ZERO + i) for i in range(32)]
            regs[0] = 0
            regs += [d, uu.reg_read(UC_MIPS_REG_HI), uu.reg_read(UC_MIPS_REG_LO)]
            open(base + ".ram", "wb").write(bytes(uu.mem_read(0, 0x200000)))
            open(base + ".spad", "wb").write(bytes(uu.mem_read(0x1F800000, 0x400)))
            open(base + ".regs", "w", newline="").write(" ".join("%08x" % r for r in regs))
            open(base + ".MANO", "w", newline="").write(
                f"cosecha: la primera entrada a {f} corriendo la original de {padre} desde su captura real "
                f"{estado['cap']}\n")
            cuenta[f] += 1
            nuevas[f] = nuevas.get(f, 0) + 1
        # un solo gancho de bloque sobre todo el codigo sale mas barato que uno por funcion
        for d in por_dir:
            u.hook_add(UC_HOOK_CODE, entrada, begin=d, end=d)
        return es(*x, **k)
    u.emu_start = emu_start
    return u


V.Uc = Uc2
for cap in sorted(glob.glob(os.path.join(AQUI, "capturas", padre, "*.regs")))[:ncap]:
    estado.update(cap=os.path.relpath(cap[:-5], AQUI), vistas=set())
    r = V.ejecutar(cap[:-5], sim[padre], None, cuenta=tope)
    print(f"{os.path.basename(cap)}: {r['error'] or 'termina'}; entraron {len(estado['vistas'])} sinteticas",
          flush=True)
print(f"{len(nuevas)} funciones con capturas nuevas:", " ".join(sorted(nuevas)), flush=True)
