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
- Final de la noche: PutDispEnv (func_8001321C), DanoPorSuelo (1864), func_8001981C (menu), func_80021A30 y
  Reservar (con el mismo truco del v0 del malloc de la BIOS que func_8004E32C) a IGUAL; func_8001EDE4
  (particula), func_8002805C (motores del mando), func_800460CC (iniciar enemigo) y func_8004EEF4
  (directorio de la tarjeta) pasaron de borrador de `src/auto` a archivo escrito, IGUAL_V0.
- Lo que queda sin IGUAL: las del CD (NO_TERMINA), func_80030208 (basura de pila que dejan los registros
  guardados por las llamadas), y las de artefactos (tablas de saltos parchadas, punteros de funcion al azar).

### Capturas nuevas para las SIN_CAPTURAS (2026-10-01)

- Capturar funciona en esta PC: `py` (Python 3.13 de Windows, `python` es el alias de la tienda) y
  PCSX-Redux con `-no-ui` y CREATE_NO_WINDOW (emu.py), sin ventanas. Un solo emulador a la vez.
- `capturar_mas.py 3 0..14 --solo <las 525>` (22 min, todos los niveles desde `saltar`) solo saco 4: el
  recorrido de siempre no llega a lo que falta. Lo que si sirvio: partir del ARRANQUE del disco (sin
  estado) y pasar por las pantallas legales, el video, el titulo y los menus: 121 de una vez. Desde
  `titulo`, `nuevo`, `final_hub`, `nivel_S3` y `saltar` con recorridos largos salieron 12 mas.
  Total: 137 funciones con capturas nuevas; quedan 388 sin capturas (codigo que no se ejecuta en esos
  recorridos: clases de objetos que no aparecen, la tarjeta de memoria, el CD, herramientas).
- El script de esta ronda (`capt_sin.py`: estado o `arranque`, lista, recorrido) estaba en el scratchpad
  de la sesion; es capturar_mas con --solo leido de un archivo y la opcion de partir del arranque.
- El lote sobre esas 137: `auto.py --solo <lista> --procesos 2` (mezcla en progreso.tsv sin borrar lo
  anterior; ojo, cada 25 reescribe build/hechas.txt con las de esta tanda: se guardo una copia antes).
- El lote `auto.py --solo` sobre las 137 lo corto Claude Code por memoria baja de la PC (no por el lote)
  antes del primer guardado: progreso.tsv y build/hechas.txt quedaron sin tocar. FALTA correrlo: la lista
  de las 137 es la diferencia entre las SIN_CAPTURAS de progreso.tsv y las que hoy tienen .regs en
  `decomp/capturas`.

### Cierre del 2026-10-01 (por pedido de Meme)

- El lote `auto.py --solo <las 137> --procesos 1` termino (con un corte a las 2 h, retomado con `--seguir`).
  De las 137: 26 IGUAL (2444 bytes), 1 IGUAL_V0, 7 DISTINTO, 16 NO_COMPILA, 7 NO_TERMINA, 3 GTE,
  3 M2C_FALLA, 10 YA_HECHA y **64 ERROR** ("process pool terminated abruptly": el trabajador se murio, casi
  seguro por memoria; no son resultados reales). Resumen del lote: 382 funciones verificadas, 24.2 %
  (progreso.tsv + lo escrito a mano).
- Listas en `notas/fases/tanda137/`: `las_137.txt`, `error_rehacer.txt` (las 64 a volver a pasar) y
  `hechas_antes_de_la_tanda.txt` (copia de build/hechas.txt antes de esta tanda; el lote con --solo lo
  reescribe con las de su tanda). Para retomar: `python3 auto.py --solo $(paste -sd, error_rehacer.txt)
  --procesos 1`, con la RAM vigilada (bajo 2 GB pausar con `pkill -STOP -f auto.py`, seguir con -CONT).
- **Escrito a mano y SIN VERIFICAR** (no esta en auditoria.tsv, no cuenta): `libgpu/reset_g13.c`
  (ResetGraph func_80012B0C, SetDispMask func_80012CDC, SetGraphDebug func_80012C80, func_80012AE4),
  `libgpu/canal_g13.c` (func_800144C4, func_80014598), `psyq/libetc_g13.c` (func_8001668C, func_800168EC,
  func_80016910, func_80016940, func_800169A0, func_80016AC4, func_80016D78, func_80016AF4, func_80016DA0,
  func_800163E4), `psyq/libgs_g13.c` (func_80016F38), `Font/textos_g13.c` (func_800190C0 con el v0 de
  entrada leido por asm, func_800193F8), `Screen/video_g13.c` (ReproducirSTR, PantallasLegales),
  `varios/arranque_g13.c` (func_800106C8, func_80010000). Correr vfull/verificar sobre cada una y anotar.
  Ojo: al estar en src, auto.py las marca YA_HECHA aunque no esten verificadas.
- Sin tocar por ser asm puro: func_80016170 (setjmp) y func_80017BC0 (parche de la BIOS).
- Verificadas despues (01-10, tarde): IGUAL ResetGraph, SetDispMask, SetGraphDebug, func_80012AE4,
  func_800144C4 y func_80014598 (D_80063824 es la base, no un puntero a puntero), func_8001668C,
  func_800168EC, func_80016910, func_80016940, func_800169A0, func_80016AC4, func_80016D78, func_80016AF4,
  func_80016DA0, func_80016F38 (D_80084C90 no tiene simbolo: se toma como D_80084CB0 - 0x20),
  func_800190C0, func_800193F8 y func_80010000. DISTINTO func_800163E4 (el setjmp guarda la vuelta y la pila
  del C). NO_TERMINA ReproducirSTR y PantallasLegales. Sin resultado func_800106C8 (llama al bucle
  principal; la original da error de lectura sin alinear en su captura y el verificador tarda demasiado).
- Las 64 de error_rehacer volvieron a dar ERROR ("process pool terminated abruptly") aunque el lote
  termino: no es la memoria (func_8002D170 sola da IGUAL en 15 min con 167 MB). Se pasan ahora DE A UNA
  (`auto.py --solo F --procesos 1` por funcion, script de_a_una.sh del scratchpad, log en
  build/auto_de_a_una_log.txt), asi un trabajador que se muere no arrastra a las demas.
- Escrito a mano y SIN VERIFICAR todavia (el lote ocupa los dos procesos): `geometria/azar_g13.c`
  (func_80021C48), `Screen/primitivas_g13.c` (func_8002153C), y en `psyq/mando_g13.c` func_80028D0C,
  func_80029ED4, func_80027AD0 (PadInfo) y func_800283C4 (PadInitDirect).
- Noche del 01-10: de las 64 y de las 137, a mano IGUAL: func_8004CB48, func_8005BED0, func_80047064
  (creditos), func_8004DAC4, func_8003DC48, func_80041CD8, func_8004EB04, func_8003EAF8, func_8004DC10,
  func_80055A38, func_8005DDE8, func_8005D164, func_8005DCD4, func_8005D844, func_8005D9C0, func_8005D1D0,
  func_80021C48, func_80028D0C, func_80029ED4, func_800283C4. DISTINTO por artefacto: func_80027AD0
  (puntero de funcion al azar), func_8003E914 y func_8003E0C4 (la captura 00 hace saltar a la ORIGINAL a 0
  y al C no; raro, mirar si la captura de esas dos de la SPU es buena). func_8002153C escrita: la original da
  error de lectura en su captura (Reservar con el malloc de la BIOS) y el C no termina; sin anotar.
- func_8002D170 dio IGUAL sola (15 min) pero en el lote quedo ERROR otra vez: repetirla sola.
- Saltadas por el CD: func_8002D714, func_8002D56C, func_8002FF1C, func_8002B810, func_8002B2BC,
  func_8005D50C (el reproductor de video).
- 01-10 noche, final: el reintento de func_8002D170 sola (auto.py --solo, 15 min) lo corto Claude Code por
  memoria critica de Windows (no por el lote); quedo ERROR. Probable causa de los "process pool terminated"
  de antes: la PC se queda sin memoria (otras sesiones) y se lleva al trabajador. Al cortar habia 1.8 GB
  libres: no se lanzo nada mas. Pendiente: func_8002D170 sola cuando haya memoria, y mas capturas con
  `scripts/capt_sin.py` (lo que mas rindio: partir del `arranque`).
- 02-10 madrugada: func_8002D170 queda PENDIENTE (en el lote se muere por memoria; sola da IGUAL).
  Capturas: el arranque y los menus ya no dan mas (2 y 2). Lo que rinde ahora es `scripts/capt_paseo.py`:
  pone a Sabrina en una cuadricula de puntos de cada nivel (escribe x y z) y espera, asi se activan los
  objetos de todo el nivel. Niveles 0 a 5: 56 funciones nuevas. Se colgo una vez en el nivel 6 (el juego
  deja de avanzar): ahora la espera tiene tope y se corre de a un nivel.

### Cierre del 02-10 madrugada (Meme apaga la PC)

- El lote de a una sobre las 57 del paseo (`notas/fases/tanda137/las_del_paseo.txt`) TERMINO: resultados en
  progreso.tsv. Muchas dieron NO_COMPILA solo porque el borrador no conocia p_sabrina: auto.py ahora pone
  `#include "objeto.h"` cuando el borrador usa p_sabrina (03199d9). PENDIENTE: repetir de a una las 36 de
  `notas/fases/tanda137/psabrina_repetir.txt` (las ya escritas a mano saldran YA_HECHA).
- Escrito a mano y SIN VERIFICAR (no estan en auditoria.tsv): `objetos/enemigo_g13.c` func_8002E51C (tercera
  clase de enemigo), `objetos/enemigo2_g13.c` func_8003D5F4, func_80045CF4, func_8002E030, func_80034710.
- Paseo (`scripts/capt_paseo.py`): niveles 0 a 6 hechos; FALTAN los niveles 7 a 14 (de a uno:
  `py capt_paseo.py lista.txt 7 8 40`, la lista = SIN_CAPTURAS de progreso.tsv sin .regs).
- func_8002D170 sigue pendiente (se muere por memoria en el lote; sola da IGUAL).
- 02-10 manana: las 36 de p_sabrina repetidas (2 IGUAL, 4 IGUAL_V0, 6 DISTINTO, resto YA_HECHA).
  Enemigos verificados: func_80034710 IGUAL; func_8002E030, func_8003D5F4, func_80045CF4 IGUAL_V0;
  func_8002E51C DISTINTO por la tabla de saltos. Paseo 6 a 14: casi nada nuevo (5 funciones; el nivel 9 con
  paso 4 dio 2). Las 327 que siguen sin capturas no aparecen paseando: hara falta jugar de verdad o
  provocar los objetos de otra forma.
- Truco: una funcion que toma la direccion de sus argumentos para usarlos como vector (func_8001C390,
  func_8004DB6C) se escribe variadica (`s32 f(s32 x, ...)` + `__builtin_va_start`): asi GCC deja los
  argumentos seguidos en su lugar de la pila del que llama, como el original.
- 02-10 mediodia: a mano IGUAL func_80054894, func_80048DC0, func_8001C390, func_8004DB6C, func_80048104,
  func_80052784; IGUAL_V0 func_80049A28, func_80049BD0, func_800496E4, func_8004951C (estados de enemigo:
  m2c ponia el vector en variables sueltas, va en un arreglo; las comparaciones son con signo),
  func_800528AC (remolino) y func_80054C5C (pieza de hechizo). Ojo con m2c: en un switch sin default puede
  cortar donde el original sigue (func_80054C5C, nivel sin jefe).
- 02-10 tarde: IGUAL func_800573C0 (caja de una ruta), func_80057800, func_80020294 (triangulos con el
  GTE; el struct del triangulo mide 0x1C, ojo con el relleno), SetGeomOffset y SetGeomScreen. Lo que queda
  sin IGUAL del lote es casi todo del CD (8002A-8002F, 80017D80, 8005D50C), asm puro (setjmp, parche de la
  BIOS, InitGeom 800177B4), BuclePrincipal (no termina) y las NO_TERMINA. Siguiente: mas capturas (hay 322
  sin capturas; el paseo ya rinde poco, probar a jugar de verdad con recorridos por nivel).
- 02-10 tarde: func_8002D170 sola volvio a morir (ERROR) con la memoria de Windows en 1.8 GB: queda pendiente,
  no insistir hasta tener la PC libre. El paseo con --acciones no saco nada nuevo (322 sin capturas).
  Idea para seguir (sin probar, consultar antes): para funciones puras sin capturas, usar como captura la
  RAM de otra funcion del mismo momento y variar los argumentos; el verificador compara original y C igual.
- 02-10: CAPTURAS SINTETICAS aprobadas: ver `notas/fases/2026-10-02_capturas_sinteticas.md`. Herramienta
  `decomp/sint.py`, resultados en `decomp/progreso_sint.tsv` (IGUAL_SINT), capturas en `capturas_sint/`.
- 02-10 noche: mutantes de las 5 sinteticas mas grandes: func_80060170 12/12, func_8003C528 11/12,
  func_80039EBC 8/12, func_80039DD0 7/12, func_80053038 4/12 (la captura sintetica ejercita un solo camino;
  en esas el IGUAL_SINT vale poco). Antes: func_80026DB0 8/8.
- 02-10 noche: arreglos de fondo en el borrador. (1) m2c definia los punteros a funcion del juego como
  `static ... = NULL` y el C saltaba a 0: ahora van extern (auto.limpiar) y verificar rechaza cualquier
  D_XXXXXXXX definido en el C. (2) Prototipo corto con `f(s32 arg2)`: se agregan arg0/arg1 delante
  (auto.rellenar_parametros). (3) Las cadenas de los datos van a m2c como bytes: antes salia "texto" y el C
  pasaba otra direccion. (4) aridad.py tenia un \b convertido en caracter de retroceso y no respetaba
  tipos_conocidos.h; arreglado. Los trampolines (func_80016970 y otros que llaman por puntero sin tocar
  a0-a3) toman la aridad de lo que escriben sus llamadores. (5) juego.h trae SUMA_TRAMPA/RESTA_TRAMPA para
  el add/sub con desborde que el original usa a mano.
- 02-10 noche: 15 a mano IGUAL_SINT/IGUAL_V0_SINT en auditoria.tsv (archivos nuevos src/varios/sueltas_g13.c,
  src/objetos/listas_g13.c, src/sabrina/vida_g13.c). func_8003E9FC: la captura sintetica es invalida (la
  original tambien revienta); func_80012F2C (MoveImage) no termina en el emulador. func_80052114 es un trozo
  de codigo que se copia a 0xDF80 (no es funcion de C).
- 02-10 noche: IGUAL_V0 del lote pasadas a IGUAL a mano (el C devuelve el v0 de cada camino; si el
  original deja en v0 la direccion de su tabla de casos, se devuelve esa constante). Hechas ~30 (menus,
  orden de GPU, camara, mando, arranques por grupo de niveles, maquina de estados de enemigos con `paso`).
  Quedan del lote: func_8004A4A8 (1596 bytes) y func_80046EAC (v0 de entrada, no se puede en C).
  func_800211D4 (barra) tarda mas de 15 min en verificarse: probar sola con mas tiempo.
- Lote sintetico ampliado (`sint_lote2.sh`, de a una con tope de 10 min cada una; log
  build/sint_lote_b1.txt). Las de copiar codigo a la BIOS (func_800521AC, func_80052240, func_800523B4) son
  asm puro: no van.
- WSL: lanzar con `scratchpad/fondo.sh script salida` (setsid nohup + confirma que arranco) y vigilar
  con `wsl.exe` (si nadie llama a wsl.exe la VM se apaga y mata lo suelto).
- 02-10 noche (sigue): con capturas sinteticas a mano IGUAL_SINT ~50 (auditoria.tsv, estado *_SINT);
  archivos nuevos src/objetos/agarrable_g13.c, anacronico_g13.c, jefe_golpes_g13.c, src/Screen/buferes_g13.c,
  barra_g13.c, fondo_g13.c, src/audio/cd_musica_g13.c, secuencia_g13.c, src/libgpu/paletas_vram_g13.c.
  Pendiente de verificar: scratchpad lanzar_vmano7.sh (func_80039350, func_80026820) y lanzar_vreal5.sh
  (las TOPE_DE_TIEMPO de auditoria otra vez con 15 min, mas func_8004A4A8 y diagnosticos de DISTINTO).
  Despues: relote real con el auto mejorado (`de_a_una2.sh build/rehacer_reales.txt`) y el lote sintetico
  b2 (`sint_lote2.sh build/sint_lote_b2.txt --tope 0x800 --llamadas 8 --globales 20`).
