# Prueba (sin tocar verificar.py): con el registro de estado de la GPU (0x1F801814) siempre "lista", cuales
# de las funciones dadas terminan en su primera captura.
# uso (WSL, venv): python3 verif/prueba_gpu.py [valor] f1 f2 ...
import glob, os, struct, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import verificar as V
from unicorn import UC_HOOK_MEM_READ

GPUSTAT = 0x1F801814
args = sys.argv[1:]
valor = int(args.pop(0), 0) if args and args[0].startswith("0x") else 0x1C000000

orig_hook_add = None


def parchar():
    import unicorn
    viejo = unicorn.Uc.__init__

    def nuevo(self, *a, **k):
        viejo(self, *a, **k)
        def lee(u, acceso, dirc, tam, v, _):
            u.mem_write(GPUSTAT, struct.pack("<I", valor))
        self._gpu = lee
        self.__dict__["_gpu_puesto"] = False
        orig = self.emu_start
        def emu_start(*aa, **kk):
            if not self.__dict__["_gpu_puesto"]:
                self.hook_add(UC_HOOK_MEM_READ, lee, begin=GPUSTAT, end=GPUSTAT + 3)
                self.__dict__["_gpu_puesto"] = True
            return orig(*aa, **kk)
        self.emu_start = emu_start
    unicorn.Uc.__init__ = nuevo


parchar()
sim = V.simbolos()
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
for f in args:
    caps = sorted(glob.glob(os.path.join("capturas", f, "*.regs")))
    if not caps:
        print(f, "SIN_CAPTURAS", flush=True)
        continue
    r = V.ejecutar(caps[0][:-5], sim[f], None)
    print(f, r["error"] or "termina", flush=True)
