#!/bin/bash
# Borrador en C de una o varias funciones con m2c.
# Uso: bash m2c.sh Funcion [Funcion...]
cd "$(dirname "$(readlink -f "$0")")"
. "$HOME/decomp-herramientas/venv/bin/activate"
# m2c no acepta directivas en el contexto: se pasa el encabezado por el preprocesador
mipsel-linux-gnu-cpp -P -Iinclude include/juego.h > /tmp/contexto_m2c.h
for f in "$@"; do
  python3 "$HOME/decomp-herramientas/m2c/m2c.py" --target mips-gcc-c --context /tmp/contexto_m2c.h asm/800.s asm/data/51280.data.s -f "$f" 2>&1
  echo
done
