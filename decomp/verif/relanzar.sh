# uso: relanzar.sh lanzar_X.sh salida  -> espera a que termine la corrida anterior de ese script y lo lanza suelto
cd /mnt/c/Proyectos/SABRINA/decomp/verif
for i in $(seq 1 60); do pgrep -f "^bash $1" >/dev/null || break; sleep 3; done
pgrep -f "^bash $1" >/dev/null && echo "sigue corriendo: $1" || bash fondo.sh "$1" "$2"
