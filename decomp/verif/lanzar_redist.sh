# repite con el verificador nuevo (MMIO, punteros a funcion, tope en variantes) las DISTINTO pendientes
cd /mnt/c/Proyectos/SABRINA/decomp/verif
TOPE=3000 bash vvarias.sh src/Screen/fondo_g13.c func_80023FD4
TOPE=3000 bash vvarias.sh src/sabrina/paso_g13.c func_80030208
for f in func_8003C678 func_8005B52C; do TOPE=1500 bash vvarias.sh --sint src/auto/$f.c $f; done
echo FIN
