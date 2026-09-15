# Abre Sabrina en PCSX-Redux con ventana, para jugar.
# Uso: powershell -NoProfile -ExecutionPolicy Bypass -File C:\Proyectos\SABRINA\jugar.ps1 [-Disco sabrina_todo.cue]
#   -Disco   un .cue de la carpeta disco (por defecto el de todos los mods; se arma con
#            scripts\armar.py sabrina_todo --es --invencible --ropa)
# Teclado: flechas = cruceta, X = X, D = circulo, Z = cuadrado, S = triangulo, Enter = START,
# Q/R = L1/R1. Un mando de Xbox tambien sirve.
param([string]$Disco = 'sabrina_todo.cue')
$R = 'C:\Proyectos\SABRINA\herramientas\pcsx-redux'
$cue = Join-Path 'C:\Proyectos\SABRINA\disco' $Disco
if (-not (Test-Path $cue)) { Write-Host "No existe $cue"; exit 1 }
Start-Process "$R\pcsx-redux.exe" -ArgumentList '-bios', "`"$R\openbios.bin`"", '-iso', "`"$cue`"", '-fastboot', '-run' -WorkingDirectory $R
