#!/bin/bash
# Vuelve a verificar todo lo que usa las macros del GTE, para cuando se toca include/gte.h o gte.py.
cd "$(dirname "$(readlink -f "$0")")" || exit 1
. ~/decomp-herramientas/venv/bin/activate
python3 verificar.py src/geometria/vectores.c func_8001C404 2>&1 | tail -2
python3 verificar.py src/geometria/camara.c func_8001FA3C 2>&1 | tail -2
python3 verificar.py src/objetos/particulas.c func_8001F6C8 2>&1 | tail -2
python3 verificar.py src/geometria/arbol.c func_8001FD50 func_800204F0 func_80024A48 2>&1 | tail -8
