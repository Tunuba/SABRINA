# 05-10: muestra, para una captura, las palabras de RAM distintas entre la original y el C y las llamadas anotadas
# (destino, ra, sp) de cada una, para ver por que la reubicacion de ra/sp no las cubre.
# uso (WSL, desde decomp): python3 verif/depurar_ra.py src/archivo.c funcion [captura]
import glob, os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import verificar as V
if "--sint" in sys.argv:
    sys.argv.remove("--sint")
    import sint
    V = sint.usar_sinteticas()
    V.AQUI_CAPS = "capturas_sint"

c, f = sys.argv[1], sys.argv[2]
sim = V.simbolos()
codigo_c, dirs = V.compilar(c, [f])
caps = sorted(glob.glob(os.path.join(V.AQUI, getattr(V, "AQUI_CAPS", "capturas"), f, "*.regs")))
cap = caps[int(sys.argv[3]) if len(sys.argv) > 3 else 0][:-5]
V.EN_PRUEBA["f"] = f
V.MAPA_C.update({dirs[n]: sim[n] for n in dirs if n in sim})
a = V.ejecutar(cap, sim[f], None)
b = V.ejecutar(cap, dirs[f], codigo_c)
print("error", a["error"], b["error"])
for x, y in zip(a["llamadas"], b["llamadas"]):
    print("  ", [None if v is None else hex(v) for v in x], "|", [None if v is None else hex(v) for v in y])
print(len(a["llamadas"]), len(b["llamadas"]))
for i in range(0, 0x200000, 4):
    if a["ram"][i:i + 4] != b["ram"][i:i + 4]:
        print(f"{0x80000000 + i:08x}: {struct.unpack_from('<I', a['ram'], i)[0]:08x} {struct.unpack_from('<I', b['ram'], i)[0]:08x}")
print(V.comparar(a, b, a["sp"]))
