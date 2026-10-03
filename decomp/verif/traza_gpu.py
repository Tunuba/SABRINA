# Como prueba_gpu.py pero guarda los ultimos saltos antes del error (para ver de donde sale un salto a 0).
import glob, os, struct, sys, collections
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import verificar as V
import unicorn
from unicorn import UC_HOOK_MEM_READ, UC_HOOK_BLOCK
GPUSTAT = 0x1F801814
ult = collections.deque(maxlen=12)
viejo = unicorn.Uc.__init__
def nuevo(self, *a, **k):
    viejo(self, *a, **k)
    orig = self.emu_start
    def emu_start(*aa, **kk):
        self.hook_add(UC_HOOK_MEM_READ, lambda u, ac, d, t, v, _: u.mem_write(GPUSTAT, struct.pack("<I", 0x1C000000)),
                      begin=GPUSTAT, end=GPUSTAT + 3)
        self.hook_add(UC_HOOK_BLOCK, lambda u, d, t, _: ult.append(d))
        return orig(*aa, **kk)
    self.emu_start = emu_start
unicorn.Uc.__init__ = nuevo
sim = V.simbolos()
inv = sorted((a, n) for n, a in sim.items() if 0x80010000 <= a < 0x80070000)
import bisect
ds = [a for a, n in inv]
def nom(pc):
    i = bisect.bisect_right(ds, pc) - 1
    return f"{inv[i][1]}+{pc - inv[i][0]:x}" if i >= 0 else hex(pc)
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
f = sys.argv[1]
r = V.ejecutar(sorted(glob.glob(os.path.join("capturas", f, "*.regs")))[0][:-5], sim[f], None)
print(r["error"])
print(" <- ".join(nom(d) for d in reversed(ult)))
