#!/bin/bash
# mutantes en el CUERPO en C de las funciones con stub de asm (05-10): antes se mutaba solo el stub
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d && source ~/decomp-herramientas/venv/bin/activate
s=$d/build/mut_cuerpos.txt
echo "== inicio $(date)" >> $s
for p in File/archivo_entero_g14.c:func_80017D80 File/archivo_entero_g14.c:func_800189A4 varios/animaciones_g07.c:CargarANI WobjCode/wrlddata_g14.c:CargarWRLDDATA psyq/cd_stream_g14.c:func_8002D714; do
  echo "== ${p##*:} real" >> $s
  timeout 7200 python3 mutantes.py src/${p%%:*} ${p##*:} --max 8 >> $s 2>&1
done
for p in varios/subir_textura_g15.c:func_8001A620 varios/convertir_tex_g15.c:HerramientaConvertirTEX varios/herramienta_tex_g14.c:func_80024450 varios/tarjeta_iconos_g15.c:func_8004EBD0 varios/textura_sprite_g15.c:func_8001B698 varios/textura_tga_g15.c:func_8001B0C8 varios/textura_fuente_g15.c:func_8001B9C0 varios/armar_cuadricula_g15.c:HerramientaArmarCuadricula varios/convertir_pic_g15.c:HerramientaConvertirPIC varios/armar_modelos_g15.c:HerramientaArmarModelos; do
  echo "== ${p##*:} sint" >> $s
  timeout 7200 python3 sint.py mutantes src/${p%%:*} ${p##*:} --max 8 >> $s 2>&1
done
echo "FIN $(date)" >> $s
