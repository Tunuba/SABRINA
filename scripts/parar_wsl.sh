#!/bin/bash
# Detiene todo lo de Sabrina que corre en WSL: el lote (auto.py), los verificadores y lo que dejaron los
# agentes (bucles de bash que relanzan verificadores, y procesos que quedaron pausados). Nada se pierde: el
# lote retoma con lanzar_lote.sh (--seguir) y el C ya escrito queda en decomp/src.
yo=$$
mios() { pgrep -f 'Sabrina decomp|Proyectos/SABRINA|tmp_g[0-9]|AppData/Local/Temp/claude|python3 (-u )?(auto|verificar|mutantes|cobertura)|python3 -u /' | grep -vx "$yo"; }
for ronda in 1 2 3; do
  for p in $(mios); do kill -CONT "$p" 2>/dev/null; kill -9 "$p" 2>/dev/null; done
  sleep 2
done
echo "quedan $(mios | wc -l) procesos de Sabrina"
