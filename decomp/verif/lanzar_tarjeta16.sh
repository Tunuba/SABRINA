#!/bin/bash
# 05-10: las 6 de la tarjeta reescritas con los argumentos de open/close/lseek/write (tarjeta_archivo_g16.c)
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/tarjeta16.txt
rm -f $s
export SABRINA_VARIANTES=8
T=src/varios/tarjeta_archivo_g16.c
TOPE=3600 bash $d/verif/vmano.sh $s $T:func_80050C40 $T:func_80050418 $T:func_80050554 $T:func_80050694 $T:func_80050AB8 $T:func_800513B4
source ~/decomp-herramientas/venv/bin/activate
for f in func_80050C40 func_80050418 func_80050554 func_80050694 func_80050AB8 func_800513B4; do
  echo "== mutantes $f" >> $s
  timeout 5400 python3 sint.py mutantes $T $f --max 8 2>&1 | grep -E "VIVO|muertos" >> $s
done
echo "TODO FIN $(date)" >> $s
