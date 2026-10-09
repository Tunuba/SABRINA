# 05-10: que registros del GTE quedan distintos entre la original y el C en una captura (con a0-a3 opcionales).
# uso (WSL, desde decomp): python3 verif/depurar_gte.py src/x.c funcion captura [a0 a1 a2 a3 en hex]
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import verificar as V

c, f, n = sys.argv[1], sys.argv[2], int(sys.argv[3])
sim = V.simbolos()
codigo_c, dirs = V.compilar(c, [f])
V.EN_PRUEBA["f"] = f
V.MAPA_C.update({dirs[k]: sim[k] for k in dirs if k in sim})
cap = sorted(glob.glob(os.path.join(V.AQUI, "capturas", f, "*.regs")))[n][:-5]
regs = None
if len(sys.argv) > 4:
    regs = [int(x, 16) for x in open(cap + ".regs").read().split()]
    for i, v in enumerate(sys.argv[4:8]):
        regs[4 + i] = int(v, 16)
a = V.ejecutar(cap, sim[f], None, regs)
b = V.ejecutar(cap, dirs[f], codigo_c, regs)
print("error", a["error"], b["error"])
for nombre, x, y in (("datos", a["gte"][0], b["gte"][0]), ("control", a["gte"][1], b["gte"][1])):
    for i, (p, q) in enumerate(zip(x, y)):
        if p != q:
            print(f"  {nombre}[{i}]: {p & 0xFFFFFFFF:08x} {q & 0xFFFFFFFF:08x}")
print("llamadas", [hex(x[0]) for x in a["llamadas"]])
print("llamadas", [hex(x[0]) for x in b["llamadas"]])
print(V.comparar(a, b, a["sp"]))
