d=/mnt/c/Proyectos/SABRINA/decomp
rm -f $d/build/criticas.txt $d/build/criticas_sint.txt
bash $d/verif/cadena.sh $d/build/conservados.txt $d/verif/lanzar_criticas.sh $d/build/criticas.txt
