# Corre la original de una funcion en su captura 00 con y sin el gancho de escrituras de hardware.
import glob, os, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import verificar as V
import unicorn
f = sys.argv[1]
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
base = sorted(glob.glob(os.path.join("capturas", f, "*.regs")))[0][:-5]
sim = V.simbolos()
print("con gancho:", V.ejecutar(base, sim[f], None)["error"])
orig = unicorn.Uc.hook_add
def sin_hw(self, tipo, cb, *a, **k):
    if tipo == unicorn.UC_HOOK_MEM_WRITE and k.get("begin") == 0x1F801000:
        return None
    return orig(self, tipo, cb, *a, **k)
unicorn.Uc.hook_add = sin_hw
print("sin gancho:", V.ejecutar(base, sim[f], None)["error"])
