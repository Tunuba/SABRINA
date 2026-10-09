#!/bin/bash
# mutantes.py con verificar_ra.py en lugar de verificar.py (prueba de la reubicacion de direcciones de vuelta, 05-10)
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
python3 -c "
import sys, runpy, verificar_ra
sys.modules['verificar'] = verificar_ra
sys.argv = ['mutantes.py'] + sys.argv[1:]
runpy.run_path('mutantes.py', run_name='__main__')
" "$@"
