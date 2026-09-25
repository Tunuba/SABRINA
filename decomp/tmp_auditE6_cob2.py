import glob, os, random, verificar
from unicorn import UC_HOOK_CODE
f = "func_8004E8C4"
sim = verificar.simbolos(); ini, fin = sim[f], verificar.fin_de(f)
toc = set(); orig = verificar.Uc.emu_start
def es(self, *a, **k):
    self.hook_add(UC_HOOK_CODE, lambda u, d, t, _: toc.add(d), begin=ini, end=fin - 1)
    return orig(self, *a, **k)
verificar.Uc.emu_start = es
caps = sorted(glob.glob(os.path.join(verificar.AQUI, "capturas", f, "*.regs")))
rnd = random.Random(1234); pool = verificar.constantes_de(f)
for cap in caps:
    base = cap[:-5]; verificar.ejecutar(base, ini, None)
    regs = [int(x, 16) for x in open(base + ".regs").read().split()]
    for r in verificar.variantes(regs, pool, 30, rnd): verificar.ejecutar(base, ini, None, r)
falta = [hex(a) for a in range(ini, fin, 4) if a not in toc]
print("faltan", falta)
