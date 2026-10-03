# uso: vmano.sh log src:func ...  (verifica con capturas REALES, de a una, tope 15 min)
cd /mnt/c/Proyectos/SABRINA/decomp
aqui=$(dirname "$(readlink -f "$0")")
log=$1; shift
for par in "$@"; do
  src=${par%%:*}; f=${par##*:}
  echo "== $f $src" >> $log
  timeout ${TOPE:-900} bash $aqui/vfull.sh $src $f >> $log 2>&1
done
echo FIN >> $log
