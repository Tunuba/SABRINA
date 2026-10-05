#!/bin/bash
# 05-10: las tres que eran limite por guardar una direccion de vuelta (setjmp, InitGeom, InitCARD), con el
# verificador nuevo (ra/sp reubicados, GTE y cop0, argumentos de la BIOS), y sus mutantes
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/limites0510.txt
echo "== inicio $(date)" > $s
export SABRINA_VARIANTES=8
echo "== func_800163E4 src/psyq/libetc_g13.c" >> $s
timeout 3600 bash $d/verif/vfull.sh src/psyq/libetc_g13.c func_800163E4 >> $s 2>&1 < /dev/null
echo "== func_800177B4 src/psyq/parche_bios_g14.c" >> $s
timeout 3600 bash $d/verif/vfull.sh src/psyq/parche_bios_g14.c func_800177B4 >> $s 2>&1 < /dev/null
TOPE=3600 bash $d/verif/vmano.sh $d/build/limites0510_sint.txt src/varios/tarjeta_dir_g14.c:func_800522E4 < /dev/null
source ~/decomp-herramientas/venv/bin/activate
for p in src/psyq/libetc_g13.c:func_800163E4 src/psyq/parche_bios_g14.c:func_800177B4; do
  echo "== mutantes ${p##*:}" >> $s
  timeout 5400 python3 mutantes.py ${p%%:*} ${p##*:} --max 8 2>&1 | grep -E "VIVO|muertos" >> $s
done
echo "== mutantes func_800522E4 (sint)" >> $s
timeout 5400 python3 sint.py mutantes src/varios/tarjeta_dir_g14.c func_800522E4 --max 8 2>&1 | grep -E "VIVO|muertos" >> $s
echo "TODO FIN $(date)" >> $s
