# arrancar.ps1
# Deja todo listo para jugar Sabrina con los mods y abre el juego. Se puede correr las veces que
# quieras: lo que ya esta hecho no lo repite.
#
#   .\arrancar.ps1                 instala lo que falte, aplica los mods y abre el juego
#   .\arrancar.ps1 -Original       abre el juego sin mods
#   .\arrancar.ps1 -SoloInstalar   deja todo listo pero no abre el juego
#   .\arrancar.ps1 -Taller         ademas instala las herramientas para investigar el juego
#                                  (mkpsxiso, jPSXdec, Java 21, Ghidra con el cargador de PS1,
#                                  unos 800 MB) y saca los archivos del disco a extraido\
#   .\arrancar.ps1 -Juego ruta     usa esa copia del juego (.7z, o la carpeta con el .cue)
#
# El juego no viene en el repositorio. Hace falta tu propia copia, version USA (SLUS-01208),
# en formato Redump: un .cue y 97 pistas .bin, o el .7z que las trae. El script la busca en
# disco\ y en tu carpeta de Descargas.
# Con doble clic en ARRANCAR.bat se corre esto mismo sin abrir PowerShell a mano.
param(
    [switch]$Original,
    [switch]$SoloInstalar,
    [switch]$Taller,
    [string]$Juego = ''
)

$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'
$RAIZ = $PSScriptRoot
$HERR = Join-Path $RAIZ 'herramientas'
$ZIP = Join-Path $HERR '_zip'
$DISCO = Join-Path $RAIZ 'disco'
$NOMBRE = 'Sabrina the Teenage Witch - A Twitch in Time! (USA)'
$PISTA1 = Join-Path $DISCO "$NOMBRE (Track 01).bin"
$CUE = Join-Path $DISCO "$NOMBRE.cue"
$SHA1_PISTA1 = '7EA984FB4292E2E96C58EB436EC60539D56F490A'   # pista 1 de la imagen Redump USA
$MODS = 'sabrina_todo'
New-Item -ItemType Directory -Force $HERR, $ZIP, $DISCO | Out-Null

function Paso($t) { Write-Host ''; Write-Host "== $t" -ForegroundColor Cyan }
function Ok($t) { Write-Host "   $t" -ForegroundColor Green }
function Aviso($t) { Write-Host "   $t" -ForegroundColor Yellow }
function Falla($t) { Write-Host ''; Write-Host "   $t" -ForegroundColor Red; exit 1 }

function Bajar($url, $destino, $sha1 = '') {
    if (Test-Path $destino) { return }
    Write-Host "   bajando $(Split-Path $destino -Leaf)..."
    Invoke-WebRequest $url -OutFile "$destino.parcial" -UseBasicParsing
    if ($sha1 -and (Get-FileHash "$destino.parcial" -Algorithm SHA1).Hash -ne $sha1.ToUpper()) {
        Remove-Item "$destino.parcial"; Falla "La descarga de $url llego danada, vuelve a correr el script"
    }
    Move-Item "$destino.parcial" $destino
}

# ---------------------------------------------------------------- Python
Paso 'Python'
$PY = $null
foreach ($c in @('python', 'py')) {
    $cmd = Get-Command $c -ErrorAction SilentlyContinue
    # el "python" que trae Windows de fabrica solo abre la tienda; se descarta si no da version
    if ($cmd -and $cmd.Source -notmatch 'WindowsApps') { $PY = $cmd.Source; break }
}
if (-not $PY) {
    Aviso 'No hay Python, lo instalo con winget (Python 3.13, solo para tu usuario)'
    winget install -e --id Python.Python.3.13 --scope user --silent --accept-package-agreements --accept-source-agreements | Out-Null
    $PY = Join-Path $env:LOCALAPPDATA 'Programs\Python\Python313\python.exe'
    if (-not (Test-Path $PY)) { Falla 'No se pudo instalar Python. Instalalo desde python.org y vuelve a correr el script.' }
}
& $PY -m pip install --user --quiet --disable-pip-version-check pillow numpy py7zr capstone 2>$null
if ($LASTEXITCODE -ne 0) { Falla 'pip no pudo instalar pillow, numpy, py7zr y capstone' }
Ok "$(& $PY --version) con pillow, numpy, py7zr y capstone"

# ---------------------------------------------------------------- Emulador
Paso 'Emulador PCSX-Redux'
$REDUX = Join-Path $HERR 'pcsx-redux'
if (-not (Test-Path (Join-Path $REDUX 'pcsx-redux.exe'))) {
    # la pagina de descargas necesita JavaScript; el manifiesto que ella misma lee es publico
    $base = 'https://distrib.app/storage/manifests/pcsx-redux/dev-win-x64'
    $ultimo = (Invoke-RestMethod "$base/manifest.json").builds | Sort-Object id -Descending | Select-Object -First 1
    $m = Invoke-RestMethod "$base/manifest-$($ultimo.id).json"
    Bajar "https://distrib.app$($m.path)" (Join-Path $ZIP 'pcsx-redux.zip') $m.hashes.sha1
    Expand-Archive (Join-Path $ZIP 'pcsx-redux.zip') $REDUX -Force
}
if (-not (Test-Path (Join-Path $REDUX 'openbios.bin'))) { Falla 'Al emulador le falta openbios.bin' }
Ok 'listo, con OpenBIOS (no hace falta la BIOS de Sony)'

# ---------------------------------------------------------------- Juego
Paso 'Tu copia del juego'
if (-not (Test-Path $CUE) -or -not (Test-Path $PISTA1)) {
    $fuente = $null
    if ($Juego) {
        $fuente = Get-Item $Juego
    } else {
        $cands = @(Get-ChildItem $DISCO -Filter '*.7z' -ErrorAction SilentlyContinue)
        $desc = Join-Path $env:USERPROFILE 'Downloads'
        $cands += @(Get-ChildItem $desc -Filter 'Sabrina*Twitch*.7z' -ErrorAction SilentlyContinue)
        $fuente = $cands | Select-Object -First 1
    }
    if (-not $fuente) {
        Falla ("No encontre el juego. Pon tu copia (version USA, formato Redump) en`n   $DISCO`n" +
               "   como el .7z o como el .cue con sus 97 pistas .bin, y vuelve a correr el script.")
    }
    if ($fuente.PSIsContainer) {
        Write-Host "   copiando desde $($fuente.FullName)..."
        Copy-Item (Join-Path $fuente.FullName '*') $DISCO -Force
    } elseif ($fuente.Extension -eq '.cue') {
        Copy-Item (Join-Path $fuente.DirectoryName '*') $DISCO -Force
    } else {
        Write-Host "   descomprimiendo $($fuente.Name) (unos 700 MB, tarda un minuto)..."
        & $PY -c "import py7zr,sys; py7zr.SevenZipFile(sys.argv[1]).extractall(sys.argv[2])" $fuente.FullName $DISCO
        if ($LASTEXITCODE -ne 0) { Falla "No se pudo descomprimir $($fuente.FullName)" }
    }
    if (-not (Test-Path $CUE)) { Falla "Despues de copiar sigue sin estar $CUE. Los nombres deben ser los de Redump." }
}
$esRedump = (Get-FileHash $PISTA1 -Algorithm SHA1).Hash -eq $SHA1_PISTA1
if ($esRedump) { Ok 'imagen Redump USA comprobada' }
else { Aviso 'La pista 1 no es la de Redump USA: el juego abre, pero los mods pueden no aplicarse.' }

# ---------------------------------------------------------------- Mods
$cueJugar = $CUE
if (-not $Original) {
    Paso 'Mods (espanol, invencible y pantalon azul)'
    $ppf = Join-Path $RAIZ "mods\$MODS.ppf"
    $pistaMod = Join-Path $DISCO "$MODS (Track 01).bin"
    $cueMod = Join-Path $DISCO "$MODS.cue"
    $alDia = (Test-Path $pistaMod) -and (Test-Path $cueMod) -and ((Get-Item $pistaMod).LastWriteTime -gt (Get-Item $ppf).LastWriteTime)
    if (-not $alDia) {
        if (-not $esRedump) { Falla 'Sin la imagen Redump USA no se puede aplicar el parche. Usa -Original para jugar sin mods.' }
        Write-Host '   aplicando el parche...'
        & $PY (Join-Path $RAIZ 'scripts\ppf.py') aplicar $PISTA1 $ppf $pistaMod
        if ($LASTEXITCODE -ne 0) { Falla 'No se pudo aplicar el parche' }
        & $PY -c "import sys; sys.path.insert(0, sys.argv[1]); import disco; disco.cue_mod(sys.argv[2], sys.argv[3])" (Join-Path $RAIZ 'scripts') $cueMod $pistaMod
    }
    Ok 'disco con mods listo'
    $cueJugar = $cueMod
}

# ---------------------------------------------------------------- Accesos directos
Paso 'Accesos directos'
$exe = Join-Path $REDUX 'pcsx-redux.exe'
$argumentos = "-bios `"$(Join-Path $REDUX 'openbios.bin')`" -iso `"$cueJugar`" -fastboot -run"
$sh = New-Object -ComObject WScript.Shell
foreach ($lnk in @((Join-Path $RAIZ 'Sabrina.lnk'), (Join-Path ([Environment]::GetFolderPath('Desktop')) 'Sabrina.lnk'))) {
    $a = $sh.CreateShortcut($lnk)
    $a.TargetPath = $exe
    $a.Arguments = $argumentos
    $a.WorkingDirectory = $REDUX
    $a.IconLocation = "$exe,0"
    $a.Description = 'Sabrina the Teenage Witch con mods'
    $a.Save()
}
Ok 'Sabrina.lnk en el escritorio y en esta carpeta: doble clic y a jugar'

# ---------------------------------------------------------------- Taller
if ($Taller) {
    Paso 'Herramientas del taller'
    $gh = @{ 'User-Agent' = 'sabrina-arrancar' }
    Bajar 'https://github.com/Lameguy64/mkpsxiso/releases/download/v2.30/mkpsxiso-2.30-win64.zip' (Join-Path $ZIP 'mkpsxiso.zip')
    if (-not (Test-Path (Join-Path $HERR 'mkpsxiso'))) { Expand-Archive (Join-Path $ZIP 'mkpsxiso.zip') (Join-Path $HERR 'mkpsxiso') -Force }
    Bajar 'https://github.com/m35/jpsxdec/releases/download/v2.1/jpsxdec_v2.1-beta.zip' (Join-Path $ZIP 'jpsxdec.zip')
    if (-not (Test-Path (Join-Path $HERR 'jpsxdec'))) { Expand-Archive (Join-Path $ZIP 'jpsxdec.zip') (Join-Path $HERR 'jpsxdec') -Force }
    Bajar 'https://api.adoptium.net/v3/binary/latest/21/ga/windows/x64/jdk/hotspot/normal/eclipse?project=jdk' (Join-Path $ZIP 'jdk21.zip')
    if (-not (Get-ChildItem $HERR -Directory -Filter 'jdk-21*')) { Expand-Archive (Join-Path $ZIP 'jdk21.zip') $HERR -Force }
    $gr = (Invoke-RestMethod 'https://api.github.com/repos/NationalSecurityAgency/ghidra/releases/latest' -Headers $gh)
    $gzip = $gr.assets | Where-Object { $_.name -like 'ghidra_*_PUBLIC_*.zip' } | Select-Object -First 1
    $gver = ($gzip.name -split '_')[1]
    Bajar $gzip.browser_download_url (Join-Path $ZIP 'ghidra.zip')
    if (-not (Get-ChildItem $HERR -Directory -Filter 'ghidra_*_PUBLIC')) { Expand-Archive (Join-Path $ZIP 'ghidra.zip') $HERR -Force }
    $gdir = (Get-ChildItem $HERR -Directory -Filter 'ghidra_*_PUBLIC' | Select-Object -First 1).FullName
    if (-not (Test-Path (Join-Path $gdir 'Ghidra\Extensions\ghidra_psx_ldr'))) {
        $lr = Invoke-RestMethod 'https://api.github.com/repos/lab313ru/ghidra_psx_ldr/releases/latest' -Headers $gh
        $lzip = $lr.assets | Where-Object { $_.name -like "ghidra_${gver}_PUBLIC_*" } | Select-Object -First 1
        if ($lzip) {
            Bajar $lzip.browser_download_url (Join-Path $ZIP 'psx_ldr.zip')
            Expand-Archive (Join-Path $ZIP 'psx_ldr.zip') (Join-Path $gdir 'Ghidra\Extensions') -Force
        } else { Aviso "El cargador de PS1 todavia no tiene version para Ghidra $gver" }
    }
    Ok 'mkpsxiso, jPSXdec, Java 21 y Ghidra con el cargador de PS1'
    $ext = Join-Path $RAIZ 'extraido'
    if (-not (Test-Path (Join-Path $ext 'sabrina.xml'))) {
        Write-Host '   sacando los archivos del disco a extraido\ ...'
        $dump = Get-ChildItem (Join-Path $HERR 'mkpsxiso') -Recurse -Filter 'dumpsxiso.exe' | Select-Object -First 1
        & $dump.FullName -l -x $ext -s (Join-Path $ext 'sabrina.xml') $CUE | Out-Null
    }
    Ok 'archivos del juego en extraido\ (los scripts de scripts\ trabajan sobre ellos)'
}

# ---------------------------------------------------------------- Jugar
if ($SoloInstalar) { Paso 'Listo. Para jugar, doble clic en Sabrina.lnk'; exit 0 }
Paso 'Abriendo el juego'
Start-Process $exe -ArgumentList $argumentos -WorkingDirectory $REDUX
Ok 'Teclado: flechas, X = X, D = circulo, Z = cuadrado, S = triangulo, Enter = START. Un mando tambien sirve.'
