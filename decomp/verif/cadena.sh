# uso: cadena.sh log1 script2 log2 [script3 log3 ...]  -> espera el FIN de log1 y lanza cada script cuando
# termina el anterior (de a una). Corre suelta con fondo.sh.
d=/mnt/c/Proyectos/SABRINA/decomp
espera=$1; shift
while [ $# -ge 2 ]; do
  until grep -q "^FIN" "$espera" 2>/dev/null; do sleep 30; done
  bash "$1" > /dev/null 2>&1
  espera=$2; shift 2
done
