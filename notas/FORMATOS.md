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

## Ciclo principal y selector de niveles

FUN_80010030 es el ciclo principal. Carga el nivel del byte `0x8007CA00` (0 menu, 1-3 Stone, 4-6 Egypt,
7-9 Japan, 10-12 West, 13 HUB, 14 Chaos; tablas de nombres en 0x80062A38 sonido, 0x80062A78 .TEX,
0x80062AB8 .PIC) y juega mientras el halfword `0x8007C9FC` no sea 0. `scripts\ir_a_nivel.py` escribe el
nivel y pone ese halfword en 0: el juego carga el nivel pedido (probado con Stone 3, Volcanic Caves).
Restos de desarrollo en ese ciclo: si falta el .PIC o el .TEX, convierte desde los originales y dice
"Please restart.... :oP".

## Posicion de Sabrina, resuelto

`+0x24 +0x28 +0x2C` de su objeto son x y z (int32). En el HUB no cambiaban porque al empezar Sabrina
esta frenada ante FashionDiva. `scripts\visitar.py` la teletransporta junto a cada objeto de un nivel.

## `WRLDDATA\*.BIN`, objetos (FUN_800246a0)

`+0x00 +0x04 +0x08` posicion, `+0x0C` tipo (int16), `+0x0E +0x10 +0x12` rotacion, `+0x14 +0x16 +0x18`
escala (4096 = 1.0), `+0x1C` 127 bytes de parametros. Tipo 1 = inicio de Sabrina (su x coincide con la
de ella al empezar). Tipos 4, 0x12, 0x13, 0x17 aparte (0x17 sonido). El resto usa la tabla de clases
(0x80074858 + 4*nivel, 0x54 bytes por tipo: funcion que lo maneja y modelo), igual en todos los niveles.
Enemigos: 2, 14, 15, 16, 17, 22 (sus funciones restan +0x118). Resumen en `notas\OBJETOS.md`
(`scripts\wobj.py`); fotos por tipo en Stone 3 con `visitar.py`.

## `.INO`, resuelto (`scripts\ino.py`, `scripts\ino_obj.py`)

Leido del cargador FUN_80018670, en este orden:
1. cuadricula del mundo: int16 A, int16 B, int16 ancho, int16 alto, int32 C; A*12, B*8, C*2 bytes (64x64)
2. uint16 n; n*32 bytes (FUN_80024328)
3. int16 ntex; ntex*32 (texturas); 0xDC bytes; un arbol de nodos por modelo de la lista del nivel
   (punteros en 0x8007C244 + 4*nivel; nombres .bud de desarrollo, por ejemplo `SABdefault.bud`)
4. uint16 n; n*12 bytes (FUN_80018c14)
5. uint16 n; n*32 bytes de particulas (FUN_8001f4a8)
Nodo: int16 nvert (negativo = fin), int16 ntri, int16 nhijos, MATRIX de 32 bytes, int16 largo y nombre
(con cero al final), hijos, triangulos de 28 bytes (int32 v0 v1 v2, int32 textura, 6 bytes de UV, 6 sin
descifrar) y vertices de 12 bytes (int16 x y z, relleno, r g b, relleno).
Comprobado: en el HUB los 124 nodos caen exactos sobre los 124 nombres del archivo, y el juego carga 25
modelos en el HUB y 51 en Stone 3, lo mismo que las listas. `FRW.INO` se lee hasta el ultimo byte; en
los demas queda una cola que el juego no lee (en el HUB trae una segunda copia de COSTUMEwest): parecen
restos de una version anterior del archivo que la herramienta del estudio no recorto.
Sabrina son dos modelos (cadera para abajo y para arriba) por traje: default, egypt, japan, stone, west.
Las funciones FUN_8001cf88 y FUN_8001d368 son la herramienta que armaba los .INO desde .bud, .TNF y
.XDX; quedaron en el juego.

## Triangulo de 28 bytes, completo

int32 v0 v1 v2, int32 textura, u0 v0 u1 v1 u2 v2, y 6 bytes:
- byte 0: tipo de superficie. 0 suelo normal, 0x01 otro suelo, 0x02 suelo que hace dano, 0x08 muerte,
  0x10 pared (su normal es horizontal en los 252 triangulos de Stone 3), 0x40 pared especial. Son los
  valores que mira FUN_80033fc8 en `+0x80` del objeto.
- byte 1: siempre 0.
- bytes 2 a 4: normal de la cara, int8 con 127 = 1.0; en los 2473 triangulos de Stone 3 apunta del lado
  de (v1-v0)x(v2-v0).
- byte 5: ejes para la prueba de colision (FUN_8003a268): bits 0-1 un eje, bits 2-3 el otro. 8 = plano
  XZ (suelos), 9 = YZ, 4 = XY (paredes).

## Cuadricula del mundo (seccion 1 del .INO)

64x64 celdas de 0x40000 unidades, de -0x800000 a 0x800000 en x y z (FUN_8003ae28). Fila =
(~((z >> 16) + 0x80) & 0xFF) >> 2, columna = ((x >> 16) + 0x80) >> 2.
- Listas (8 bytes): int16 cantidad, int32 inicio en la tabla de indices; los indices (int16) son
  triangulos del modelo del mundo. Es la colision por celda. Comprobado: la suma de las listas es igual a
  la cantidad de indices y todos caen dentro del mundo, en todos los niveles.
- Celdas (12 bytes): int16 primer triangulo de suelo de la celda (-1 ninguno), int16 cuantos, int16
  cantidad de objetos, int16 primer objeto de WRLDDATA (los objetos van ordenados por celda), uint32 zona.
  Los rangos de suelo cubren justo todos los triangulos de suelo normal (2085 de 2085 en Stone 3, 512
  de 512 en Chaos; en Egypt 1 tambien 76 de tipo 0x80, otro suelo caminable). FUN_80020f00 activa los
  objetos de las celdas cercanas a Sabrina: 119 de 119 objetos de Stone 3 caen en la celda que los lista.
- Zona: siempre una potencia de dos (FUN_80020a48 pasa el numero de zona 0-16 a un bit). El juego dibuja
  y activa solo la zona de Sabrina y las dos vecinas (el bit corrido a cada lado): el nivel esta partido
  en hasta 16 salas en fila. Stone 3 tiene 8, Egypt 1 tiene 10, el HUB ninguna.
- Escala: una posicion de WRLDDATA o del objeto de Sabrina es la coordenada del modelo del mundo por 256.

## Seccion 2 del .INO: sprites de pantalla

59 registros con el formato de textura: iconos de los 6 hechizos, el aro, la barra de vida, los digitos,
gemas, huevo, los 12 signos del zodiaco, los objetos anacronicos y los retratos para los dialogos.
`scripts\sprites.py`.

## Seccion 4 del .INO: la letra

Un registro de 12 bytes por casilla (94): +4 TPAGE, +5 avance, +6 CLUT (cada letra tiene la suya), +8 u,
+9 v, +10 ancho, alto 32. El juego pasa cada caracter ASCII a su casilla con la tabla de 128 bytes en
`0x8006551C`: a-z 0-25, A-Z 47-72, 0-9 35-44, y los iconos @ triangulo, < cuadrado, = X, > circulo,
` cruceta, ^ bloque de barra. El espacio da 126 y avanza 7 sin dibujar. `scripts\letra.py`.

## Objetos: que es cada tipo

El numero de tipo es un puesto; la tabla de clases de cada nivel dice que modelo usa (entrada m-1 de la
lista de modelos del nivel). 1 Sabrina, 2/15/16/17/22 enemigos (Stone: brujo, cavernicola,
triceratops, planta, cavernicola mujer; Egypt: lanzador, camello, guardia; Japan: monje, ninja, geisha;
West: gordo, nino, coyote), 3 Salem en su burbuja, 13 trampa con puas, 24 y 25 gemas especiales, 28 jefe
(RockTroll, chaos), 39 ficha del zodiaco, 40 cofre, 41 caja, 46 roca rodante, 47 mula, 49 FashionDiva, 50
el ropero, 51 pesa, 52 planta rodante. Los tipos 4, 0x12, 0x13 y 0x17 son objetos para recoger: el
juego anota en 0x800C7990 los ya recogidos y no los vuelve a poner.

## Rutas de patrulla y parametros de enemigos

La segunda lista de WRLDDATA (registros de 24 bytes, se carga en 0x800D58A4) son puntos de ruta: x y z,
int16 numero, anterior y siguiente (0 = ninguno). Hay rutas de ida y vuelta (1-2) y cerradas (11 a 19).
Enemigos (FUN_80044f50 y parecidas): vida en +0x118 (2, 1 en Egypt), dano que hacen en +0x119 (1).
Parametros: +00 int16 primer punto de ruta (0 o -1 = quieto; si no, arranca ahi y la sigue), +04 y +08
dos radios en 16.16 que el juego eleva al cuadrado (de 0.7 a 12). Casi todos los enemigos estan parados
justo sobre su primer punto. En los objetos para recoger los parametros son basura del editor salvo el
byte 4 (siempre 0: gema de valor 1; la tabla de 0x800757CC da valores 1 2 3 5 10 20 50 100).

## Seccion 5 del .INO: cuadros de particulas

Registros de 32 bytes: h4 h5 tamano en el mundo (0x1000 = 1.0), h6 TPAGE, h7 CLUT, h8 u v, h14 u y v
finales (el tamano en pixeles sale de ahi). En Stone 3: chispas (12 cuadros), la gema que gira (8
cuadros, gris porque el juego le cambia la paleta), huevo, herradura, abanico, escarabajo y la estrella
1UP. Cada efecto (tabla en 0x80074898) dice desde que cuadro empieza. `sprites.py S3W particulas`.

## Direcciones de los codigos de GameShark (confirman lo propio)

Vida 0x8008B210 (= objeto de Sabrina + 0x118), vidas 0x800C8518, gemas 0x800C8556, huevos 0x800C857A,
hechizos 0x8007C8B0 a 0x8007C8B5, objetos anacronicos 0x8007C88C a 0x8007C88F. 0x800C8518 es tambien el
bloque de 0x13AC bytes que prepara el ciclo principal: parece la partida guardada.

## Animaciones, nombres

Las tablas de punteros a los nombres .MAO dan el orden real de cada .ANI: Sabrina 0x8006DA34 (47),
Egypt 0x8006DEC8 (43), Stone 0x8006E30C (38), Japan 0x8006E774 (43), West 0x8006EC18 (44), Chaos 0x8006ED94
(8), Hub 0x8006EE40 (6). En las 229 animaciones, donde hay modelo, los huesos coinciden con sus piezas
(`scripts\anims_nombres.py`). `animar.py` hace GIF de cualquier personaje; los texeles con el bit 15 se
mezclan al 50 % (la burbuja de Salem).

## Sonidos y videos

`SOUND\*.VHD/.VBD` son VAB estandar; `scripts\vab.py` saca las 45 a 55 muestras de cada nivel a WAV (en
los 15 bancos la tabla de tamanos suma justo el .VBD). `FMV\*.STR` salen a AVI con jPSXdec:
`java -jar jpsxdec.jar -f "<pista 1>.bin" -x indice.idx -a video -dir notas\videos`.

## Por descifrar

- `.INO`: empieza con `00 10 00 10 40 00 40 00` y un numero (0x29D en el HUB); luego entradas de
  12 bytes `ff ff 00 00 00 00 02 00 00 00 00 00`. Parece una cuadricula de 64x64 del mundo.
- Los parametros de los objetos que no son enemigos (cofres, Salem, jefes).
- La partida guardada (bloque de 0x13AC bytes en 0x800C8518): se saben vidas +0x00, gemas +0x3E y
  huevos +0x62.
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
