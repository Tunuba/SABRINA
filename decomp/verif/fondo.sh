# uso: fondo.sh script salida  -> lo deja corriendo suelto (sin terminal) y espera a que arranque
setsid nohup bash "$1" > "$2" 2>&1 < /dev/null &
sleep 3
pgrep -f "$1" > /dev/null && echo "arranco: $1" || echo "NO arranco: $1"
