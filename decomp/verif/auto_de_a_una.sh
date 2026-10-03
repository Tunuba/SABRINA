# uso: auto_de_a_una.sh f1 f2 ...  -> auto.py --solo de a una funcion (m2c + verificar con capturas reales -> progreso.tsv)
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
for f in "$@"; do
  timeout ${TOPE:-1500} python3 auto.py --solo $f --procesos 1 2>&1 | tail -2
  grep -P "^$f\t" progreso.tsv | cut -c1-200
done
