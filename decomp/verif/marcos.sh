#!/bin/bash
# uso: marcos.sh archivo.c f...  -> tamano del marco (addiu sp) de cada funcion: original y C
cd /mnt/c/Proyectos/SABRINA/decomp
src=$1; shift
mipsel-linux-gnu-gcc -c -O2 -march=r3000 -mabi=32 -mno-abicalls -fno-pic -G0 -fno-builtin -ffreestanding \
  -msoft-float -std=gnu89 -fcommon -Iinclude -o /tmp/marcos.o "$src"
for f in "$@"; do
  o=$(awk "/glabel $f\$/,/endlabel $f\$/" asm/*.s | grep -m1 -o 'addiu *\$sp, \$sp, -0x[0-9A-F]*' | grep -o '0x[0-9A-F]*')
  c=$(mipsel-linux-gnu-objdump -d /tmp/marcos.o | grep -A3 "<$f>:" | grep -m1 -o 'addiu.sp,sp,-[0-9]*' | grep -o '[0-9]*$')
  printf "%s original %s C 0x%x\n" "$f" "$o" "$c"
done
