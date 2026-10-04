#!/bin/bash
# uso: perfil.sh func [n]  -> cuanto tarda la ORIGINAL en su captura n y en que se va el tiempo (cProfile)
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
python3 - "$@" <<'PY'
import sys, glob, os, time, cProfile, pstats
import verificar as V
f = sys.argv[1]; n = int(sys.argv[2]) if len(sys.argv) > 2 else 0
caps = sorted(glob.glob(os.path.join("capturas", f, "*.regs")))
V.simbolos()
t = time.time()
pr = cProfile.Profile(); pr.enable()
r = V.ejecutar(caps[n][:-5], V.simbolos()[f], None)
pr.disable()
print(f, "error:", r["error"], "%.1f s" % (time.time() - t), "cd:", len(r["cd"]), "hw:", len(r["hw"]))
pstats.Stats(pr).sort_stats("tottime").print_stats(12)
PY
