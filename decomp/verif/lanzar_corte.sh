#!/bin/bash
# 08-10: main y BuclePrincipal con el modo de corte (SABRINA_CORTE): las dos corren desde la captura real del
# arranque hasta la N-esima entrada a una funcion de la original y ahi se compara todo. Pocas variantes: no
# tienen argumentos. Log: build/cola_corte.txt
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/cola_corte.txt; rm -f $s
source ~/decomp-herramientas/venv/bin/activate
export SABRINA_VARIANTES=4 SABRINA_LIMITE=300000000
for par in arranque_g13.c:func_800106C8:0x80018050:1 bucle_principal.c:BuclePrincipal:0x80018050:1 \
           bucle_principal.c:BuclePrincipal:0x8004E268:1 bucle_principal.c:BuclePrincipal:0x8004B320:1 \
           bucle_principal.c:BuclePrincipal:0x80019D80:30; do
  IFS=: read -r f fn a n <<< "$par"
  echo "== $fn src/varios/$f (corte $a:$n)" >> $s
  SABRINA_CORTE=$a:$n timeout 10800 bash $d/verif/vfull.sh src/varios/$f $fn >> $s 2>&1 < /dev/null
done
echo "TODO FIN $(date)" >> $s
