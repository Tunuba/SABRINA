#!/bin/bash
# Red de seguridad para que la PC no se sature. Solo detiene procesos DE SABRINA, nunca otros:
#   RAM de Windows > TOPE_RAM (92 %)              -> detiene el verificador mas nuevo de WSL
#   CPU total > TOPE_CPU (95 %) 3 lecturas seguidas -> PAUSA (SIGSTOP) el verificador mas nuevo que siga
#                                                    corriendo; con la CPU < 85 % 2 lecturas seguidas reanuda
#                                                    (SIGCONT) el pausado mas viejo. Asi no se pierde trabajo.
# El verificador que se detiene es mutantes.py primero, despues verificar.py (los agentes reintentan solos).
# Uso: bash scripts/vigilar_ram.sh [tope_ram] [tope_cpu]
export MSYS_NO_PATHCONV=1   # que Git Bash no convierta las rutas /mnt/d de WSL
TOPE=${1:-92}
TOPE_CPU=${2:-95}
LOG="$(dirname "$0")/../notas/logs/vigilar_ram.txt"
altas=0; bajas=0
# si el vigilante se cierra, que no quede nada congelado
trap 'wsl -d Ubuntu -- bash "/mnt/d/proyectos personales/Sabrina decomp/SABRINA/scripts/verificadores.sh" soltar; exit' EXIT INT TERM
detener() {
  v=$(wsl -d Ubuntu -- bash "/mnt/d/proyectos personales/Sabrina decomp/SABRINA/scripts/verificadores.sh" detener)
  echo "$(date +%T) $1: detenido ${v:-nada (no habia verificadores de Sabrina corriendo)}" | tee -a "$LOG"
}
pausar() {
  v=$(wsl -d Ubuntu -- bash "/mnt/d/proyectos personales/Sabrina decomp/SABRINA/scripts/verificadores.sh" pausar)
  echo "$(date +%T) $1: pausado ${v:-nada (no habia verificadores de Sabrina corriendo)}" | tee -a "$LOG"
}
reanudar() {
  v=$(wsl -d Ubuntu -- bash "/mnt/d/proyectos personales/Sabrina decomp/SABRINA/scripts/verificadores.sh" reanudar)
  [ -n "$v" ] && echo "$(date +%T) CPU ${1}%: reanudado $v" | tee -a "$LOG"
}
while true; do
  read -r p c < <(powershell.exe -NoProfile -Command '$o=Get-CimInstance Win32_OperatingSystem; $c=(Get-CimInstance Win32_PerfFormattedData_PerfOS_Processor | Where-Object Name -eq _Total).PercentProcessorTime; "{0} {1}" -f [int](100*($o.TotalVisibleMemorySize-$o.FreePhysicalMemory)/$o.TotalVisibleMemorySize), $c' | tr -d '\r')
  if [ -n "$p" ] && [ "$p" -gt "$TOPE" ]; then
    detener "RAM ${p}% > ${TOPE}%"; sleep 20
  fi
  if [ -n "$c" ] && [ "$c" -gt "$TOPE_CPU" ]; then altas=$((altas+1)); else altas=0; fi
  if [ -n "$c" ] && [ "$c" -lt 85 ]; then bajas=$((bajas+1)); else bajas=0; fi
  if [ "$altas" -ge 3 ]; then
    pausar "CPU ${c}% > ${TOPE_CPU}% (3 lecturas seguidas)"; altas=0
  fi
  if [ "$bajas" -ge 2 ]; then
    reanudar "$c"; bajas=0
  fi
  sleep 10
done
