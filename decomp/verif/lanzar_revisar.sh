#!/bin/bash
# 05-10: repite con el verificador nuevo (argumentos de la BIOS, GTE, cop0, ra reubicado) las 61 de build/revisar.txt
# (las contadas que llaman a la BIOS o usan cop2/mtc0; armada con verif/lista_revisar.py). 8 variantes.
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
export SABRINA_VARIANTES=8
r=$d/build/revisar_real.txt; s=$d/build/revisar_sint.txt
rm -f $r $s
while IFS=$'\t' read -r tipo par; do
  par=${par%$'\r'}
  if [ "$tipo" = real ]; then
    echo "== ${par##*:} ${par%%:*}" >> $r
    timeout 3600 bash $d/verif/vfull.sh ${par%%:*} ${par##*:} >> $r 2>&1 < /dev/null
  else
    echo "== ${par##*:} ${par%%:*}" >> $s
    timeout 3600 bash $d/verif/vsint.sh ${par%%:*} ${par##*:} >> $s 2>&1 < /dev/null
  fi
done < $d/build/revisar.txt
echo FIN >> $r; echo FIN >> $s
