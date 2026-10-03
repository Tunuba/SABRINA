# uso: vmano.sh log src:func ...  (verifica con capturas SINTETICAS, de a una, tope 15 min)
aqui=$(dirname "$(readlink -f "$0")")
cd /mnt/c/Proyectos/SABRINA/decomp
log=$1; shift
for par in "$@"; do
  src=${par%%:*}; f=${par##*:}
  echo "== $f $src" >> $log
  timeout ${TOPE:-900} bash $aqui/vsint.sh $src $f >> $log 2>&1
done
echo FIN >> $log
