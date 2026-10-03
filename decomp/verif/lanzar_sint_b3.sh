# espera a que termine el lote b2 y lanza el b3 (limites amplios, solo las que faltan)
while pgrep -f "^bash lanzar_sint_b2.sh" >/dev/null; do sleep 60; done
bash /mnt/c/Proyectos/SABRINA/decomp/verif/sint_lote2.sh build/sint_lote_b3.txt --tope 0x2000 --llamadas 40 --globales 80 --gte
