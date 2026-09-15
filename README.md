# SABRINA

Mods para *Sabrina the Teenage Witch: A Twitch in Time!* (PlayStation, 2000, Asylum Entertainment,
SLUS-01208), un juego que no tenia comunidad de mods, y las herramientas que se hicieron para
descifrarlo.

## Jugar

1. Consigue tu propia copia del juego, version USA en formato Redump (un .cue con 97 pistas .bin, o el
   .7z que las trae) y dejala en la carpeta `disco\` o en tu carpeta de Descargas. El juego no viene en
   este repositorio.
2. Doble clic en `ARRANCAR.bat`.

La primera vez instala lo que falte (Python si no esta, el emulador PCSX-Redux), comprueba que la copia
sea la correcta, le aplica el parche y abre el juego. Deja un acceso directo `Sabrina` en el escritorio
para las siguientes veces.

Teclado: flechas para moverse, X = X, D = circulo, Z = cuadrado, S = triangulo, Enter = START.
Un mando de Xbox tambien sirve.

Otras formas de correrlo, desde PowerShell en esta carpeta:

```
.\arrancar.ps1 -Original       el juego sin mods
.\arrancar.ps1 -SoloInstalar   deja todo listo sin abrir el juego
.\arrancar.ps1 -Taller         ademas instala las herramientas para investigar (unos 800 MB)
```

## Que traen los mods

- Menus y pantalla de carga en espanol.
- Sabrina no pierde vida.
- Pantalon azul en todos los niveles.

El parche es `mods\sabrina_todo.ppf`. Tambien sirve con PPF-O-Matic sobre la pista 1 de la imagen.

## Carpetas

- `scripts\` herramientas propias, en Python y Lua.
- `mods\` los parches PPF.
- `notas\FORMATOS.md` todo lo descifrado del juego. `notas\OBJETOS.md` los objetos de cada nivel.
- `notas\DESCOMPILACION.md` la descompilacion (`decomp\`) y `notas\TRASPASO.md` por donde seguir.
- `notas\simbolos.tsv` nombres de funciones y datos; `notas\modulos.tsv` a que archivo fuente pertenece
  cada tramo del ejecutable.
- `herramientas\`, `disco\`, `extraido\`, `estados\` se crean al instalar y no van al repositorio.

## Taller

Con `.\arrancar.ps1 -Taller` quedan mkpsxiso, jPSXdec, Java 21 y Ghidra con el cargador de PS1, y los
archivos del disco en `extraido\`. Desde `scripts\`:

```
python armar.py sabrina_todo --es --invencible --ropa   vuelve a armar el disco y el parche
python ino_obj.py H1W                     modelos de un nivel a OBJ con texturas
python nivel_completo.py S3W              el nivel entero con sus objetos y rutas, a OBJ
python animar.py SABRun                   animacion de Sabrina en GIF
python animar.py S3W RockTroll STONE TROLLtaunt   animacion de cualquier personaje
python sprites.py S3W [particulas]        sprites de pantalla o cuadros de particulas
python letra.py FRW "Pulsa = para seguir" texto con la letra del juego
python vab.py todos                       sonidos de todos los niveles a WAV
python wobj.py S3W                        objetos de un nivel
python pic.py todos salida                pantallas de carga a PNG
python ir_a_nivel.py saltar 3 30          salta a un nivel en el emulador
python prueba_final.py sabrina_todo.cue   arranca el disco desde cero y prueba el dano
```

`emu.py` maneja el emulador sin ventana por HTTP (`control.lua`): botones, capturas, RAM, VRAM,
estados guardados y contadores por direccion. Los estados que usan algunos scripts (`titulo`, `saltar`,
`nivel_S3`) se crean con `explorar.py` e `ir_a_nivel.py` con `--guardar`.

Ghidra sin ventana, desde la carpeta del proyecto. La primera vez importa y analiza (unos 5 minutos);
despues se aplican los simbolos (gp y nombres), se crean las funciones que solo se alcanzan por punteros y
se exporta:

```
$env:JAVA_HOME = (Get-ChildItem herramientas -Directory -Filter 'jdk-21*').FullName
$g = (Get-ChildItem herramientas -Directory -Filter 'ghidra_*_PUBLIC').FullName
& "$g\support\analyzeHeadless.bat" "$PWD\ghidra" sabrina -import extraido\SLUS_012.08 -overwrite `
  -scriptPath scripts\ghidra -postScript ExportarTodo.java "$PWD\notas\ghidra"
& "$g\support\analyzeHeadless.bat" "$PWD\ghidra" sabrina -process SLUS_012.08 -scriptPath scripts\ghidra `
  -postScript AplicarSimbolos.java "$PWD\notas\simbolos.tsv" -postScript FuncionesPorPunteros.java `
  -postScript ExportarTodo.java "$PWD\notas\ghidra"
```

Para compilar codigo MIPS de PS1 hace falta WSL con `gcc-mipsel-linux-gnu` y Nugget en
`herramientas\nugget` (ver `scripts\compilar_ejemplos.sh`).
