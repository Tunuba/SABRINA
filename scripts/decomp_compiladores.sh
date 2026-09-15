#!/bin/bash
# Baja los GCC para PS1 de decompals/old-gcc (release 0.17) a ~/decomp-herramientas/gcc/<version>/
set -e
G="$HOME/decomp-herramientas/gcc"
mkdir -p "$G"
cd "$G"
for v in 2.6.3 2.7.2 2.8.0 2.8.1 2.91.66 2.95.2; do
  if [ ! -d "$v" ]; then
    mkdir -p "$v"
    curl -sL "https://github.com/decompals/old-gcc/releases/download/0.17/gcc-$v-psx.tar.gz" | tar xz -C "$v"
  fi
  echo "$v: $(ls "$v" | tr '\n' ' ')"
done
