# 05-10: anota a0-a2 en cada entrada a una funcion (por direccion) en la original y en el C, para ver donde se
# separan. uso (WSL, desde decomp): python3 verif/depurar_args.py src/x.c funcion captura dir_hex [a0 a1 a2 a3]
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import verificar as V
from unicorn import UC_HOOK_CODE
from unicorn.mips_const import UC_MIPS_REG_A0, UC_MIPS_REG_SP

c, f, n, dirf = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4], 16)
sim = V.simbolos()
codigo_c, dirs = V.compilar(c, [f])
V.EN_PRUEBA["f"] = f
V.MAPA_C.update({dirs[k]: sim[k] for k in dirs if k in sim})
cap = sorted(glob.glob(os.path.join(V.AQUI, "capturas", f, "*.regs")))[n][:-5]
regs = None
if len(sys.argv) > 5:
    regs = [int(x, 16) for x in open(cap + ".regs").read().split()]
    for i, v in enumerate(sys.argv[5:9]):
        regs[4 + i] = int(v, 16)

registro = []
Original = V.Uc


def Uc(*a):
    u = Original(*a)
    u.hook_add(UC_HOOK_CODE, lambda u, d, t, _: registro.append(
        tuple(u.reg_read(UC_MIPS_REG_A0 + i) for i in range(3)) + (u.reg_read(UC_MIPS_REG_SP),)), begin=dirf, end=dirf)
    return u


V.Uc = Uc
a = V.ejecutar(cap, sim[f], None, regs)
ra, registro[:] = list(registro), []
b = V.ejecutar(cap, dirs[f], codigo_c, regs)
rb = list(registro)
print(len(ra), len(rb))
pa, pb = [x[:3] for x in ra], [x[:3] for x in rb]
k = next((i for i in range(min(len(pa), len(pb))) if pa[i] != pb[i]), min(len(pa), len(pb)))
print("se separan en", k)
for i in range(max(0, k - 2), min(k + 4, max(len(pa), len(pb)))):
    print(i, [hex(v) for v in pa[i]] if i < len(pa) else None, [hex(v) for v in pb[i]] if i < len(pb) else None)
