#!/bin/bash
# Respaldo automatico de TODO lo que no va al repositorio publico y que costaria rehacer:
# el C escrito a mano (decomp/src), el avance (progreso.tsv, notas, reportes de cada fase), los estados del
# emulador y los scripts. Se guarda con historial en un repositorio git privado FUERA del disco D:
# (por defecto C:\Users\<usuario>\respaldo_sabrina.git) y, si se pide, un unico archivo .bundle para llevar a
# otra PC o a la nube.
#
#   bash scripts/respaldo.sh              respalda si hubo cambios (lo corre la tarea programada cada 15 min)
#   bash scripts/respaldo.sh --bundle D   ademas deja D/sabrina_respaldo.bundle (un solo archivo con todo)
#
# Restaurar en otra PC: ver notas/RESPALDO.md
#
# Las capturas (decomp/capturas, ~5 GB) NO van: se regeneran con scripts/rondas_paralelo.sh en ~30 min.
# El desensamblado (decomp/asm) tampoco: se regenera con splat en segundos.
set -u
RAIZ="$(cd "$(dirname "$0")/.." && pwd)"
DESTINO="${SABRINA_RESPALDO:-$HOME/respaldo_sabrina.git}"
export GIT_DIR="$DESTINO" GIT_WORK_TREE="$RAIZ"
LOG="$RAIZ/notas/logs/respaldo.txt"
mkdir -p "$RAIZ/notas/logs"
if [ ! -d "$DESTINO" ]; then
  env -u GIT_DIR -u GIT_WORK_TREE git init -q --bare "$DESTINO"
  git config core.bare false
  git config core.autocrlf false
  git config user.name "respaldo sabrina"; git config user.email "respaldo@local"
fi
# Que entra: todo lo propio. Que no: el juego, las herramientas, lo regenerable y lo pesado.
cat > "$DESTINO/info/exclude" <<'X'
/disco/
/extraido/
/herramientas/
/ghidra/
/prueba_disco/
/decomp/capturas/
/decomp/asm/
/decomp/build/
/decomp/SLUS_012.08
/decomp/*.ld
/decomp/undefined_*.txt
/notas/logs/*.log
/notas/capturas/
/notas/modelos/
/notas/sonidos/
/notas/videos/
/notas/pic/
/notas/tex/
__pycache__/
*.pyc
/mods/*.png
/disco_*/
X
cd "$RAIZ"
git add -A . 2>/dev/null
# el .gitignore del proyecto publico deja fuera lo privado: se fuerza lo que si hay que respaldar
for d in decomp/src estados notas/ghidra notas/fases mods; do [ -e "$d" ] && git add -f "$d" 2>/dev/null; done
if ! git diff --cached --quiet 2>/dev/null || ! git rev-parse -q --verify HEAD >/dev/null; then
  hechas=$(grep -rhoE '^\w[^;]*\b(func_[0-9A-F]{8}|[A-Z]\w+)\([^;]*$' "$RAIZ/decomp/src" --include=*.c --exclude-dir=auto 2>/dev/null | wc -l)
  git commit -q -m "respaldo $(date '+%Y-%m-%d %H:%M') ($hechas funciones a mano)" && \
    echo "$(date '+%F %T') respaldado: $(git log -1 --format=%s)" >> "$LOG"
fi
if [ "${1:-}" = "--bundle" ] && [ -n "${2:-}" ]; then
  mkdir -p "$2" && git bundle create "$2/sabrina_respaldo.bundle" --all -q 2>/dev/null && \
    echo "$(date '+%F %T') bundle en $2/sabrina_respaldo.bundle" >> "$LOG"
fi
exit 0
