cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
python3 - "$@" <<'PY'
import sys, glob, os, bisect, collections
import verificar as V
from unicorn import UC_HOOK_BLOCK
sim = V.simbolos()
fun = sorted((a, n) for n, a in sim.items() if 0x80010000 <= a < 0x80070000 and not n.startswith(("jtbl_", "D_", ".L")))
dirs = [a for a, n in fun]
cuenta = collections.Counter()
orig_uc = V.Uc
def Uc2(*a):
    u = orig_uc(*a)
    es = u.emu_start
    def emu_start(*x, **k):
        def blk(uu, d, t, _):
            i = bisect.bisect_right(dirs, d) - 1
            cuenta[fun[i][1] if i >= 0 else hex(d)] += 1
        u.hook_add(UC_HOOK_BLOCK, blk)
        return es(*x, **k)
    u.emu_start = emu_start
    return u
V.Uc = Uc2
f = sys.argv[1]
caps = sorted(glob.glob(os.path.join("capturas", f, "*.regs")))
r = V.ejecutar(caps[0][:-5], sim[f], None, cuenta=int(sys.argv[2]) if len(sys.argv) > 2 else 3000000)
print(r["error"])
for n, c in cuenta.most_common(25): print(c, n)
PY
