cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
python3 verif/cascada_lote.py --max-por-funcion 2 > build/cascada_lote.txt 2>&1
echo FIN >> build/cascada_lote.txt
