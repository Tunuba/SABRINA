#!/bin/bash
# Deja la descompilacion lista en una PC nueva, en un paso (dentro de WSL, Ubuntu 24.04):
#   paquetes de apt (con espejo https si archive.ubuntu.com falla), venv con splat/m2c/unicorn, GCC viejos,
#   desensamblado con splat y el ejecutable rearmado y comparado (debe decir IGUAL).
# Uso, desde Windows:  wsl -d Ubuntu -- bash "/mnt/<disco>/<ruta>/SABRINA/scripts/decomp_todo.sh"
# Pide la contrasena de sudo una vez (para apt). Se puede correr las veces que quieras.
set -e
RAIZ="$(dirname "$(dirname "$(readlink -f "$0")")")"
PAQ="python3-venv python3-dev binutils-mipsel-linux-gnu gcc-mipsel-linux-gnu cpp-mipsel-linux-gnu build-essential git curl p7zip-full"
if ! command -v mipsel-linux-gnu-gcc >/dev/null; then
  if ! sudo apt-get update -qq; then
    echo "archive.ubuntu.com no responde bien: uso el espejo https de kernel.org"
    sudo sed -i 's#http://archive.ubuntu.com/ubuntu#https://mirrors.edge.kernel.org/ubuntu#; s#http://security.ubuntu.com/ubuntu#https://mirrors.edge.kernel.org/ubuntu#' /etc/apt/sources.list.d/ubuntu.sources
    sudo apt-get update -qq
  fi
  sudo DEBIAN_FRONTEND=noninteractive apt-get install -y -qq $PAQ
fi
bash "$RAIZ/scripts/decomp_instalar.sh"
. ~/decomp-herramientas/venv/bin/activate
pip install -q "unicorn==2.1.4" capstone pyyaml
bash "$RAIZ/scripts/decomp_compiladores.sh"
cd "$RAIZ/decomp"
[ -f SLUS_012.08 ] || cp "$RAIZ/extraido/SLUS_012.08" .
[ -d asm ] || python -m splat split slus_012.08.yaml
bash armar.sh | tail -1
echo "Listo. Faltan las capturas (se regeneran): desde Git Bash, bash scripts/rondas_paralelo.sh 4 12"
