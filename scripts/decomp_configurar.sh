#!/bin/bash
# Crea el proyecto de descompilacion en decomp/ con la configuracion inicial de splat.
set -e
RAIZ="$(dirname "$(dirname "$(readlink -f "$0")")")"
D="$RAIZ/decomp"
mkdir -p "$D"
cd "$D"
cp -n "$RAIZ/extraido/SLUS_012.08" "$D/SLUS_012.08"
. "$HOME/decomp-herramientas/venv/bin/activate"
if [ ! -f sabrina.yaml ] && [ ! -f slus_012.08.yaml ]; then
  python -m splat create_config SLUS_012.08
fi
ls
