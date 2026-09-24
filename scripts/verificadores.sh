#!/bin/bash
# Maneja los verificadores de Sabrina en WSL (mutantes.py y verificar.py). Lo usa vigilar_ram.sh.
#   pausar     congela (SIGSTOP) el mas nuevo que siga corriendo
#   reanudar   descongela (SIGCONT) el pausado mas viejo
#   detener    mata el mas nuevo (mutantes primero)
#   soltar     descongela todos
lista() { pgrep -f 'python3 (mutantes|verificar)\.py'; }
estado() { ps -o stat= -p "$1" 2>/dev/null | cut -c1; }
mostrar() { ps -o pid=,args= -p "$1" | cut -c1-110; }
case "$1" in
  pausar)   for p in $(lista | sort -rn); do [ "$(estado $p)" != T ] && mostrar $p && kill -STOP $p && break; done ;;
  reanudar) for p in $(lista | sort -n);  do [ "$(estado $p)" = T ] && mostrar $p && kill -CONT $p && break; done ;;
  detener)  p=$(pgrep -n -f 'python3 mutantes\.py') || p=$(pgrep -n -f 'python3 verificar\.py'); [ -n "$p" ] && mostrar $p && kill -CONT $p && kill $p ;;
  soltar)   for p in $(lista); do kill -CONT $p; done ;;
esac
exit 0
