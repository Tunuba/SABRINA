#!/bin/bash
# 05-10 noche: reverifica las funciones del dibujo del escenario con las capturas nuevas de scripts/capt_dibujo.py
# (las viejas eran del arranque y no llegaban a dibujar), y los mutantes de func_8001FD50. Espera a que termine
# verif/lanzar_0510b.sh para no correr dos colas a la vez (poca RAM). Lanzar por WMI. Log: build/cola_dibujo.txt
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/cola_dibujo.txt; rm -f $s
while ! grep -q "TODO FIN" $d/build/cola_0510b.txt 2>/dev/null; do sleep 60; done
for par in geometria/arbol.c:func_800204F0 geometria/triangulos_g13.c:func_80020294 \
           geometria/partir_80057F34.c:func_80057F34 geometria/partir_800582CC.c:func_800582CC \
           geometria/partir_8005865C.c:func_8005865C geometria/partir_800589EC.c:func_800589EC \
           geometria/partir_80058EE4.c:func_80058EE4 geometria/partir_800593E0.c:func_800593E0 \
           geometria/partir_800598DC.c:func_800598DC; do
  echo "== ${par##*:} src/${par%%:*}" >> $s
  timeout 5400 bash $d/verif/vfull.sh src/${par%%:*} ${par##*:} >> $s 2>&1 < /dev/null
done
source ~/decomp-herramientas/venv/bin/activate
export SABRINA_VARIANTES=8
echo "== mutantes func_8001FD50" >> $s
timeout 10800 python3 mutantes.py src/geometria/arbol.c func_8001FD50 --max 12 2>&1 < /dev/null | grep -E "VIVO|muertos|Error" >> $s
echo "TODO FIN $(date)" >> $s
