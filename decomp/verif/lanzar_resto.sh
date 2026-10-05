# lo que falta de las herramientas, de a una, con los archivos virtuales de cada corrida (04-10 noche)
d=/mnt/c/Proyectos/SABRINA/decomp
for n in tga5 modelos; do rm -f $d/build/$n.txt; bash $d/verif/lanzar_$n.sh; done
