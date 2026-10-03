# repaso con mutantes de las IGUAL_SINT grandes (6 por funcion); arranca cuando termina lanzar_mut1.sh
while pgrep -f "^bash lanzar_mut1.sh" >/dev/null; do sleep 60; done
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
for p in src/psyq/mando_g13.c:func_80026820 src/objetos/agarrable_g13.c:func_80039350 src/objetos/tirador_g14.c:func_800552C0 src/auto/func_8001CB4C.c:func_8001CB4C src/libgpu/espacio_vram_g14.c:func_8001A228 src/objetos/rayo_g14.c:func_8003B894 src/objetos/lanzado_g14.c:func_8003C678 src/auto/func_80026ECC.c:func_80026ECC src/objetos/proyectil_g14.c:func_8005B52C src/objetos/agarrar_g14.c:func_80039104 src/objetos/fuente_g14.c:func_8005359C src/varios/sueltas_g13.c:func_8001951C src/varios/tarjeta_sector_g14.c:func_80052578 src/libgpu/drawenv_g14.c:func_80013714; do
  echo "== ${p##*:}"
  timeout 3600 python3 sint.py mutantes ${p%%:*} ${p##*:} --max 6 2>&1 | grep -E "VIVO|mutantes muertos"
done
echo FIN
