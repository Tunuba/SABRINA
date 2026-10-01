# Como retomar (actualizado 2026-09-24, antes de apagar la PC)

Todo lo escrito esta en `decomp\src` (y en GitHub).

**Hay dos PCs.** La del amigo: `D:\proyectos personales\Sabrina decomp\SABRINA`, distro WSL `Ubuntu`. La de Meme:
`C:\Proyectos\SABRINA`, distro `Ubuntu-24.04`. Los `.sh` de `scripts\` detectan solos la distro y la ruta
(`scripts\wsl.sh`); en los comandos de abajo cambia `-d Ubuntu` y la ruta `/mnt/d/...` por los de tu PC
(en la de Meme: `-d Ubuntu-24.04` y `/mnt/c/Proyectos/SABRINA`). Probado en la de Meme el 2026-09-24:
`decomp_todo.sh` da IGUAL y `verificar.py` da IGUAL en func_8001BE8C y func_8001FA3C.

Lo que estaba corriendo se paro a proposito y se retoma asi:

1. **Lote automatico** (m2c + verificador sobre todas las funciones con capturas). Retoma donde quedo
   (`decomp\build\hechas.txt`, 623 de ~1000 al pararlo). Desde PowerShell:
   ```
   Start-Process -WindowStyle Hidden wsl.exe -ArgumentList '-d','Ubuntu','--','bash','-lc','"cd ''/mnt/d/proyectos personales/Sabrina decomp/SABRINA/decomp'' && ./lanzar_lote.sh 6"'
   ```
   Avance en `decomp\build\auto_log2.txt`; resultado en `decomp\progreso.tsv`.

2. **Auditoria del C a mano**: `python3 auditar.py --procesos 12` (en WSL, carpeta decomp). Resultado por
   funcion en `notas\fases\auditoria.tsv`; el porcentaje total al final de `notas\logs\auditoria.txt`.
   **Lo que manda es auditoria.tsv**: una funcion escrita a mano solo cuenta si ahi dice IGUAL o IGUAL_V0.

3. **Los tres workflows de agentes** (se pararon a medias; el C que alcanzaron a escribir quedo en disco):
   - 23 funciones perdidas en la mudanza, run `wf_284f6b64-abc`
   - 7 funciones GTE que parten triangulos, run `wf_7ab69402-535` (`src\geometria\partir_*.c`)
   - oleada de ~100 funciones chicas, run `wf_cdde7b44-8fa` (archivos `*_gNN.c`)

   Para seguirlos no hace falta relanzarlos tal cual: mejor partir de `auditoria.tsv` y mandar agentes solo a
   las que quedaron DISTINTO / NO_COMPILA / TOPE_DE_TIEMPO.

4. **Si algo queda colgado en WSL**: `wsl -d Ubuntu -- bash "/mnt/d/proyectos personales/Sabrina decomp/SABRINA/scripts/parar_wsl.sh"`
   cierra el lote, los verificadores y los bucles que dejan los agentes (solo lo de Sabrina).

5. **Vigilante de RAM y CPU**: `bash scripts/vigilar_ram.sh 92 95` desde Git Bash (una sola copia; si ya hay
   una, sale sola). Pausa verificadores si la CPU pasa de 95 % y detiene uno si la RAM pasa de 92 %.

## Nivel fantasma (pendiente de probar jugando)

`scripts\nivel_fantasma.py` tenia dos fallos, ya arreglados en el script:
- **La traba**: cada una de las 4096 celdas declaraba el piso entero como suyo. Medido con
  `scripts\medir_fps.py`: **4.3 cuadros por segundo contra 31 del HUB original**. Ahora cada celda declara
  solo sus triangulos, igual que el HUB real.
- **La colision**: se leia la `y` del vertice en vez de la `z`, asi que todo el piso caia en una sola fila de
  la cuadricula. Ahora ocupa sus 100 celdas reales.
- **Nuevo: un cubo** (`CUBO` en el script: 1400 de lado, 700 de alto, en x = z = 2100), con la tapa y las 4
  paredes partidas en triangulos de tamano normal. Sin probar todavia: si se ve, si Sabrina se sube encima
  y si las paredes la frenan.

Para probarlo: `python scripts\nivel_fantasma.py disco` y despues `python scripts\medir_fps.py disco\sabrina_fantasma.cue`
(~5 min; tiene que dar cerca de 30 por segundo). Para jugarlo: `python scripts\nivel_fantasma.py probar`.

## 2026-09-30, PC de Meme: DISTINTO y NO_COMPILA a mano

Una sesion sola, sin agentes, con el lote `auto.py --procesos 3 --seguir` corriendo de fondo (no se toco).
`auditar.py` no tiene `--solo`, asi que no se corrio entero: cada funcion se verifico con `verificar.py` y
se anoto a mano en `notas/fases/auditoria.tsv`, como en la fase 4.

**A IGUAL (26, con Liberar)**: func_8003A46C (era la DISTINTO de la fase 4), ArchivoIniciar, func_80047710,
func_800425C8, TocarSonido, func_80042B78, func_8003A524, func_80037278, func_8002506C, func_8002EDC8,
func_8001E588, MatrizDesdeAngulos, func_80020818, func_80011930, func_8004F2D8, func_8004C82C,
func_80023B3C, RegistrarRecogible, func_8004BDA0, func_8001C45C, func_8002303C, func_80014670,
func_80014774, LeerMAO, PuntoEnTriangulo, Liberar. **A IGUAL_V0 (1)**: func_80037468 (v0 al salir antes es la
direccion de la tabla de saltos). Archivos nuevos `*_g13.c` en audio, colision, Screen, WobjCode, varios,
libgpu y psyq.

Trampas que aparecieron (sirven para las que faltan):
- **p[3] de PuntoEnTriangulo**: si el byte de ejes del triangulo vale 3 lee un cuarto valor del punto, que
  en el original es lo que sigue en la pila del llamador. func_8003A46C lo resuelve con
  `__builtin_dwarf_cfa()`; func_8003A524 poniendo normal, punto y vertice en un solo arreglo de 9.
- **Argumentos chicos**: con `s16`/`s8` en el prototipo GCC supone que vienen recortados y el original no
  (func_800425C8). Declararlos s32 y recortar donde el original recorta. Lo mismo con lo que devuelve una
  funcion real (SpuGetKeyStatus: declararla s32 y hacer `(s16)`).
- **Resta de punteros**: GCC divide "exacto" (por inverso multiplicativo); con un puntero parchado da otra
  cosa. Hacer la resta en bytes y dividir con signo (LeerMAO).
- **Direccion de una funcion propia**: si el C guarda `&func` y func esta en el mismo archivo, queda la
  direccion del C (0x804xxxxx). func_80014774 va en su propio archivo para que func_80014670 sea la real.
- Varias "void" pasan de IGUAL_V0 a IGUAL devolviendo lo que deja el original en v0 (func_8004F2D8,
  RegistrarRecogible).

**Escritas pero DISTINTO por variantes absurdas** (anotadas en auditoria.tsv con el motivo):
func_80023FD4 (con 0xAF43 casillas la tabla de sprites se lee hasta la pila de la propia funcion) y
func_800447E4 (una variante salta a un puntero de funcion al azar). **Liberar** (`src/varios/reservar_g13.c`) quedo IGUAL;
**Reservar** DISTINTO solo cuando D_8007C8E0 no es 0: llama a malloc de la BIOS (A0 0x33), que en el
emulador vuelve sin tocar v0, asi que el resultado es lo que hubiera en v0 (en el original, D_8007C8E0).
No es un error del C. Su verificacion tarda unas 2 horas.

**No intentadas**: DanoPorSuelo (1864 bytes, switch que m2c no lee) y las que leen el CD
(func_8002FF1C, func_80017D80, func_8002CF28: van a dar NO_TERMINA).

Mutantes: func_8003A46C 6/8 (los 2 vivos en comentarios), TocarSonido 6/8 (SpuGetKeyStatus no cambia en el
emulador), func_8002506C 7/8, func_8001C45C 4/8 (la rama de vectores muy grandes casi no se prueba),
PuntoEnTriangulo 8/8.

Lote de fondo al cerrar: 300 de 886 (empezo 19:07), sigue corriendo.

### Segunda tanda (2026-09-30, noche, mismas reglas; prioridad a las grandes)

**A IGUAL (11)**: func_8001D8EC (lectura de los mandos, `modelLoader/mando_g13.c`), func_8003A94C y
func_8003AF9C (choques contra listas de triangulos, `colision/consulta_g13.c`), func_800252A0 y
CrearObjetoMundo (crear objetos, `objetos/crear_g13.c`), func_80032B98 (hechizos, `sabrina/hechizos_g13.c`),
func_800325AC (acciones de Sabrina, `sabrina/acciones_g13.c`), func_80036880, func_80036D58 y
func_80037A18 (`objetos/camara_g08.c`), func_80047AA4 (`WobjCode/anotados_g13.c`).
**A IGUAL_V0 (3)**: func_80056584 (`objetos/atraido_g13.c`), func_80045278 y func_80046428 (dos clases de
enemigo que comparten el C, `objetos/enemigo_g13.c`). **Escrita y DISTINTO solo en v0**: func_80037738 (el
original deja basura en v0 y el verificador cree que un llamador lo lee).

En auditoria.tsv quedan 137 IGUAL y 11 IGUAL_V0 (62068 bytes escritos a mano y verificados).

Trampas nuevas:
- **GCC junta las ramas de un if que guardan en el mismo campo** y pone el valor en la pila del llamador
  (el lugar de un argumento), que el verificador compara. Se corta con `__asm__ volatile("" ::: "memory")`
  al final de cada rama (func_800252A0).
- Un void que deja algo util en v0 (func_80037A18: el alcance) pasa de IGUAL_V0 a IGUAL devolviendolo.

Saltadas: las del CD (func_8002A09C, func_80017D80, func_8002CF28, func_8002FF1C), DanoPorSuelo y
func_8005C358 (switch que m2c no lee). Siguen pendientes, de mayor a menor: func_80035314 (3900),
func_8005A360, func_80030208, func_8004D0C0, FisicaObjeto, func_80054068, func_80056CE8, func_80038318,
func_8001321C, func_8002367C, func_8002AC18...

Lote de fondo al cerrar esta tanda: 875 de 886.

### Tercera tanda (noche del 2026-09-30 al 10-01; el lote de fondo ya termino)

- func_80035314 (3900 bytes, la camara del juego) a IGUAL, en `objetos/camara_g08.c`. Trampa: llama a
  func_80036250, que lee una escala sin valor de la pila (0x14 bytes debajo de la del llamador); en el
  original ahi queda el s1 que guardo func_80047710 (el propio objeto camara). El C deja `o` en ese lugar
  con `__builtin_frame_address(0)[-5]` antes de llamarla.
- func_80038318 (1536, carga de hechizo) a IGUAL_V0; ActivarObjetosCercanos (544) y func_800489C4 (816, avanzar
  por la ruta) a IGUAL. func_80030208 (3164, el paso de Sabrina) escrita en `sabrina/paso_g13.c`: 475 de 476
  (la mala pasa por FisicaObjeto, que lee pila sin valor; depende del tamano del marco del C).
  func_8005A360 (3168) da NO_TERMINA (espera la musica del CD); no se escribio.
- Atajo util: probar el borrador de `src/auto` cambiando `juego.h` por `objeto.h` (los que fallaban por
  p_sabrina) y, si queda cerca, reescribirlo con tipos (func_80038318 y ActivarObjetosCercanos salieron asi).
- func_8004D0C0 (2564, el portal) a IGUAL_V0. FisicaObjeto (2436) a IGUAL en `colision/fisica_g13.c`. Trampa: copia
  a la consulta compartida D_800C6594 campos de su consulta local que nunca llena (basura de su pila); el C
  la toma al entrar del mismo lugar con `__builtin_dwarf_cfa() - 0xC0 + 0x40`. Lo que le falta a
  func_80030208 es esa misma basura vista desde el llamador (depende del tamano de su marco).
- DibujarTexto (900) a IGUAL (`Font/texto_g13.c`). func_8002367C (1136, el marcador) escrita: solo fallan 2
  variantes que parchan su tabla de saltos (las variantes de memoria tambien tocan jtbl_*; un switch en C no
  la usa, asi que esas nunca pueden dar igual). func_80056CE8 (1684) escrita pero NO_TERMINA (CD).
- Antes de escribir una, probar si termina: `scratchpad/termina.sh` corre la original en la primera captura
  (estaba en el scratchpad de la sesion; es un `verificar.ejecutar` sobre capturas/F/00).
- func_8003C1E8 (832, disparo de enemigo), func_800365F0 (656) y func_80031698 (572, reaparecer) a IGUAL.
  Trampa de func_80031698: func_80031494 (ya verificada) usa lo que trae en v1; el C lo llama con un
  `__asm__` que pone v1 = D_8007CAFC y hace el jal.
- CrearRecogible (544), func_8004FA54 (acciones del inventario), func_800607AC (seguir una ruta),
  func_80053C74 (marca de lugar), func_800113DC (SetDrawEnv), func_8005C358 (1416, el selector de hechizos),
  DibujarCeldasVisibles (508), func_80010920 (FntOpen) e ImprimirDepuracion (960, FntPrint) a IGUAL.
- Trampa nueva, el marco a mano: CrearRecogible arma el objeto en su pila y el iniciar de la clase guarda esa
  direccion (la camara); ImprimirDepuracion, con una letra de formato que no entiende, copia bytes de su
  propio marco. GCC pone los registros guardados arriba del marco, asi que no se puede igualar en C: la
  funcion es `__attribute__((naked))` con el prologo del juego en `__asm__` y llama a un cuerpo en C
  (`static`, `noinline, used`) que recibe el sp del marco.
- Para pasar de IGUAL_V0 a IGUAL en un switch con tabla: el v0 de los casos que saltan derecho al final es la
  direccion del final (la que esta en la tabla), y ojo con los delay slots que oculta el filtro de nop.
- func_80054068 (1748, el activador) queda DISTINTO solo por una variante que parcha jtbl_80062550.
- FntOpen: con el flujo -1 el campo largo cae sobre D_80063500 (se relee al final con volatile).
- Lentos: func_8001981C (menu, `Screen/menu_g13.c`) paso los 30 min de fondo sin terminar; func_8004E32C
  (el asignador, `varios/banco_g13.c`) igual de lento. Correrlos solos con mucho tiempo.
- Mas tarde, la misma noche: func_8005ED8C (5092, el jefe de los mundos; marco a mano porque en el estado
  0xE pasa a func_80048228 un lugar de su pila sin llenar y en el 5 usa el s0 del que llama),
  func_800318F4 (3256, moverse), func_800349F0 (1428, reaparicion), func_8005BA10 (1216),
  func_8002886C (1000) y func_80028D40 (844, libpad), func_8004E32C (684, reservar), func_8003477C (628),
  func_80050938, func_800509A8 y func_8003BFC4 a IGUAL.
- func_8004E32C: func_80017CBC llega al malloc de la BIOS, que en el emulador vuelve con el v0 que traia;
  el C la llama con un `__asm__` que deja v0 = pv (NULL) como el original.
- Quedan DISTINTO por artefactos: func_8004B320 (una variante con nivel 0x12 deja un byte que nadie
  escribe a la vista; con un gancho de escritura en Unicorn las dos dan igual) y func_80025EF8 (un puntero
  de funcion al azar). func_80021A30 (cuadro sin camara, `Screen/cuadro_g13.c`) es lenta: sin resultado.
- Saltadas por el CD: func_8002A6D0 (CD_sync), func_8002A950, func_8002BE88 (CdSearchFile).
