#!/bin/bash
# Instala en WSL las herramientas de descompilacion (todas libres):
#   splat (parte el ejecutable), m2c (MIPS a C), asm-differ (compara), maspsx (imita el ensamblador de Sony)
#   y compiladores GCC viejos para PS1 compilados por decompals/old-gcc.
# Uso, desde la carpeta del proyecto: wsl -d Ubuntu-24.04 -- bash scripts/decomp_instalar.sh
set -e
H="$HOME/decomp-herramientas"
mkdir -p "$H"
cd "$H"
if [ ! -d venv ]; then python3 -m venv venv; fi
. venv/bin/activate
pip install -q --upgrade pip
pip install -q "splat64[mips]" pycparser graphviz python-Levenshtein colorama ansiwrap watchdog cxxfilt 2>&1 | tail -2
for r in matt-kempster/m2c simonlindholm/asm-differ mkst/maspsx; do
  n=$(basename "$r")
  if [ ! -d "$n" ]; then git clone -q --depth 1 "https://github.com/$r.git"; fi
done
echo "herramientas en $H"
splat --version 2>/dev/null || python -m splat --version 2>/dev/null || echo "splat instalado (sin --version)"
ls
