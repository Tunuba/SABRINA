#!/bin/bash
# 05-10: mitad A de lanzar_reanudar0510.sh (la cola se partio en dos con mas RAM libre): reverificacion con la BIOS
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/reanudar.txt
# lo que falto de lanzar_bios.sh (se agrega a build/bios.txt)
echo "== bios reales $(date)" >> $s
export SABRINA_VARIANTES=8
for par in src/psyq/psyq_g01.c:func_800161D4 src/auto/func_800164BC.c:func_800164BC src/psyq/libetc_g13.c:func_8001668C src/psyq/parche_bios_g14.c:func_80017BC0 src/auto/func_80029808.c:func_80029808 src/auto/func_80029858.c:func_80029858 src/auto/func_8003E554.c:func_8003E554 src/auto/func_8004FD34.c:func_8004FD34 src/auto/func_80050034.c:func_80050034 src/varios/tarjeta_dir_g14.c:func_80051024 src/auto/func_80051A84.c:func_80051A84 src/auto/func_80051C60.c:func_80051C60 src/auto/func_80051D14.c:func_80051D14 src/auto/func_80051E1C.c:func_80051E1C src/auto/func_80051EF4.c:func_80051EF4 ; do
  echo "== ${par##*:} ${par%%:*}" >> $d/build/bios.txt
  timeout 3600 bash $d/verif/vfull.sh ${par%%:*} ${par##*:} >> $d/build/bios.txt 2>&1
done
echo FIN >> $d/build/bios.txt
echo "== bios sinteticas $(date)" >> $s
rm -f $d/build/bios_sint.txt
TOPE=3600 bash $d/verif/vmano.sh $d/build/bios_sint.txt src/auto/func_80014910.c:func_80014910 src/auto/func_80014988.c:func_80014988 src/auto/func_800167D4.c:func_800167D4 src/auto/func_80016874.c:func_80016874 src/auto/func_80017CBC.c:func_80017CBC src/auto/func_80017CE4.c:func_80017CE4 src/auto/func_80029830.c:func_80029830 src/auto/func_8004FD04.c:func_8004FD04 src/varios/tarjeta_leer_g15.c:func_800502DC src/auto/func_80050418.c:func_80050418 src/auto/func_80050554.c:func_80050554 src/auto/func_80050694.c:func_80050694 src/auto/func_80050AB8.c:func_80050AB8 src/auto/func_80050C40.c:func_80050C40 src/auto/func_800513B4.c:func_800513B4 src/auto/func_800515B0.c:func_800515B0 src/auto/func_80051764.c:func_80051764 src/auto/func_80051820.c:func_80051820 src/varios/tarjeta_bios_g15.c:func_800521AC src/varios/tarjeta_bios_g15.c:func_80052240 src/auto/func_80052350.c:func_80052350 src/varios/tarjeta_bios_g15.c:func_800523B4 src/varios/tarjeta_sector_g14.c:func_80052434
unset SABRINA_VARIANTES
echo "COLA A FIN $(date)" >> $s
