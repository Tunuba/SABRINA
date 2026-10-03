# mutantes de las grandes que pasaron a IGUAL el 02/03-10 (8 por funcion)
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
for par in src/objetos/entrar_nivel_g13.c:func_8004B320 src/objetos/activador_g13.c:func_80054068 src/Screen/sprites_g13.c:func_8002367C src/audio/vab_g13.c:func_800447E4 src/psyq/cdsync_g14.c:func_8002A6D0; do
  echo "== ${par##*:}"
  timeout 7200 python3 mutantes.py ${par%%:*} ${par##*:} --max 8 2>&1 | tail -3
done
echo FIN
