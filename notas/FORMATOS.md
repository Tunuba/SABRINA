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

## Por descifrar

- `.INO`: empieza con `00 10 00 10 40 00 40 00` y un numero (0x29D en el HUB); luego entradas de
  12 bytes `ff ff 00 00 00 00 02 00 00 00 00 00`. Parece una cuadricula de 64x64 del mundo.
- `WRLDDATA\*.BIN`: un contador y coordenadas de 32 bits.
- `ANIMS\*.ANI`: firma `MAO\0`.
- `SOUND\*.VHD/.VBD`: VAB estandar de Sony (`pBAV`).
- `FMV\*.STR`: video estandar, se abre con jPSXdec.

## Mods hechos

1. Pantalla de carga en espanol (`FR.PIC`), `scripts\mod_carga.py`. Funciona en el emulador: solo
   cambian 12 sectores del disco.
