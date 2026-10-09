#!/bin/bash
# 05-10: InitCARD (func_800522E4) con las llamadas de cola anotadas (GCC hace j func_800143F4; la original jal)
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/initcard.txt; rm -f $s
export SABRINA_VARIANTES=8
TOPE=3600 bash $d/verif/vmano.sh $s src/varios/tarjeta_dir_g14.c:func_800522E4 < /dev/null
source ~/decomp-herramientas/venv/bin/activate
echo "== mutantes func_800522E4" >> $s
timeout 5400 python3 sint.py mutantes src/varios/tarjeta_dir_g14.c func_800522E4 --max 8 2>&1 | grep -E "VIVO|muertos|Error" >> $s
echo "== mutantes func_800163E4" >> $s
timeout 5400 python3 mutantes.py src/psyq/libetc_g13.c func_800163E4 --max 8 2>&1 | grep -E "VIVO|muertos|Error" >> $s
echo "TODO FIN $(date)" >> $s
