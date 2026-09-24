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
# Ademas, como mucho una vez por hora, sube a GitHub (origin, rama main) lo que el .gitignore permite: el C, el
# avance, las notas y los scripts. Nunca el juego, lo extraido, las capturas ni los estados.
# Con SABRINA_SIN_GITHUB=1 no sube.
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
# --- copia afuera: GitHub, una vez por hora ---
unset GIT_DIR GIT_WORK_TREE
MARCA="$DESTINO/ultimo_push"
if [ -z "${SABRINA_SIN_GITHUB:-}" ] && [ "$(git -C "$RAIZ" branch --show-current)" = main ] &&    { [ ! -f "$MARCA" ] || [ $(( $(date +%s) - $(cat "$MARCA") )) -ge 3600 ]; }; then
  git -C "$RAIZ" add -A . 2>/dev/null
  if ! git -C "$RAIZ" diff --cached --quiet; then
    git -C "$RAIZ" -c user.name="José Manuel González Corado" -c user.email="161869532+Tunuba@users.noreply.github.com"       commit -q -m "Respaldo automatico $(date '+%Y-%m-%d %H:%M')"
  fi
  if timeout 300 git -C "$RAIZ" push -q origin main 2>>"$LOG"; then
    date +%s > "$MARCA"; echo "$(date '+%F %T') subido a GitHub: $(git -C "$RAIZ" log -1 --format='%h %s')" >> "$LOG"
  else
    echo "$(date '+%F %T') no se pudo subir a GitHub (sin red o sin credenciales); se reintenta en 15 min" >> "$LOG"
  fi
fi
export GIT_DIR="$DESTINO" GIT_WORK_TREE="$RAIZ"
if [ "${1:-}" = "--bundle" ] && [ -n "${2:-}" ]; then
  mkdir -p "$2" && git bundle create "$2/sabrina_respaldo.bundle" --all -q 2>/dev/null && \
    echo "$(date '+%F %T') bundle en $2/sabrina_respaldo.bundle" >> "$LOG"
fi
exit 0
