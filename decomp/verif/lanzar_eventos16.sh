#!/bin/bash
# 05-10: las 14 de bios_eventos_g16.c (antes borradores de m2c que llamaban a la BIOS sin argumentos)
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/eventos16.txt; ss=$d/build/eventos16_sint.txt
rm -f $s $ss
export SABRINA_VARIANTES=8
T=src/varios/bios_eventos_g16.c
for f in func_80029808 func_80029858 func_8003E554 func_80051A84 func_80051C60 func_80051D14 func_80051E1C func_80051EF4; do
  echo "== $f $T" >> $s
  timeout 3600 bash $d/verif/vfull.sh $T $f >> $s 2>&1 < /dev/null
done
echo FIN >> $s
TOPE=3600 bash $d/verif/vmano.sh $ss $T:func_80014910 $T:func_80014988 $T:func_80016874 $T:func_80029830 $T:func_800515B0 $T:func_80052350 < /dev/null
source ~/decomp-herramientas/venv/bin/activate
for f in func_8003E554 func_80051A84 func_80051D14 func_80051E1C; do
  echo "== mutantes $f" >> $s
  timeout 5400 python3 mutantes.py $T $f --max 8 2>&1 | grep -E "VIVO|muertos" >> $s
done
for f in func_80014910 func_80016874 func_800515B0; do
  echo "== mutantes $f (sint)" >> $s
  timeout 5400 python3 sint.py mutantes $T $f --max 8 2>&1 | grep -E "VIVO|muertos" >> $s
done
echo "TODO FIN $(date)" >> $s
