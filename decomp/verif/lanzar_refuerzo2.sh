# segunda tanda del repaso de sinteticas debiles, y la herramienta INO entera con tope alto
d=/mnt/c/Proyectos/SABRINA/decomp
TOPE=3600 bash $d/verif/vmano.sh $d/build/refuerzo2.txt src/auto/func_800538A0.c:func_800538A0 src/auto/func_8003980C.c:func_8003980C
SABRINA_LIMITE=400000000 TOPE=7200 bash $d/verif/vmano.sh $d/build/ino.txt src/varios/armar_ino_g15.c:func_800185A8
