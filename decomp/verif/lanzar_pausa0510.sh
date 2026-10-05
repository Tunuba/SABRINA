#!/bin/bash
# cola que quedo de la PAUSA 05-10, de a una: PantallasLegales, criticas, mutantes
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
echo "== PantallasLegales $(date)" > $d/build/pausa_pl.txt
SABRINA_VARIANTES=8 SABRINA_LIMITE=300000000 timeout 14400 bash $d/verif/vfull.sh src/Screen/pantallas_legales_g14.c PantallasLegales >> $d/build/pausa_pl.txt 2>&1
echo "FIN $(date)" >> $d/build/pausa_pl.txt
rm -f $d/build/criticas.txt $d/build/criticas_sint.txt
bash $d/verif/lanzar_criticas.sh
bash $d/verif/lanzar_mut5_log.sh
echo "COLA FIN $(date)" >> $d/build/pausa_pl.txt
