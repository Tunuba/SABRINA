# uso: vsint3.sh archivo.c f...  -> vsint de cada funcion, de a una (SABRINA_VARIANTES se respeta)
for f in "${@:2}"; do timeout ${TOPE:-900} bash /mnt/c/Proyectos/SABRINA/decomp/verif/vsint.sh "$1" "$f" 2>&1 | tail -3; done
