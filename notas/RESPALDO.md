# Respaldo y migracion a otra PC

Ya se perdio trabajo dos veces por apagones y mudanzas: el repositorio publico no guarda el C, las
capturas ni los estados, porque son del juego. Este mecanismo evita tener que empezar de cero.

## Que se respalda y donde

`scripts\respaldo.sh` guarda, con historial, todo lo propio que costaria rehacer:

- el C escrito a mano (`decomp\src`),
- el avance (`decomp\progreso.tsv`, `notas\`, `notas\fases\` con el reporte de cada fase),
- los estados del emulador (`estados\`), los scripts y los parches.

Va a un repositorio git privado **en otro disco**, `C:\Users\<usuario>\respaldo_sabrina.git`. Otra ruta se
elige con la variable `SABRINA_RESPALDO`.

La tarea programada de Windows **SabrinaRespaldo** lo corre cada 15 minutos y al iniciar sesion, sin
ventana. Solo hace un commit si hubo cambios. El registro queda en `notas\logs\respaldo.txt`.

**Copia fuera de la PC: GitHub.** Una vez por hora el mismo script hace commit en `main` de lo que permite
el `.gitignore` y lo sube a github.com/Tunuba/SABRINA: el C, el avance, las notas y los scripts. Desde
2026-09-24 el C (`decomp\src`) ya no esta excluido. El juego, lo extraido, las capturas de RAM y los estados
del emulador **no** se suben, porque el repositorio es publico y eso es el juego con copyright. Con
`SABRINA_SIN_GITHUB=1` no sube.

Lo que NO va, porque se regenera:

| Que | Como se regenera | Tiempo |
|---|---|---|
| `decomp\asm` (desensamblado) | splat, dentro de `scripts\decomp_todo.sh` | segundos |
| `decomp\capturas` (~5 GB) | `bash scripts/rondas_paralelo.sh 8 12` | ~30-60 min |
| `decomp\src\auto` (borradores de m2c) y `progreso.tsv` | el lote `auto.py` (lo corre `rondas_paralelo.sh` al final) | ~1 h |
| el juego (`disco\`, `extraido\`) y las herramientas | tu copia del juego + `arrancar.ps1 -Taller` | ~15 min |

## Llevarlo a otra PC

0. Si la PC vieja ya no existe: `git clone https://github.com/Tunuba/SABRINA` trae todo lo propio, como mucho
   con una hora de atraso. Faltan los estados del emulador (`estados\`): `scripts\crear_estado_saltar.py`
   rehace `saltar`, que es el unico que usan las capturas. Sigue en el paso 3.
1. Si la PC vieja existe, un solo archivo con todo el historial, estados incluidos:
   ```
   bash scripts/respaldo.sh --bundle "E:\"        (una memoria USB, OneDrive, etc.)
   ```
2. En la PC nueva:
   ```
   git clone E:\sabrina_respaldo.bundle SABRINA
   ```
   Si solo tienes el repositorio `respaldo_sabrina.git`, tambien sirve: `git clone ruta\respaldo_sabrina.git SABRINA`.
3. Pon tu copia del juego (Redump USA, `.cue` + 97 `.bin`) en `SABRINA\disco\` y corre `.\arrancar.ps1 -Taller`
   (emulador, Ghidra, extraccion de archivos).
4. Instala WSL con Ubuntu 24.04 si no esta (`wsl --install -d Ubuntu`) y deja la descompilacion lista en un
   paso: `wsl -d Ubuntu -- bash "/mnt/<disco>/<ruta>/SABRINA/scripts/decomp_todo.sh"` (tiene que decir IGUAL).
5. Regenera las capturas y el lote: desde Git Bash, `bash scripts/rondas_paralelo.sh 8 12`.
6. Vuelve a crear la tarea programada del respaldo (ver "Tarea programada" abajo).

Desde ahi se sigue en el mismo porcentaje: el C a mano ya esta en `decomp\src` y `auto.py` lo marca
YA_HECHA sin tocarlo.

## Tarea programada (si hay que rehacerla)

En PowerShell:
```
$a = New-ScheduledTaskAction -Execute "C:\Windows\System32\conhost.exe" -Argument "--headless `"C:\Program Files\Git\bin\bash.exe`" -lc `"bash '/d/<ruta>/SABRINA/scripts/respaldo.sh'`""
$t = New-ScheduledTaskTrigger -Once -At (Get-Date).AddMinutes(1) -RepetitionInterval (New-TimeSpan -Minutes 15)
$p = New-ScheduledTaskPrincipal -UserId "$env:USERDOMAIN\$env:USERNAME" -LogonType Interactive   # con tu sesion: usa tus credenciales de GitHub
Register-ScheduledTask -TaskName SabrinaRespaldo -Action $a -Trigger $t -Principal $p -Force
```

## Ver o recuperar algo del respaldo

```
git --git-dir="$HOME/respaldo_sabrina.git" log --oneline | head          # los respaldos
git --git-dir="$HOME/respaldo_sabrina.git" show HEAD~3:decomp/src/sabrina/estados.c   # un archivo de antes
```
