#!/bin/bash
# 08-10: el video paso a IGUAL con una sola captura real (func_8005D50C 10 de 10, ReproducirSTR 22 de 22).
# Mutantes de las dos para ver que la comparacion caza errores. Espera el "TODO FIN" de build/cola_0810b.txt.
# Log: build/cola_0810c.txt
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/cola_0810c.txt; rm -f $s
until grep -q "TODO FIN" $d/build/cola_0810b.txt 2>/dev/null; do sleep 60; done
source ~/decomp-herramientas/venv/bin/activate
export SABRINA_LIMITE=300000000 SABRINA_VARIANTES=4
for par in Screen/video_reproductor_g14.c:func_8005D50C Screen/video_g13.c:ReproducirSTR; do
  echo "== mutantes ${par##*:}" >> $s
  timeout 21600 python3 mutantes.py src/${par%%:*} ${par##*:} --max 8 2>&1 < /dev/null | grep -E "VIVO|muertos|Error" >> $s
done
echo "TODO FIN $(date)" >> $s
