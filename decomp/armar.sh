#!/bin/bash
# Arma SLUS_012.08 desde asm/ (y src/ cuando haya C) y lo compara con el original.
# Uso: wsl -d Ubuntu -- bash decomp/armar.sh
set -e
cd "$(dirname "$(readlink -f "$0")")"
AS="mipsel-linux-gnu-as"
LD="mipsel-linux-gnu-ld"
OC="mipsel-linux-gnu-objcopy"
ASFLAGS="-EL -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0"
mkdir -p build
for s in $(find asm -name '*.s' -not -path '*/nonmatchings/*'); do
  o="build/${s%.s}.o"
  mkdir -p "$(dirname "$o")"
  if [ ! -f "$o" ] || [ "$s" -nt "$o" ]; then
    $AS $ASFLAGS -o "$o" "$s"
  fi
done
# El C todavia solo se verifica (verificar.py); el ejecutable sale del ensamblador. compilar_c.sh sera el
# paso del "armado movible" (TRASPASO.md, Siguiente 3): mientras no exista, el C no entra al armado.
[ -f compilar_c.sh ] && for c in $(find src -name '*.c' -not -path '*/auto/*' 2>/dev/null); do
  o="build/${c%.c}.c.o"
  mkdir -p "$(dirname "$o")"
  bash compilar_c.sh "$c" "$o"
done
$LD -EL -T undefined_syms_auto.txt -T undefined_funcs_auto.txt -T slus_012.08.ld \
    -Map build/slus_012.08.map --no-check-sections -nostdlib -o build/slus_012.08.elf
$OC -O binary build/slus_012.08.elf build/SLUS_012.08
a=$(sha1sum build/SLUS_012.08 | cut -d' ' -f1)
b=$(sha1sum SLUS_012.08 | cut -d' ' -f1)
echo "armado  $a $(stat -c%s build/SLUS_012.08) bytes"
echo "original $b $(stat -c%s SLUS_012.08) bytes"
if [ "$a" = "$b" ]; then echo "IGUAL"; else echo "DISTINTO"; cmp -l build/SLUS_012.08 SLUS_012.08 | head -5; fi
