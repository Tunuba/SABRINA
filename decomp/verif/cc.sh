#!/bin/bash
# uso: cc.sh archivo.c ...  -> compila cada uno como verificar.py (solo para ver errores)
cd /mnt/c/Proyectos/SABRINA/decomp
for f in "$@"; do
  mipsel-linux-gnu-gcc -c -O2 -march=r3000 -mabi=32 -mno-abicalls -fno-pic -G0 -fno-builtin -ffreestanding \
    -msoft-float -std=gnu89 -fcommon -Iinclude -o /tmp/cc.o "$f" 2>&1 | grep -E "error|implicit" && echo "MAL $f" || echo "ok $f"
done
