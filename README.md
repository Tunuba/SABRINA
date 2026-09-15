# SABRINA

Taller para modificar *Sabrina the Teenage Witch: A Twitch in Time!* (PlayStation, 2000,
Asylum Entertainment, SLUS-01208), un juego sin comunidad de mods. Todo corre en esta PC, en el
emulador PCSX-Redux, sin ventana y manejado desde Python.

## Carpetas

| Carpeta | Que hay | En git |
|---|---|---|
| `scripts\` | Todas las herramientas propias (Python, Lua, bash) | si |
| `notas\` | Hallazgos, capturas y registros | solo los .md |
| `mods\` | Imagenes y datos de cada mod | si |
| `herramientas\` | PCSX-Redux, Ghidra 12.1.3, JDK 21, mkpsxiso 2.30, jPSXdec 2.1, Nugget | no |
| `disco\` | La imagen del juego (97 pistas y .cue) y los discos parchados | no |
| `extraido\` | Los archivos sacados del disco con dumpsxiso, y `sabrina.xml` con el sector de cada uno | no |
| `estados\` | Estados guardados del emulador (21 MB cada uno) | no |
| `prueba_disco\` | Disco de prueba propio para ensayar el armado | no |

La imagen del juego y lo que se saca de ella no va en git ni se comparte. Un mod se comparte como
parche.

## Herramientas

- **Emulador**: `herramientas\pcsx-redux`, compilacion nocturna 25363 del 2026-09-13, bajada del
  manifiesto de distrib.app (`https://distrib.app/storage/manifests/pcsx-redux/dev-win-x64/manifest.json`,
  el enlace de winget ya no existe). Trae OpenBIOS, asi que no hace falta la BIOS de Sony.
- **Control remoto**: `scripts\emu.py` arranca el emulador sin ventana con `-no-ui -webserver` y carga
  `scripts\control.lua`, que agrega rutas HTTP para pulsar botones, contar frames, evaluar Lua y
  guardar o cargar estados. Captura con `/api/v1/screen/still`, RAM con `/api/v1/cpu/ram/raw`,
  VRAM con `/api/v1/gpu/vram/raw`.
- **Compilador MIPS**: en WSL `Ubuntu-24.04`, paquete `gcc-mipsel-linux-gnu`. Nugget en
  `herramientas\nugget`; compilar con `scripts\compilar_ejemplos.sh` (hay que pasar
  `PREFIX=mipsel-linux-gnu FORMAT=elf32-tradlittlemips`).
- **Disco**: `dumpsxiso -l` saca los archivos anotando su sector. `scripts\disco.py` parcha la pista
  de datos en su sitio, recalculando EDC y ECC (verificado contra sectores originales), y escribe un
  .cue que reusa las pistas de audio originales.

## Uso rapido

```
cd C:\Proyectos\SABRINA\scripts
python arrancar_sabrina.py 40                 capturas del arranque cada 5 s
python explorar.py titulo prueba "CROSS w120 c"   parte de un estado, pulsa y captura
python mod_carga.py                           mod de la pantalla de carga en espanol
```

`explorar.py` explica el formato de los pasos. Estados utiles: `titulo` (menu principal),
`saltar` (dentro del HUB, jugando).

## Lo que ya se sabe del juego

Ver `notas\FORMATOS.md`.
