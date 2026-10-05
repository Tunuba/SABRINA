#!/bin/bash
# 05-10: prueba de verificar_ra.py (reubicacion de ra/sp, GTE y cop0, espera de VSync) en las que lo necesitan
d=/mnt/c/Proyectos/SABRINA/decomp
s=$d/build/probar_ra.txt
echo "== inicio $(date)" > $s
export SABRINA_VARIANTES=8
for par in src/psyq/psyq_g01.c:func_800161D4 src/varios/tarjeta_dir_g14.c:func_800522E4 src/psyq/libetc_g13.c:func_800163E4; do
  echo "== ${par##*:}" >> $s
  timeout 3600 bash $d/verif/vfull_ra.sh ${par%%:*} ${par##*:} >> $s 2>&1
done
echo "FIN $(date)" >> $s
