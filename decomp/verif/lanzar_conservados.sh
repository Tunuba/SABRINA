# repaso de las funciones con stub en asm con los registros conservados comparados al volver (04-10 noche)
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
for par in src/File/archivo_entero_g14.c:func_800189A4 src/psyq/cd_stream_g14.c:func_8002D714 src/varios/animaciones_g07.c:CargarANI src/WobjCode/wrlddata_g14.c:CargarWRLDDATA src/objetos/crear_g13.c:CrearRecogible src/libgpu/fuente_g13.c:ImprimirDepuracion src/objetos/jefe_g13.c:func_8005ED8C src/Screen/pantallas_legales_g14.c:PantallasLegales; do
  echo "== ${par##*:} ${par%%:*}" >> $d/build/conservados.txt
  SABRINA_LIMITE=300000000 timeout 5400 bash $d/verif/vfull.sh ${par%%:*} ${par##*:} >> $d/build/conservados.txt 2>&1
done
TOPE=3600 bash $d/verif/vmano.sh $d/build/conservados_sint.txt src/varios/armar_cuadricula_g15.c:HerramientaArmarCuadricula src/varios/armar_modelos_g15.c:HerramientaArmarModelos src/varios/convertir_pic_g15.c:HerramientaConvertirPIC src/varios/convertir_tex_g15.c:HerramientaConvertirTEX src/varios/herramienta_tex_g14.c:func_80024450 src/varios/subir_textura_g15.c:func_8001A620 src/varios/tarjeta_iconos_g15.c:func_8004EBD0 src/varios/textura_fuente_g15.c:func_8001B9C0 src/varios/textura_sprite_g15.c:func_8001B698 src/varios/textura_tga_g15.c:func_8001B0C8
echo FIN >> $d/build/conservados.txt
