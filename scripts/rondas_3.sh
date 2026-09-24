#!/bin/bash
# Espera a que termine la ronda 2, corre la ronda 3 con mas emuladores y despues el lote de auto.py.
# Uso: bash scripts/rondas_3.sh [emuladores] [procesos_lote]
cd "$(dirname "$0")"
L=../notas/logs
K=${1:-8}; P=${2:-12}
while tasklist | grep -qi "pcsx-redux.main"; do sleep 10; done
echo "== ronda 2 lista"; tail -qn 1 $L/ronda2_*.txt
echo "== ronda 3 (niveles de la ronda 1 y HUB, recorrido nuevo), $K emuladores"
for ((i=0;i<K;i++)); do python capturar_mas.py 3 3,4,7,10,13,14 --parte $i/$K --puerto $((8091+i)) > $L/ronda3_$i.txt 2>&1 & done; wait
tail -qn 1 $L/ronda3_*.txt
echo "== lote auto.py con $P procesos"
wsl -d Ubuntu -- bash -lc "cd '/mnt/d/proyectos personales/Sabrina decomp/SABRINA/decomp' && . ~/decomp-herramientas/venv/bin/activate && python3 auto.py --procesos $P > build/auto_log.txt 2>&1; tail -n 5 build/auto_log.txt"
echo "== FIN"
