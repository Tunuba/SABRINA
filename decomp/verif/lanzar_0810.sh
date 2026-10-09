#!/bin/bash
# 08-10: paso 1 del traspaso 07-10 (el video con la captura real, ahora que modelo_cd.py salta el audio XA) y
# despues lanzar_0710.sh sin los mutantes de func_80058EE4 (ya dieron 5 de 8, los vivos son de cobertura).
# Lanzar por WMI (Invoke-CimMethod Win32_Process Create, wsl.exe -d Ubuntu-24.04 -- bash ...). Log: build/cola_0810.txt
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/cola_0810.txt; rm -f $s
source ~/decomp-herramientas/venv/bin/activate
export SABRINA_LIMITE=300000000
for par in Screen/video_reproductor_g14.c:func_8005D50C Screen/video_g13.c:ReproducirSTR; do
  echo "== ${par##*:} src/${par%%:*}" >> $s
  timeout 14400 bash $d/verif/vfull.sh src/${par%%:*} ${par##*:} >> $s 2>&1 < /dev/null
done
unset SABRINA_LIMITE
export SABRINA_VARIANTES=8
echo "== mutantes func_800593E0" >> $s
timeout 5400 python3 mutantes.py src/geometria/partir_800593E0.c func_800593E0 --max 8 2>&1 < /dev/null | grep -E "VIVO|muertos|Error" >> $s
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
