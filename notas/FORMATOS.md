# Formatos de Sabrina, lo que ya se sabe

Medido el 2026-09-14 sobre la imagen Redump (pista 1 de datos, 95 MB, y 96 pistas de audio).

## Disco

- ISO9660 normal con nombres, 105 archivos de datos. `extraido\sabrina.xml` tiene el sector (LBA)
  de cada uno (atributo `offs`).
- Pistas 2 a 97: audio de CD. dumpsxiso las nombra por sus entradas DA: `AUDIO1\CHACHAOS.WAV`,
  `AUDIO3\DIVINTRO.WAV`, etc. Las grandes (20 a 27 MB) parecen musica y las chicas voces.
- Arranca con OpenBIOS y `-fastboot` en PCSX-Redux. Menu principal a los 35 s.

## Ejecutable `SLUS_012.08`

PS-X EXE. Carga en `0x80010000`, `0x6D000` bytes; entrada `0x80010714`; BSS desde `0x8007C9D8`,
`0x5A800` bytes; pila `0x801FFFF0`.

## Niveles

FRONT (menu), HUB, CHAOS (C1), EGYPT (E1-E3), JAPAN (J1-J3), STONE (S1-S3), WEST (W1-W3).
Cada uno trae `GRAPHICS\<n>.PIC`, `.TEX`, `<n>W.INO`, `SOUND\<n>W.VHD/.VBD`, `WRLDDATA\<n>W.BIN`.

## `.PIC`, resuelto

Pantalla completa de 512x220, 16 bits por pixel (formato de la PS1), sin cabecera, 225280 bytes.
Son las pantallas de carga, logos y el aviso legal. `scripts\pic.py` convierte en los dos sentidos.
El negro se guarda como 0x0001 porque 0x0000 es transparente.

## `.TEX`, resuelto en lo esencial

Copia directa de la mitad derecha de la VRAM: rectangulo x 512-1023, y 0-511 (en unidades de 16 bits),
512 KB. Comprobado con `scripts\tex_vs_vram.py` en el HUB: 39 de 45 filas identicas, el resto las
cambia el juego al correr. Dentro hay texturas de 4 y 8 bits y las paletas (CLUT) en las filas de
abajo. Que textura usa que paleta lo dice el modelo, falta leer los `.INO`.

## Framebuffer

Dos buffers de 512x220 en la mitad izquierda de la VRAM (y 0 y y 220 aprox.).

## Ejecutable por dentro (Ghidra, `notas\ghidra\`)

- Analisis sin ventana: `analyzeHeadless` con el cargador `ghidra_psx_ldr` y el script
  `scripts\ghidra\ExportarTodo.java`. 1193 funciones, 544 reconocidas como biblioteca de Sony por firma.
  `funciones.tsv`, `textos.tsv` (con quien usa cada texto) y `decompilado.c` (50 mil lineas, no va a git).
- Nombres de archivos fuente que quedaron: BasicTools.c, File.cpp, GraphicTools.c, loadtga.c,
  modelLoader.c, Object.c, Particle.c, SceneProcessing.c, Screen.c, StratTools.c, TexAnima.c, WobjCode.c,
  DelaySpell.c, btrigger.c, membank.cpp, trigger.c.
- Restos de desarrollo: rutas `GRAPHICS\TARGA\`, `GRAPHICS\SPRITE\`, `GRAPHICS\PICTURES\` y `Titles12.tga`
  que no estan en el disco.
- **gp = 0x80084754.** Las globales se leen como `gp - algo`; Ghidra las muestra como `iRamffffXXXX`
  (direccion real = 0x80084754 + (0xXXXX - 0x10000)).
- **Objeto de Sabrina**: puntero en `0x8007CAF8`. Vida: byte `+0x118` (empieza en 20); la barra de la
  pantalla copia el valor en `0x8007CB1D`. `+0x70` estado (2 = muerta), `+0x3C` velocidad vertical (la
  gravedad suma 0x51E), `+0x80` tipo de suelo que pisa (lo recalcula la fisica cada paso: 8 muerte, 4 y 2
  dano), `+0x8C` bit 0x10 en el suelo. `+0x118` es la vida de TODOS los objetos, enemigos incluidos.
- **Truco escondido**: si la palabra `0x8007CB74` no es 0, el juego imprime "SABRINA IS INVINCIBLE" y no
  aplica dano de enemigos ni de suelo. Ningun codigo la enciende. Solo se lee en `0x80031300` y `0x8003401C`.
  El printf no sale por ningun lado en la version comercial.
- Danos a Sabrina (los que tambien escriben la barra): enemigos `0x80031324` (FUN_800310b4), suelo
  `0x80034320` y `0x80034604` (FUN_80033fc8, llamado cada paso por la fisica FUN_80033154), golpes de 4
  `0x8005A018` y `0x8005A16C`.
- Menus: textos en el ejecutable, alineados a 4 bytes, con tablas de punteros (menu principal en
  `0x80079D94`). '=' es el icono de X y '^' un bloque de barra. La letra esta en el `.TEX` (4 bits).
- La logica del juego corre a 30 pasos por segundo.
- Salida de depuracion del emulador: `emu.py` la guarda en `notas\logs\<nombre>.tty.log`. Ahi se ven las
  busquedas de archivos del CD (`CdSearchFile`).

## `WRLDDATA\*.BIN`, estructura

Lo lee FUN_8002456c (WobjCode.c): un contador de 32 bits, esa cantidad de objetos del mundo de 0x9C bytes,
otro contador y registros de 0x18 bytes. En el HUB: 8 objetos y 2 registros, 1304 bytes justos.

## Por descifrar

- `.INO`: empieza con `00 10 00 10 40 00 40 00` y un numero (0x29D en el HUB); luego entradas de
  12 bytes `ff ff 00 00 00 00 02 00 00 00 00 00`. Parece una cuadricula de 64x64 del mundo.
- Que hay dentro de cada objeto de 0x9C de `WRLDDATA` (posicion, tipo de enemigo u objeto).
- La posicion de Sabrina: `+0x24 +0x28 +0x2C` no cambian al caminar en el HUB; falta encontrarla.
- `ANIMS\*.ANI`: firma `MAO\0`.
- `SOUND\*.VHD/.VBD`: VAB estandar de Sony (`pBAV`).
- `FMV\*.STR`: video estandar, se abre con jPSXdec.

## Mods hechos

1. Pantalla de carga en espanol (`FR.PIC`), `scripts\mod_carga.py`. Funciona en el emulador: solo
   cambian 12 sectores del disco.
2. Menus en espanol, 62 textos del ejecutable, `scripts\traducir.py`. Comprobado con capturas del menu
   principal, ajustes y sonido.
3. Invencible, 5 instrucciones, `scripts\mod_invencible.py`. Comprobado con el laboratorio de dano
   (`control.lua`, ruta `suelo`): el juego original baja la vida de 20 a 19, el parchado se queda en 20,
   tambien arrancando el disco armado desde cero (`prueba_final.py`).

4. Pantalon azul, `scripts\mod_ropa.py`: 6 o 7 paletas por nivel, en los 14 niveles. Comprobado en el
   HUB arrancando el disco desde cero.

Todo junto: `python armar.py sabrina_todo --es --invencible --ropa` deja el disco para el emulador y
`mods\sabrina_todo.ppf` (32 KB) para compartir. `jugar.ps1` lo abre con ventana.

## Paletas de Sabrina (decodificando los paquetes de la GPU)

`scripts\gpu_paquetes.py` recorre la RAM buscando los paquetes de poligonos con textura (comandos
0x24-0x3F) y los agrupa por paleta (CLUT) y pagina de textura, con la caja que ocupan en pantalla. En el
HUB, de 4400 poligonos, Sabrina usa las paletas de 4 bits de la fila 472 de la VRAM y la de 8 bits
(512,473) para cabeza y pelo. Comprobado cambiandolas en vivo con `probar_paletas.py`: piernas
(832,472), cadera (864,472), brazo (896,472), pelo (512,473). La paleta de las piernas esta identica en
los 14 niveles (en otra posicion en cada .TEX); `FR.TEX` no la tiene y en esas filas trae pixeles de
imagenes. Los colores guardados son oscuros porque la GPU los multiplica por el color del vertice.
