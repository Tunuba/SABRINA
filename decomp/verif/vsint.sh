#!/bin/bash
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate && python3 - "$@" <<'PY'
import sys, io, contextlib
import sint; V = sint.usar_sinteticas()
orig = V.comparar
oe = V.ejecutar
ult = {}
def ej(base, *a, **k):
    ult["args"] = (base.split("/")[-1], a[2:] if len(a) > 2 else None, k)
    return oe(base, *a, **k)
V.ejecutar = ej
malos = []
ejemplos = []
def comp(a, b, sp, con_v0=True):
    d = orig(a, b, sp, con_v0)
    if d:
        malos.append("; ".join(orig(a, b, sp, False)) or "; ".join(d))
        if len(ejemplos) < 4:
            base, extra, k = ult["args"]
            regs = extra[0] if extra and extra[0] else None
            par = extra[1] if extra and len(extra) > 1 else None
            ejemplos.append(f"{base} regs={' '.join('%x' % x for x in regs[4:8]) if regs else '-'} parche={dict((hex(0x80000000+kk), v.hex()) for kk, v in par.items()) if par else '-'}: {malos[-1]}")
    return d
V.comparar = comp
buf = io.StringIO()
with contextlib.redirect_stdout(buf):
    V.verificar(sys.argv[1], sys.argv[2:])
print(buf.getvalue().strip().split("\n")[-1])
from collections import Counter
for k, v in Counter(malos).most_common(8):
    print(v, k)
for e in ejemplos:
    print("  ej:", e)
PY
