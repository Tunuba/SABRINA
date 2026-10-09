#!/bin/bash
# 05-10: tarjeta_archivo_g16.c con las capturas a mano de capturas_tarjeta16.sh y el verificador nuevo, y mutantes
# (en func_80050554/694 se muta abrir_y_pasar, la static que hace todo)
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/tarjeta16b.txt; rm -f $s
export SABRINA_VARIANTES=8
T=src/varios/tarjeta_archivo_g16.c
TOPE=3600 bash $d/verif/vmano.sh $s $T:func_80050418 $T:func_80050554 $T:func_80050694 $T:func_800513B4 $T:func_80050AB8 $T:func_80050C40 < /dev/null
source ~/decomp-herramientas/venv/bin/activate
for f in func_80050418 func_800513B4 func_80050AB8; do
  echo "== mutantes $f" >> $s
  timeout 5400 python3 sint.py mutantes $T $f --max 8 2>&1 | grep -E "VIVO|muertos|Error" >> $s
done
for f in func_80050554 func_80050694; do
  echo "== mutantes $f (abrir_y_pasar)" >> $s
  timeout 5400 python3 sint.py mutantes $T $f --max 8 --en abrir_y_pasar 2>&1 | grep -E "VIVO|muertos|Error" >> $s
done
echo "TODO FIN $(date)" >> $s
