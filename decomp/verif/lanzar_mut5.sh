# lo que falto de lanzar_mut4.sh (se paro para ahorrar bateria el 04-10 noche), ya con los registros conservados
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
for p in src/varios/tarjeta_bios_g15.c:func_800521AC src/varios/tarjeta_bios_g15.c:func_80052240 src/varios/tarjeta_bios_g15.c:func_800523B4 src/varios/herramienta_tex_g14.c:func_80024450 src/varios/armar_modelos_g15.c:HerramientaArmarModelos src/varios/armar_cuadricula_g15.c:HerramientaArmarCuadricula src/varios/convertir_pic_g15.c:HerramientaConvertirPIC; do
  echo "== ${p##*:}"
  timeout 5400 python3 sint.py mutantes ${p%%:*} ${p##*:} --max 8 2>&1 | grep -E "VIVO|muertos"
done
echo FIN
