#!/bin/bash
# Compila ejemplos de psyqo (Nugget) con el compilador MIPS de Ubuntu en WSL.
# Uso: wsl -d Ubuntu-24.04 -- bash /mnt/c/Proyectos/SABRINA/scripts/compilar_ejemplos.sh hello padtest
# El compilador de Debian/Ubuntu se llama mipsel-linux-gnu y su enlazador nombra el formato
# elf32-tradlittlemips, no elf32-littlemips como espera Nugget por defecto.
EJ=/mnt/c/Proyectos/SABRINA/herramientas/nugget/psyqo/examples
for e in "$@"; do
  cd "$EJ/$e" || exit 1
  make -j12 PREFIX=mipsel-linux-gnu FORMAT=elf32-tradlittlemips > "/tmp/ej_$e.log" 2>&1
  c=$?
  echo "$e codigo $c"
  [ $c -ne 0 ] && tail -5 "/tmp/ej_$e.log"
  ls -la *.ps-exe 2>/dev/null
done
