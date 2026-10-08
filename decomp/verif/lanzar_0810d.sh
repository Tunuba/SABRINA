#!/bin/bash
# 08-10 noche: retoma lo que murio al reiniciarse WSL. Primero los cortes de BuclePrincipal que faltaban
# (log build/cola_corte2.txt), despues los mutantes del video (lanzar_0810c.sh, log build/cola_0810c.txt).
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/cola_corte2.txt; rm -f $s
source ~/decomp-herramientas/venv/bin/activate
export SABRINA_VARIANTES=4 SABRINA_LIMITE=300000000
for par in bucle_principal.c:BuclePrincipal:0x8004E268:1 bucle_principal.c:BuclePrincipal:0x8004B320:1 \
           bucle_principal.c:BuclePrincipal:0x80019D80:30; do
  IFS=: read -r f fn a n <<< "$par"
  echo "== $fn src/varios/$f (corte $a:$n)" >> $s
  SABRINA_CORTE=$a:$n timeout 10800 bash $d/verif/vfull.sh src/varios/$f $fn >> $s 2>&1 < /dev/null
done
echo "TODO FIN $(date)" >> $s
echo "TODO FIN" > $d/build/cola_0810b.txt.fin
bash $d/verif/lanzar_0810c.sh
