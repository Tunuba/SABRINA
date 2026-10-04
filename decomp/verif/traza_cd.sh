#!/bin/bash
# uso: traza_cd.sh func [n]  -> corre la ORIGINAL en su captura n y muestra donde queda y lo que hablo con el CD
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
f = sys.argv[1]
n = int(sys.argv[2]) if len(sys.argv) > 2 else 0
caps = sorted(glob.glob(os.path.join("capturas", f, "*.regs")))
r = V.ejecutar(caps[n][:-5], sim[f], None, cuenta=3_000_000)
e = r["error"] or "termina"
if "pc " in e:
    e = "gira en " + nombre(int(e.split("pc ")[1].rstrip(")"), 16))
print(f, e)
cdw = [(d, v) for d, t, v in r["hw"] if 0x1F801800 <= d < 0x1F801804 or d in (0x1F8010B8,)]
print(len(r["hw"]), "escrituras de hw,", len(cdw), "al CD; primeras:")
print(" ".join(f"{d & 0xFFF:x}={v:x}" for d, v in cdw[:60]))
print("ultimas:", " ".join(f"{d & 0xFFF:x}={v:x}" for d, v in cdw[-30:]))
print("CD:", " ".join(r["cd"][:150]))
print("CD fin:", " ".join(r["cd"][-40:]))
PY
