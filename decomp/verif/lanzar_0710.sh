#!/bin/bash
# 07-10: lo que quedo parado el 05-10 noche 2. Mutantes de los dos partidores que faltaban (func_80058EE4,
# func_800593E0) y despues la cola del dibujo (lanzar_dibujo.sh sin la espera de cola_0510b.txt).
# Lanzar por WMI (Invoke-CimMethod Win32_Process Create, wsl.exe -d Ubuntu-24.04 -- bash ...). Log: build/cola_0710.txt
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/cola_0710.txt; rm -f $s
source ~/decomp-herramientas/venv/bin/activate
export SABRINA_VARIANTES=8
for f in 80058EE4 800593E0; do
  echo "== mutantes func_$f" >> $s
  timeout 5400 python3 mutantes.py src/geometria/partir_$f.c func_$f --max 8 2>&1 < /dev/null | grep -E "VIVO|muertos|Error" >> $s
done
unset SABRINA_VARIANTES
for par in geometria/arbol.c:func_800204F0 geometria/triangulos_g13.c:func_80020294 \
           geometria/partir_80057F34.c:func_80057F34 geometria/partir_800582CC.c:func_800582CC \
           geometria/partir_8005865C.c:func_8005865C geometria/partir_800589EC.c:func_800589EC \
           geometria/partir_80058EE4.c:func_80058EE4 geometria/partir_800593E0.c:func_800593E0 \
           geometria/partir_800598DC.c:func_800598DC; do
  echo "== ${par##*:} src/${par%%:*}" >> $s
  timeout 5400 bash $d/verif/vfull.sh src/${par%%:*} ${par##*:} >> $s 2>&1 < /dev/null
done
export SABRINA_VARIANTES=8
echo "== mutantes func_8001FD50" >> $s
timeout 10800 python3 mutantes.py src/geometria/arbol.c func_8001FD50 --max 12 2>&1 < /dev/null | grep -E "VIVO|muertos|Error" >> $s
echo "TODO FIN $(date)" >> $s
