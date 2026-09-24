#!/bin/bash
# Rondas de capturas con varios emuladores a la vez (sin sonido, sin ventana) y despues el lote de auto.py.
# Uso (desde Git Bash): bash scripts/rondas_paralelo.sh [emuladores] [procesos_lote]
# Ronda 1: primeras llamadas en HUB y niveles 3,4,7,10,14. Ronda 2: el resto de los niveles. Ronda 3: vuelve a
# los de la ronda 1 con el recorrido de capturar_mas (chocar, caer, menus). Cada emulador acepta ~896 puntos de
# interrupcion, por eso las funciones se reparten con --parte.
cd "$(dirname "$0")"
L=../notas/logs
K=${1:-8}; P=${2:-12}
echo "== ronda 1 (completar), 2 emuladores"
for i in 0 1; do python capturar_todo.py 3 saltar --parte $i/2 --puerto $((8091+i)) > $L/ronda1_$i.txt 2>&1 & done; wait
tail -n 2 $L/ronda1_*.txt
echo "== ronda 2 (niveles nuevos), $K emuladores"
for ((i=0;i<K;i++)); do python capturar_mas.py 3 0,1,2,5,6,8,9,11,12 --parte $i/$K --puerto $((8091+i)) > $L/ronda2_$i.txt 2>&1 & done; wait
tail -n 1 $L/ronda2_*.txt
echo "== ronda 3 (niveles de la ronda 1 y HUB, recorrido nuevo), $K emuladores"
for ((i=0;i<K;i++)); do python capturar_mas.py 3 3,4,7,10,13,14 --parte $i/$K --puerto $((8091+i)) > $L/ronda3_$i.txt 2>&1 & done; wait
tail -n 1 $L/ronda3_*.txt
DW="$(cd ../decomp && pwd -W | sed -E 's#^([A-Za-z]):#/mnt/\L\1#')"   # la ruta vista desde WSL
echo "== lote auto.py con $P procesos"
wsl -d Ubuntu -- bash -lc "cd \"$DW\" && . ~/decomp-herramientas/venv/bin/activate && python3 auto.py --procesos $P > build/auto_log.txt 2>&1; tail -n 5 build/auto_log.txt"
echo "== FIN"
