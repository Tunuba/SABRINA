#!/bin/bash
# reverifica con la comparacion nueva de llamadas a la BIOS las funciones que llaman a un stub de la BIOS
# y las que cambiaron de static a extern (armado con C). Resultado en build/reverificar_bios.txt
cd "$(dirname "$(readlink -f "$0")")/.."
. ~/decomp-herramientas/venv/bin/activate 2>/dev/null
python3 - <<'PY' > build/reverificar_lista.txt
import json
d=set(json.load(open('build/llaman_bios.json')))
d|={"func_80010000","func_800259A8","func_80025EF8","func_80026D50","func_80027248","func_800272B0","func_80027368","func_80027AD0","func_80027D44","func_800283C4","func_800285FC","func_8002886C","func_80028D0C","func_80028D40","func_8002988C","func_8002A5F8","func_8003E554","func_80041F54","func_8001981C"}
fs={l.split('\t')[1]:l.split('\t')[2] for l in open('build/armado_c_completo.txt',encoding='utf-8') if l.startswith('OK')}
for f in sorted(d):
    if f in fs: print(f, fs[f])
PY
while read f arch; do
  echo "== $f $arch"
  SABRINA_VARIANTES=8 python3 verificar.py "$arch" "$f" 2>&1 | tail -3
done < build/reverificar_lista.txt
