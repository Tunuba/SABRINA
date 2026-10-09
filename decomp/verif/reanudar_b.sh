#!/bin/bash
# 05-10: mitad B de lanzar_reanudar0510.sh: mutantes que faltaron (mut5 y cuerpos de los stubs)
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/reanudar.txt
# lo que falto de lanzar_mut5.sh
source ~/decomp-herramientas/venv/bin/activate
echo "== mut5 resto $(date)" >> $s
for p in src/varios/herramienta_tex_g14.c:func_80024450 src/varios/armar_modelos_g15.c:HerramientaArmarModelos src/varios/armar_cuadricula_g15.c:HerramientaArmarCuadricula src/varios/convertir_pic_g15.c:HerramientaConvertirPIC; do
  echo "== ${p##*:}" >> $s
  timeout 5400 python3 sint.py mutantes ${p%%:*} ${p##*:} --max 8 2>&1 | grep -E "VIVO|muertos" >> $s
done

# lo que falto de lanzar_mut_cuerpos.sh (se agrega a build/mut_cuerpos.txt)
m=$d/build/mut_cuerpos.txt
echo "== reanudado $(date)" >> $m
for p in File/archivo_entero_g14.c:func_800189A4 varios/animaciones_g07.c:CargarANI WobjCode/wrlddata_g14.c:CargarWRLDDATA psyq/cd_stream_g14.c:func_8002D714; do
  echo "== ${p##*:} real" >> $m
  timeout 7200 python3 mutantes.py src/${p%%:*} ${p##*:} --max 8 >> $m 2>&1
done
for p in varios/subir_textura_g15.c:func_8001A620 varios/convertir_tex_g15.c:HerramientaConvertirTEX varios/herramienta_tex_g14.c:func_80024450 varios/tarjeta_iconos_g15.c:func_8004EBD0 varios/textura_sprite_g15.c:func_8001B698 varios/textura_tga_g15.c:func_8001B0C8 varios/textura_fuente_g15.c:func_8001B9C0 varios/armar_cuadricula_g15.c:HerramientaArmarCuadricula varios/convertir_pic_g15.c:HerramientaConvertirPIC varios/armar_modelos_g15.c:HerramientaArmarModelos; do
  echo "== ${p##*:} sint" >> $m
  timeout 7200 python3 sint.py mutantes src/${p%%:*} ${p##*:} --max 8 >> $m 2>&1
done
echo "FIN $(date)" >> $m
echo "COLA B FIN $(date)" >> $s
