# uso: vvarias.sh [--sint] src func ...  -> verifica varias funciones de un mismo .c, de a una (tope $TOPE o 25 min)
cd /mnt/c/Proyectos/SABRINA/decomp
aqui=$(dirname "$(readlink -f "$0")")
v=vfull.sh; [ "$1" = "--sint" ] && { v=vsint.sh; shift; }
src=$1; shift
for f in "$@"; do
  echo "== $f $src"
  timeout ${TOPE:-1500} bash $aqui/$v $src $f
done
