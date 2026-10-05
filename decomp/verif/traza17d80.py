# uso (desde decomp, en WSL con el venv): python3 verif/traza17d80.py -> corre las 2 variantes raras en la original y
# en el C y anota cada llamada a printf, CdSearchFile y _putchar (copiar y cambiar VIGILAR para otra funcion)
# traza de la variante a0=0x10000 de func_80017D80: original contra C
import sys, os
sys.path.insert(0, os.getcwd())
import verificar as V
from unicorn import Uc as UcReal
from unicorn.mips_const import *
log = []
VIGILAR = {0x800151B0: "printf", 0x8002BE88: "CdSearchFile", 0x80017D3C: "f17D3C", 0x80014CB0: "_putchar"}
cuenta = {}
def h(u, d, t, _):
    n = VIGILAR.get(d)
    if n:
        cuenta[n] = cuenta.get(n, 0) + 1
        if cuenta[n] <= 4:
            a0 = u.reg_read(UC_MIPS_REG_A0); sp = u.reg_read(UC_MIPS_REG_SP); ra = u.reg_read(UC_MIPS_REG_RA)
            s = bytes(u.mem_read(a0 & 0x1FFFFF, 48)) if (a0 & 0x1FFFFFFF) < 0x200000 else b""
            log.append(f"{n} a0={a0:08x} a1={u.reg_read(UC_MIPS_REG_A1):08x} sp={sp:08x} ra={ra:08x} {s[:48]!r}")
def UcT(*a):
    u = UcReal(*a)
    u.hook_add(1 << 2, h, None, 0x80014000, 0x8002C000)
    return u
V.Uc = UcT
sim = V.simbolos()
c = "src/File/archivo_entero_g14.c"
codigo_c, dirs = V.compilar(c, ["func_80017D80"])
f = "func_80017D80"
V.PILA_LOCAL["bytes"] = 0x4000
for cap in ("00", "04"):
    base = f"capturas/{f}/{cap}"
    regs = [int(x, 16) for x in open(base + ".regs").read().split()]
    regs[4] = 0x10000 if cap == "00" else 0x10001
    if cap == "00":
        regs[5], regs[6], regs[7] = 0xc92, 0xffffffff, 0x801ffe45
    else:
        regs[5], regs[6], regs[7] = 0, 0xeb9cf9f0, 0xba040001
    for nom, pc, cod in (("ORIGINAL", sim[f], None), ("C", dirs[f], codigo_c)):
        log.clear(); cuenta.clear()
        os.environ["SABRINA_LIMITE"] = "20000000"
        r = V.ejecutar(base, pc, cod, regs)
        print(f"== {cap} {nom} error={r['error']} sp={regs[29]:08x}")
        for l in log: print("  ", l)
        print("   cuentas", cuenta)
