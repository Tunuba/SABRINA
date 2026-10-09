#!/bin/bash
# 05-10 noche: func_80051764 reescrita (bios_eventos_g16.c, _card_load con el puerto y marco 0x18) y los tres partidores
# con stub del marco de la original (el tercer vector del GTE sale de la pila de la original). Verificacion y mutantes.
# Lanzar por WMI (Invoke-CimMethod Win32_Process Create, wsl.exe -d Ubuntu-24.04 -- bash ...). Log: build/cola_0510b.txt
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/cola_0510b.txt; rm -f $s
T=src/varios/bios_eventos_g16.c
echo "== func_80051764 $T" >> $s
timeout 3600 bash $d/verif/vsint.sh $T func_80051764 >> $s 2>&1 < /dev/null
for f in 800589EC 80058EE4 800593E0; do
  echo "== func_$f src/geometria/partir_$f.c" >> $s
  timeout 3600 bash $d/verif/vfull.sh src/geometria/partir_$f.c func_$f >> $s 2>&1 < /dev/null
done
source ~/decomp-herramientas/venv/bin/activate
export SABRINA_VARIANTES=8
echo "== mutantes func_80051764" >> $s
timeout 5400 python3 sint.py mutantes $T func_80051764 --max 8 2>&1 < /dev/null | grep -E "VIVO|muertos|Error" >> $s
for f in 800589EC 80058EE4 800593E0; do
  echo "== mutantes func_$f" >> $s
  timeout 5400 python3 mutantes.py src/geometria/partir_$f.c func_$f --max 8 2>&1 < /dev/null | grep -E "VIVO|muertos|Error" >> $s
done
echo "TODO FIN $(date)" >> $s
