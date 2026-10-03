#!/bin/bash
# uso: termina.sh func ...  -> corre la ORIGINAL en su primera captura y dice si termina (antes de escribirla)
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
for f in "$@"; do
  r=$(timeout 300 python3 - "$f" <<'PY'
import sys, glob, os
import verificar as V
f = sys.argv[1]
caps = sorted(glob.glob(os.path.join(os.environ.get("CAPTURAS", "capturas"), f, "*.regs")))
if not caps:
    print("SIN_CAPTURAS"); sys.exit()
r = V.ejecutar(caps[0][:-5], V.simbolos()[f], None)
print("NO_TERMINA" if r["error"] and "no termino" in r["error"] else ("ERROR " + str(r["error"]) if r["error"] else "termina"))
PY
)
  echo "$f $r"
done
