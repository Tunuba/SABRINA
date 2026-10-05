# mutantes de las IGUAL_SINT nuevas del 04-10 noche (8 por funcion, de a una)
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
for p in src/varios/tarjeta_leer_g15.c:func_800502DC src/varios/armar_cuadricula_g15.c:HerramientaArmarCuadricula src/varios/convertir_pic_g15.c:HerramientaConvertirPIC src/varios/fuente_a_pc_g15.c:func_80018CB8 src/varios/tarjeta_bios_g15.c:func_800521AC src/varios/tarjeta_bios_g15.c:func_80052240 src/varios/tarjeta_bios_g15.c:func_800523B4 src/varios/herramienta_tex_g14.c:func_80024450 src/varios/armar_modelos_g15.c:HerramientaArmarModelos; do
  echo "== ${p##*:}"
  timeout 5400 python3 sint.py mutantes ${p%%:*} ${p##*:} --max 8 2>&1 | grep -E "VIVO|muertos"
done
echo FIN
