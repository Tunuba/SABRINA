# tandas de las herramientas de la PC de desarrollo, de a una (las de texturas se cortaron al actualizar la PC
# el 04-10; las corridas ahora son mucho mas cortas con los sectores vacios despues de los archivos virtuales)
d=/mnt/c/Proyectos/SABRINA/decomp
for n in tga1 tga2 tga4 tga5 pic modelos; do rm -f $d/build/$n.txt; bash $d/verif/lanzar_$n.sh; done
