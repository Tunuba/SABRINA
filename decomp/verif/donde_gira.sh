#!/bin/bash
# uso: donde_gira.sh func ...  -> corre la ORIGINAL en su primera captura y dice en que pc queda girando
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
python3 - "$@" <<'PY'
import sys, glob, os, bisect
import verificar as V
sim = V.simbolos()
fun = sorted((a, n) for n, a in sim.items() if 0x80010000 <= a < 0x80070000 and not n.startswith(("jtbl_", "D_", ".L")))
dirs = [a for a, n in fun]
def nombre(pc):
    i = bisect.bisect_right(dirs, pc) - 1
    return f"{fun[i][1]}+{pc - fun[i][0]:x}" if i >= 0 else hex(pc)
for f in sys.argv[1:]:
    caps = sorted(glob.glob(os.path.join("capturas", f, "*.regs")))
    if not caps:
        print(f, "SIN_CAPTURAS"); continue
    r = V.ejecutar(caps[0][:-5], sim[f], None)
    e = r["error"] or "termina"
    if "pc " in e:
        pc = int(e.split("pc ")[1].rstrip(")"), 16)
        e = "gira en " + nombre(pc)
    print(f, e, flush=True)
PY
