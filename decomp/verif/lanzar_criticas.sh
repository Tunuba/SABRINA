# repaso de las que llaman a Enter/ExitCriticalSection con la comparacion nueva de secciones criticas (04-10 noche)
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
export SABRINA_VARIANTES=8
for par in src/psyq/parche_bios_g14.c:func_80017BC0 src/auto/func_8002D170.c:func_8002D170 src/audio/tempo_g13.c:func_80041CD8 src/auto/func_80051A84.c:func_80051A84 src/auto/func_80051C60.c:func_80051C60; do
  echo "== ${par##*:} ${par%%:*}" >> $d/build/criticas.txt
  timeout 3600 bash $d/verif/vfull.sh ${par%%:*} ${par##*:} >> $d/build/criticas.txt 2>&1
done
TOPE=3600 bash $d/verif/vmano.sh $d/build/criticas_sint.txt src/auto/func_80014910.c:func_80014910 src/auto/func_80014988.c:func_80014988 src/auto/func_800167D4.c:func_800167D4 src/auto/func_80016874.c:func_80016874 src/varios/tarjeta_bios_g15.c:func_800521AC src/varios/tarjeta_bios_g15.c:func_80052240 src/auto/func_80052350.c:func_80052350 src/varios/tarjeta_bios_g15.c:func_800523B4
echo FIN >> $d/build/criticas.txt
