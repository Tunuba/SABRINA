# 05-10: en la corrida del C, las escrituras que hace codigo de fuera del C (la original y la BIOS) por encima del sp
# mas bajo del C, o sea dentro de los marcos de la funcion en C; para ver si una funcion llamada pisa el marco.
# uso (WSL, desde decomp): python3 verif/depurar_pila.py src/x.c funcion captura [a0 a1 a2 a3]
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import verificar as V
from unicorn import UC_HOOK_MEM_WRITE, UC_HOOK_CODE
from unicorn.mips_const import UC_MIPS_REG_PC, UC_MIPS_REG_SP

c, f, n = sys.argv[1], sys.argv[2], int(sys.argv[3])
sim = V.simbolos()
codigo_c, dirs = V.compilar(c, [f])
V.EN_PRUEBA["f"] = f
V.MAPA_C.update({dirs[k]: sim[k] for k in dirs if k in sim})
cap = sorted(glob.glob(os.path.join(V.AQUI, "capturas", f, "*.regs")))[n][:-5]
regs = [int(x, 16) for x in open(cap + ".regs").read().split()]
for i, v in enumerate(sys.argv[4:8]):
    regs[4 + i] = int(v, 16)
ini_c, fin_c = V.BASE_C, V.BASE_C + len(codigo_c)
estado = {"sp_c": 0xFFFFFFFF}
pisadas = []
Original = V.Uc


def Uc(*a):
    u = Original(*a)

    def codigo(u, d, t, _):
        estado["sp_c"] = min(estado["sp_c"], u.reg_read(UC_MIPS_REG_SP))

    def escribe(u, acc, d, tam, v, _):
        pc = u.reg_read(UC_MIPS_REG_PC)
        d |= 0x80000000
        if not (ini_c <= pc < fin_c) and estado["sp_c"] <= d < regs[29] and d >= u.reg_read(UC_MIPS_REG_SP) + 0:
            # por encima del sp del que escribe: no es su propio marco
            pisadas.append((pc, d, tam, v))

    u.hook_add(UC_HOOK_CODE, codigo, begin=ini_c, end=fin_c)
    u.hook_add(UC_HOOK_MEM_WRITE, escribe)
    return u


V.Uc = Uc
b = V.ejecutar(cap, dirs[f], codigo_c, regs)
print("error", b["error"], "sp mas bajo del C", hex(estado["sp_c"]), "pisadas", len(pisadas))
vistas = set()
for pc, d, tam, v in pisadas:
    if (pc, d) not in vistas:
        vistas.add((pc, d))
        print(f"  pc {pc:08x} escribe {tam} en {d:08x} = {v & 0xFFFFFFFF:08x}")
    if len(vistas) > 30:
        break
