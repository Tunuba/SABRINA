# restaurar.ps1
# Deja la descompilacion de Sabrina andando en una PC nueva (o despues de perder las carpetas), en un paso.
# Antes: clonar el repositorio (git clone https://github.com/Tunuba/SABRINA) y poner tu copia del juego
# (Redump USA, .cue + 97 .bin, o el .7z) en disco\ o en Descargas. Despues, doble clic en RESTAURAR.bat.
#
# Hace, saltando lo que ya este hecho:
#   1. arrancar.ps1 -Taller -SoloInstalar  (Python, emulador, Ghidra, Java, extraer el disco)
#   2. WSL con Ubuntu, si no esta
#   3. scripts/decomp_todo.sh              (herramientas de WSL, desensamblado y ejecutable IGUAL)
#   4. la tarea programada SabrinaRespaldo (respaldo cada 15 min y subida a GitHub cada hora)
#   5. scripts/rondas_paralelo.sh          (capturas y lote de auto.py, en segundo plano; ~1-2 h)
#
#   .\restaurar.ps1 -SinCapturas   no lanza el paso 5
param([switch]$SinCapturas)
$ErrorActionPreference = 'Stop'
$RAIZ = $PSScriptRoot
function Paso($t) { Write-Host ''; Write-Host "== $t" -ForegroundColor Cyan }
function Falla($t) { Write-Host "   $t" -ForegroundColor Red; exit 1 }

Paso '1. Juego, emulador y herramientas de Windows'
& (Join-Path $RAIZ 'arrancar.ps1') -Taller -SoloInstalar
if ($LASTEXITCODE -ne 0 -and $LASTEXITCODE -ne $null) { Falla 'arrancar.ps1 fallo (mira el mensaje de arriba)' }

Paso '2. WSL con Ubuntu'
$distros = (wsl.exe -l -q 2>$null) -replace "`0", '' | Where-Object { $_ }
if ($distros -notcontains 'Ubuntu') {
    Write-Host '   Instalo Ubuntu en WSL. Si Windows pide reiniciar, reinicia y vuelve a correr RESTAURAR.bat.'
    Write-Host '   Al terminar te pide crear un usuario y contrasena de Linux (la contrasena la pide despues sudo).'
    wsl.exe --install -d Ubuntu
    Falla 'Cuando Ubuntu quede instalado y con usuario, vuelve a correr RESTAURAR.bat'
}

Paso '3. Herramientas de descompilacion (WSL)'
$unidad = $RAIZ.Substring(0, 1).ToLower()
$rutaWsl = "/mnt/$unidad" + ($RAIZ.Substring(2) -replace '\\', '/')
wsl.exe -d Ubuntu -- bash "$rutaWsl/scripts/decomp_todo.sh"
if ($LASTEXITCODE -ne 0) { Falla 'decomp_todo.sh fallo (mira el mensaje de arriba)' }

Paso '4. Respaldo automatico'
$bash = 'C:\Program Files\Git\bin\bash.exe'
if (-not (Test-Path $bash)) { Falla 'Falta Git for Windows (winget install Git.Git) y vuelve a correr' }
$rutaBash = '/' + $unidad + ($RAIZ.Substring(2) -replace '\\', '/')
$a = New-ScheduledTaskAction -Execute 'C:\Windows\System32\conhost.exe' -Argument "--headless `"$bash`" -lc `"bash '$rutaBash/scripts/respaldo.sh'`""
$t1 = New-ScheduledTaskTrigger -Once -At (Get-Date).AddMinutes(1) -RepetitionInterval (New-TimeSpan -Minutes 15)
$t2 = New-ScheduledTaskTrigger -AtLogOn -User $env:USERNAME
$p = New-ScheduledTaskPrincipal -UserId "$env:USERDOMAIN\$env:USERNAME" -LogonType Interactive -RunLevel Limited
$s = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -StartWhenAvailable -ExecutionTimeLimit (New-TimeSpan -Minutes 10) -Hidden
Register-ScheduledTask -TaskName SabrinaRespaldo -Action $a -Trigger $t1, $t2 -Principal $p -Settings $s -Force | Out-Null
Write-Host '   tarea SabrinaRespaldo lista (cada 15 min; GitHub cada hora)' -ForegroundColor Green

if (-not $SinCapturas) {
    Paso '5. Capturas y lote automatico (en segundo plano, sin sonido)'
    if (-not (Test-Path (Join-Path $RAIZ 'estados\saltar.estado'))) {
        # los estados no van a GitHub (son RAM del juego): el de partida de las capturas se rehace jugando solo
        Write-Host '   creando estados\saltar.estado (el HUB jugando), ~1 min...'
        Push-Location (Join-Path $RAIZ 'scripts'); python crear_estado_saltar.py; Pop-Location
        if (-not (Test-Path (Join-Path $RAIZ 'estados\saltar.estado'))) { Falla 'no se pudo crear estados\saltar.estado' }
    }
    Start-Process -WindowStyle Hidden $bash -ArgumentList '-lc', "`"cd '$rutaBash' && bash scripts/rondas_paralelo.sh 8 12 > notas/logs/restaurar_rondas.txt 2>&1`""
    Write-Host '   corriendo; avance en notas\logs\restaurar_rondas.txt y notas\logs\ronda*.txt' -ForegroundColor Green
}
Paso 'Listo. Donde quedo el trabajo: notas\TRASPASO.md y la ultima de notas\fases\'
