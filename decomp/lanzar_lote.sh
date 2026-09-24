#!/bin/bash
# Relanza el lote de auto.py retomando lo que ya hizo (build/hechas.txt).
# Se lanza desde Windows con Start-Process oculto: ese proceso sostiene la sesion de WSL
# durante todo el lote, porque la maquina virtual se apaga cuando no queda ninguna.
cd "$(dirname "$(readlink -f "$0")")" || exit 1
. ~/decomp-herramientas/venv/bin/activate
exec python3 auto.py --procesos "${1:-5}" --seguir >> build/auto_log2.txt 2>&1
