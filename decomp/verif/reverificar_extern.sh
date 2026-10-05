#!/bin/bash
# reverifica las funciones cuyos borradores tenian un static de dato del juego, ya cambiado a extern (armado con C)
cd "$(dirname "$(readlink -f "$0")")/.."
. ~/decomp-herramientas/venv/bin/activate 2>/dev/null
for f in func_80010000 func_800259A8 func_80025EF8 func_80026D50 func_80027248 func_800272B0 func_80027368 func_80027AD0 func_80027D44 func_800283C4 func_800285FC func_8002886C func_80028D0C func_80028D40 func_8002988C func_8002A5F8 func_8003E554 func_80041F54 func_8001981C; do
  echo "== $f"
  SABRINA_VARIANTES=8 python3 verificar.py src/auto/$f.c $f 2>&1 | tail -2
done
