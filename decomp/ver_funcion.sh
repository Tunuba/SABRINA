#!/bin/bash
# Muestra el ensamblador original de una o varias funciones (del asm de splat).
# Uso: bash ver_funcion.sh Nombre [Nombre...]
cd "$(dirname "$(readlink -f "$0")")"
for f in "$@"; do
  archivo=$(grep -rl "glabel $f\$" asm | head -1)
  awk -v f="$f" '$0 ~ ("glabel " f "$") {p=1} p {print} p && /endlabel/ {exit}' "$archivo"
  echo "----"
done
