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
- 02-10, CIERRE (Meme apaga): todo parado a mano. Pendiente al retomar (scripts en el scratchpad de la
  sesion; si se perdio, rehacerlos con vmano.sh = vsint.sh por funcion y vreal.sh = vfull.sh por funcion):
  1. Verificar con capturas sinteticas las ~34 de lanzar_vmano8.sh (C a mano con su v0, ya en src/:
     sueltas_g13, listas_g13, agarrable_g13, mando_g13, secuencia_g13, tempo_g13, vida_g13) y anotarlas
     IGUAL_SINT en auditoria.tsv.
  2. Verificar con capturas reales lanzar_vreal6.sh (func_800123E0, func_80022614, func_80022918,
     func_8002805C, las maquinas func_8003D5F4/80045CF4/80057CA0/8004A140 con el v0 de la distancia,
     func_80025EF8 con a1, func_80037738, func_80023FD4 nueva en fondo_g13.c) y diagnosticos de
     func_8002367C, func_80054068, func_8002E51C, func_8004B320, func_800447E4.
  3. La tanda vreal5 quedo cortada en ArchivoLeer: faltan las TOPE_DE_TIEMPO de auditoria (con 15 min).
  4. Relanzar el lote sintetico b2 (sint_lote2.sh build/sint_lote_b2.txt --tope 0x800 --llamadas 8
     --globales 20 --gte); solo hizo 1 de 45.
  No arreglables en C: func_800163E4 (setjmp guarda ra/sp), func_8002153C y func_8003E914/8003E0C4 (la
  captura revienta en la original), func_80046EAC/80047058/8004CA4C/80048908 (v0 de entrada).

### 02-10 noche, sesion sola sin agentes (Meme: "continua descompilando, no pares")

- **Los scripts de verificacion ya viven en el repo**: `decomp/verif/` (antes en el scratchpad de cada sesion,
  se perdian). `vfull.sh src f` (capturas reales) y `vsint.sh src f` (sinteticas) muestran tambien los
  ejemplos de variantes malas, incluso cuando solo difiere v0; `vvarias.sh [--sint] src f1 f2...` varias de un
  mismo .c; `vreal.sh`/`vmano.sh log src:f ...` en tanda con tope `$TOPE`; `fondo.sh script salida` lanza
  suelto; `termina.sh f...` y `donde_gira.sh f...` dicen si la original termina y donde gira;
  `py verif/cuenta.py [--pendientes]` da el % (reales y sinteticas aparte) y la lista de lo que falta;
  `py verif/anotar.py log [--sint]` pasa un log a auditoria.tsv sin reordenarla ni bajar un IGUAL.
- Ojo: `wsl.exe ... bash -c '...$f...'` expande `$f` en el shell de afuera; usar un script (vvarias.sh).
  Y no editar un .sh mientras corre: bash lo lee a medida que avanza y se rompe.
- **verificar.py**: si una palabra de memoria que se varia es un puntero a una funcion del juego, la
  variante solo puede ser otra funcion o 0 (`_puntero_a_funcion`): saltar a la mitad de otro codigo no lo
  imita ningun C. Con eso func_80025EF8 paso a IGUAL.
- Resultados: vreal6 dio IGUAL func_8004B320 (2688), func_80054068, func_8002367C, func_800447E4,
  func_8002805C, func_8003D5F4, func_80057CA0, func_8004A140; IGUAL_V0 func_8002E51C y func_80037738.
  vmano8: 33 IGUAL_SINT (func_80026C18 con volatile: escribe en el hardware en orden).
  func_80045CF4 a IGUAL: en el caso 1 de `paso()` (enemigo2_g13.c) se llama a func_80048908 con v0 = la
  direccion del caso, porque esa funcion a veces vuelve sin tocar v0.
- Escritas: `psyq/cdsync_g14.c` (CdSync y CdReady, la original termina) y `modelLoader/leer_nodo_g14.c`
  (LeerNodoModelo, NO_TERMINA: lee del CD).
- **verificar.py, registros de hardware como MMIO** (03-10): Unicorn tiene un fallo con el gancho de
  escritura: un sw/sh al hardware en el hueco de retardo de un salto hace saltar a 0 (la original daba error
  en func_8003E914 y func_8003E0C4 y el C no). Ahora 0x1F801000-0x1F803000 es `mmio_map`: cada escritura
  se anota en hw (en orden) y se puede releer. Probado: esas dos a IGUAL, func_80025EF8/80029ED4/800283C4
  siguen IGUAL y la version sin volatile de func_80026C18 sigue dando DISTINTO (detecta el orden).
- **verificar.py, tope de tiempo en variantes**: la original de una variante tiene 40 veces lo que tardo en
  la captura mas lenta (minimo 3 s); si lo pasa, la variante se descarta como las que dan error. Asi
  CdSync/CdReady terminaron (antes cada variante que la hacia girar gastaba 20 millones de instrucciones).
- **sint.py crear_con F a0=..,a1=.. [--en 0]**: captura sintetica con argumentos elegidos (anotados en
  NN.MANO) cuando los de la donante no tienen sentido (func_8001A228 con un ancho de 0x1F8010F4 giraba).
- Ideas SIN aprobar (cambian el metodo; preguntar a Meme): (1) GPU desocupada: GPUSTAT (0x1F801814) siempre
  "lista" destraba DrawSync/LoadImage/StoreImage/MoveImage/DrawOTag y 3 mas (`verif/prueba_gpu.py`); 8 que
  usan la cola del GPU saltan a 0 despues (falta ver por que). (2) VSync: 13 NO_TERMINA giran esperando el
  contador de cuadros. (3) BIOS de archivos: lseek/read/write vuelven sin poner v0 (func_800502DC).
  `verif/donde_gira.sh` dice en que funcion gira cada NO_TERMINA: CD 16, VSync 13, GPU 11.
- **03-10 madrugada, resultados**: reales 64.8 %, sinteticas 16.3 % (81.2 % entre las dos). A mano en esta
  sesion (archivos `*_g14.c`): CrearParticula (952, real, estaba solo declarada), CdSync/CdReady (reales),
  y con sinteticas: tarjeta (escritura comprobada y formateo), menus de nivel y mundo, DRAWENV, rayo y el
  objeto que lanza rayos, proyectil, tirador, saltarin, fuente de chispas, atrapar objetos, lanzado hacia
  Sabrina, reduccion de colores a paleta (func_8001A754, 1668), voltear imagen, glifos de la fuente, lugar
  en la VRAM. Con el verificador nuevo pasaron solas func_80023FD4 (IGUAL), func_80030208 (IGUAL_V0),
  func_80025EF8, func_8003E914/8003E0C4 y varias TOPE_DE_TIEMPO.
- Trampa de los borradores de m2c que se repite: cuando una funcion llamada escribe un vector de 3 en
  `&sp5C`, m2c declara sp5C, sp60, sp64 como variables sueltas y el C pasa basura; va en un arreglo.
- Trampa de GCC: guarda variables en el lugar de un argumento de pila (la pila del que llama) cuando junta
  ramas o reusa el hogar del parametro; el original no toca esa pila. Se corta con `__asm__("" : "+r"(x))`
  y separando ramas con `__asm__ volatile("" ::: "memory")` (CrearParticula).
- Mutantes (`verif/lanzar_mut1.sh`, `lanzar_mut2.sh`): func_8004B320 7/8 muertos (fuerte); func_80054068
  3/8 (debil: las capturas no recorren varias ramas). Resultados en build/mut1.txt y mut2.txt.
- Quedan sin verificar casi solo: las que esperan al CD/VSync/GPU (NO_TERMINA), las herramientas de
  desarrollo que leen archivos, y 37 sin capturas (BIOS, trozos de codigo, archivos). `verif/lanzar_cqt.sh`
  mide si alguna NO_TERMINA termina en otra captura que no sea la primera.
- **verificar.py, 03-10**: (1) una captura en la que la original no termina se descarta (como una variante
  que da error); NO_TERMINA solo si no termina en ninguna. (2) Topes por INSTRUCCIONES, no por tiempo: la
  original de cada captura se mide por escalones (`ESCALONES`) y las variantes tienen 16 veces ese escalon;
  la cantidad de variantes tambien depende del escalon. Antes dependia de lo cargada que estaba la PC (la
  misma funcion daba 114, 104 o 34 variantes segun la carga); ahora siempre da lo mismo.
- **Propuesta VSync (sin aplicar, para Meme)**: VSync (func_8001626C) espera en func_800161D4 a que el
  contador de cuadros D_800649EC (lo sube la interrupcion de VBlank) llegue a un objetivo. Modelo minimo y
  determinista: un gancho en la entrada de func_800161D4 que ponga D_800649EC = max(D_800649EC, a0) y vuelva
  (como las llamadas a la BIOS). Original y C llaman a la misma VSync, asi que ven lo mismo. Con GPUSTAT
  "desocupado" (bit 22 en 0) la espera del campo entrelazado no se activa. Destrabaria ~13 NO_TERMINA.
  Igual que el de GPU, iria con estado aparte (_VS) hasta que Meme lo apruebe.
- Con capturas a mano por estado (`verif/capturas_8003C9DC.sh`, `capturas_8003B57C.sh`) los mutantes
  muertos subieron: func_8003C9DC de 4/8 a 6/8, func_8003B57C de 2/8 a 6/8 (los vivos son `<` por `<=` en
  bordes y constantes que no cambian el resultado en esos datos).
- Repaso de mutantes de las sinteticas grandes (`build/mut3.txt`, anotado en auditoria.tsv como "mutantes
  muertos N/6"). Debiles (0-1 de 6): func_80026820 (mando), func_80052578 (formatear tarjeta) y, del lote,
  func_8001CB4C y func_80026ECC: dependen del hardware o de leer archivos, que el emulador no simula; para
  hacerlas fuertes hace falta modelar ese hardware (mismo tema que GPU/VSync, decision de Meme).
- **03-10: Meme APROBO los modelos de GPU y VSync.** Prendidos por defecto en verificar.py (`MODELOS`;
  `SABRINA_SIN_MODELOS=1` los apaga). GPU: GPUSTAT siempre listo. VSync: cada llamada a func_8001626C
  hace pasar un cuadro y la espera func_800161D4 encuentra el contador en el objetivo. Las IGUAL_GPU
  anotadas pasaron a IGUAL/IGUAL_SINT (con nota). Tanda `verif/lanzar_vmodelos.sh` repite con los modelos
  las 74 NO_TERMINA/TOPE que tienen C (log build/vmodelos.txt; anotar con `py verif/anotar.py`).
- 03-10, modelos agregados en la misma linea (Meme: "no pares hasta terminar todo"): el control de cada canal de
  DMA dice "transferencia terminada" (destraba DrawSync y la cola del GPU) y el estado del puerto del mando
  (0x1F801044) dice listo/recibido/enviado. Lo que sigue girando: respuesta del CD, MDEC (video), la
  rutina de VBlank del juego (D_8007CAE6) y partes del protocolo del mando.

### TRASPASO 04-10 madrugada (EMPIEZA AQUI el chat siguiente)

**Estado: reales 73.4 % (658 fn) + sinteticas 16.9 % (289 fn) = 90.3 %.** Medir con `py decomp/verif/cuenta.py`
(desde `decomp`; `--pendientes` lista lo que falta). Todo commiteado y pusheado en main.

Modelos aprobados por Meme y prendidos en verificar.py: GPU desocupada, VSync (cada llamada pasa un cuadro),
DMA terminado al instante, puerto del mando listo. Capturas donde la original no termina se descartan; topes
por instrucciones (determinista).

**Siguiente, en orden:**
1. Tanda `verif/lanzar_v9.sh` (log `decomp/build/v9.txt`), PARADA a mano al cerrar en func_80019D80: relanzar desde ahi (func_80019D80, func_8002CF28,
   func_8002B2BC, func_80017D80, func_800189A4, CargarWRLDDATA (borradores de src/auto). Anotar con
   `py verif/anotar.py build/v9.txt`. Las que no compilan o den DISTINTO: escribir a mano (`*_g14.c`).
   func_8005D50C (824, el reproductor de video) no compila: escribirla a mano (ya terminan con los modelos).
2. 27 NO_TERMINA con C siguen girando: respuesta del CD (func_8002AC18 adentro), MDEC/video (func_8005DADC),
   la rutina de VBlank del juego (D_8007CAE6, func_800218D4/80021B4C/800219F8) y partes del mando
   (func_8002643C). Un modelo de "VSyncCallback" (llamar a la funcion registrada en cada cuadro) destrabaria
   las de VBlank; el del CD es mas dificil (respuestas del controlador).
3. 34 SIN_CAPTURAS: herramientas de desarrollo que leen archivos, BIOS, asm puro; pocas se pueden.
4. Sinteticas debiles segun mutantes (auditoria.tsv "mutantes muertos"): func_80026820, func_80052578,
   func_8001CB4C, func_80026ECC dependen del hardware; ahora con el modelo del mando podrian mejorar.
5. Meme dejo `C:\esp` (proyecto ESP32) por si algo sirve para ganar velocidad: revisar.

Trampas de esta sesion (repetidas): m2c pone sp5C/sp60/sp64 sueltos donde va un vector o un RECT (usar
arreglo); borradores viejos definen punteros a funcion como `static = NULL`; heredoc pierde `\` (usar
Write o 0x5C); `wsl.exe bash -c '$f'` expande afuera (usar scripts); Claude Code mata procesos de fondo si
la memoria de Windows baja (Bambu Studio, Edge y otros node se la comen); lanzar con `verif/fondo.sh`.

### 04-10 manana (sesion sola, Meme: "tu mandas, te doy la aprobacion de todo")

- **Tanda v9**: la vieja NO estaba parada; termino sin resultado en func_80019D80 (la actualizacion de cada
  cuadro: TOPE, es lentisima de emular). WSL: el distro por defecto ahora es docker-desktop, lanzar con
  `wsl.exe -d Ubuntu-24.04 ...` y, desde Git Bash, `MSYS_NO_PATHCONV=1`.
- **Escritas a mano (047d651)**: func_8005D50C reproductor de video (Screen/video_reproductor_g14.c),
  func_8002D714 lectura de video por CD y func_8002D56C arranque del DMA (psyq/cd_stream_g14.c),
  func_8002CF28 CdPlay y func_8002B2BC CD_init (psyq/cd_play_g14.c), func_800275F8 envio al mando
  (psyq/mando_envio_g14.c), func_80017BC0 parche de la BIOS (psyq/parche_bios_g14.c, GetC0Table con asm),
  func_80051024 directorio de la tarjeta (varios/tarjeta_dir_g14.c), func_80017D80 cargar archivo entero
  (File/archivo_entero_g14.c), las 6 cargas de animaciones (varios/animaciones_g14.c, generadas del asm).
  func_80016170 es setjmp: asm puro.
- **Modelos nuevos en verificar.py, prendidos por defecto** (aprobados por Meme 04-10):
  - VBlank: en cada llamada a VSync corre la rutina de VBlank del juego (func_80016A2C), que sube el contador
    y llama a las funciones de VSyncCallback (la barra de carga). En la pila de interrupciones y guardando
    todos los registros. `SABRINA_SIN_VBLANK=1` lo apaga.
  - CD: `decomp/modelo_cd.py` imita el controlador del CD (ordenes, acuse INT3, respuesta INT2, sectores INT1
    sacados del .bin del disco, DMA del canal 3). El acuse queda pendiente al dar la orden; lo demas se
    entrega en la proxima VSync corriendo la rutina del CD de libcd (func_8002A5F8). El modo del CD se toma
    de la copia de libcd en RAM (D_8006D320). `SABRINA_SIN_CD=1` lo apaga.
    `verif/traza_cd.sh F [n]` muestra donde queda la original y el dialogo con el CD (o=orden, I=respuesta
    de la cola, S=sector, v=VSync con la interrupcion pendiente).
  Con eso terminan CargarArchivoEntero, CargarANI, CargarINO, func_80019CC4, func_8003E0B4, func_8002CEB4,
  func_800219F8 (antes NO_TERMINA). Tanda `verif/lanzar_cd1.sh` (log build/cd1.txt): las 45 NO_TERMINA y
  las escritas a mano, de chica a grande.
  - Arreglos del modelo del CD: arranca en la posicion de la ultima Setloc de libcd (D_8006D31C) y, si piden
    un sector (request 0x80) sin haber leido, da el de esa posicion (en la consola ya estaba listo al
    capturar; si no, func_8002D714 giraba esperando datos).
  - MDEC (04-10): el estado (0x1F801824) dice siempre desocupado y sin datos de salida (0x80040000). No
    decodifica: los DMA 0/1 terminan sin copiar, igual en original y C.
  - Mas modelos 04-10 (en verificar.py, con MODELOS): I_STAT con el bit 7 (ACK del mando) y el contador 2
    que avanza 0x40 por lectura (las esperas con tiempo de libpad); el 0 y el 1 quietos porque VSync lee el 1
    hasta que dos lecturas coincidan (con los tres avanzando, VSync giraba para siempre). GetC0Table devuelve
    una tabla C0 del modelo en 0x81000000 (la BIOS de las capturas no tiene el kernel de Sony en la RAM).
    Las interrupciones del CD tambien llegan al entrar a StGetNext (el juego la llama en un bucle sin VSync).
    Con eso terminan las del mando (func_8002643C, 80027488, 800273B0, 80027534), func_8005C9D0,
    func_800218D4, func_80025A10.
  - Falta para el video (ReproducirSTR, func_8005D50C, PantallasLegales, func_8005CEBC): el video corre y
    llegan los sectores, pero los cuadros se consumen en la interrupcion de fin de DMA (libetc,
    func_80016B4C, DICR 0x1F8010F4 y las funciones de D_800649F4). Modelar: al arrancar un DMA con su
    interrupcion habilitada en DICR, marcar el bit 24+n y entregar func_80016B4C en el proximo punto.
  - Ojo: no editar verificar.py mientras corre una tanda (cada vfull lo importa de nuevo); editar una copia y
    cambiarla con mv. Una tanda (cd3) quedo con resultados rotos por eso y se repitio entera (cd4).
  - DICR (0x1F8010F4) como en la consola: banderas de fin de DMA que se borran escribiendo 1, puestas al
    arrancar un DMA con su interrupcion habilitada; el estado inicial se arma con los canales que tienen
    funcion en D_800649F4; la rutina de libetc func_80016B4C se entrega en los mismos puntos que el CD.
    Y si la ultima orden de libcd (D_8006D321) fue ReadN/ReadS, el modelo arranca leyendo: func_8005CEBC
    termina. `verif/histo.sh F [instrucciones]` cuenta bloques por funcion (donde se va el tiempo).
  - NO se puede: el reproductor de video (ReproducirSTR, func_8005D50C) decodifica de verdad cada cuadro
    (DecDCTvlc2, millones de instrucciones por cuadro): un video entero no cabe en 20 M instrucciones.
  - Propuesta (no hecha): interrupciones de VBlank "por tiempo" solo cuando una corrida pasa de ~2 M
    instrucciones sin volver (cada 100 mil), para los bucles que esperan un contador que sube en VBlank sin
    llamar a nada (func_800218D4 espera D_8007CAE6, func_80021B4C). Ojo con parar en un hueco de retardo.
  - Limite de C (04-10): CargarANI, CargarWRLDDATA (y quiza CargarSonidoNivel) dan DISTINTO solo en
    variantes con el nombre del archivo roto: ArchivoCerrar imprime "Deleting file %s" con un puntero sin
    inicializar de la estructura del archivo (basura de la pila). El original guarda los registros DEBAJO de
    los locales y la estructura llega al tope del marco, donde GCC guarda ra: no hay forma de igualar la
    basura en C. CargarINO paso porque su marco coincide. `verif/marcos.sh archivo.c f...` compara marcos.
    Para func_8002FE64 bastaba no tener CargarANI en el mismo archivo (GCC la metia adentro).

### TRASPASO 04-10 manana (EMPIEZA AQUI el chat siguiente si este se corta)

**Estado al escribir esto: reales 74.3 % + sinteticas 16.9 % = 91.1 %** (sube con lo que anoten las tandas).
Tandas encadenadas corriendo solas en WSL (cada una espera el FIN de la anterior, `verif/cadena.sh`):
cd4 (build/cd4.txt) -> cd5 -> sintcd (sinteticas que no terminaban, ahora con modelos) -> cd6 -> sint2.
Al terminar: `py verif/anotar.py build/cdN.txt` (y `--sint` para sintcd.txt y sint2.txt), cuenta.py, commit.
Si se cortaron (la PC se apago), relanzar desde la que no tiene FIN con `verif/fondo.sh verif/lanzar_X.sh`.
Escritas a mano en esta sesion y en esas tandas: cargar_ino, wrlddata, sonido_nivel, cd_datasync,
mover_imagen, tabla_corrida, mando_cuadro, parche_bios (InitGeom), cd_stream_aviso (todas *_g14.c).
Lo que queda sin salida conocida: video entero (DecDCTvlc2), basura de pila en cargas con nombre roto,
tarjeta de memoria (func_80051298: falta modelo de la tarjeta), func_80018218 (montón lleno en la captura),
setjmp, BuclePrincipal, herramientas que leen del PC.
  - Mas limites (04-10): InitGeom (func_800177B4) guarda en memoria la direccion de retorno del parche de la
    BIOS (D_80084CD0): apunta al codigo, distinto en C. func_8002D714 copia 4 bytes sin inicializar de su
    pila (si D_80091478 != 0) y el marco de GCC es otro (0x68 contra 0x40). func_8002153C: la captura rompe
    la original (salta a 0). La pila de interrupciones del modelo se restaura al volver (guardaba registros
    del codigo interrumpido, distintos en C).
  - 04-10 mediodia: 76.1 % reales + 16.9 % sinteticas = 93.0 %.

### CIERRE 04-10 tarde (EMPIEZA AQUI)

**Reales 77.4 % (692 fn) + sinteticas 17.4 % (298 fn) = 94.8 %.** Todas las tandas terminaron y estan
anotadas (cd4, cd5, sintcd, cd6a, cd6, sint2). Todo pusheado en main.
Hoy pasaron a IGUAL, entre otras: func_8005C9D0 y func_8005CEBC (video), func_800275F8, func_8002643C,
func_80025A10, func_80027488/534/3B0 (mando), func_8002D56C, func_8002CB00, CdPlay, CD_init, CargarINO,
CargarSonidoNivel, CargarArchivoEntero, las 7 cargas de animaciones, el directorio de la tarjeta,
func_80017BC0, func_800218D4, func_80021B4C, func_8005D26C, func_8005D8D0, func_8005DCA0; y 9 sinteticas.
Lo que queda (ver lista con `py verif/cuenta.py --pendientes`) es casi todo limite conocido:
- basura de pila en el tope del marco (el original guarda registros debajo de los locales): func_8002D714,
  func_80017D80, func_800189A4, CargarANI, CargarWRLDDATA, func_8001B000, func_8004EBD0 (bufer de pila en
  la cola del GPU), InitGeom (ra guardado en memoria);
- video entero (DecDCTvlc2): func_8005D50C, ReproducirSTR; PantallasLegales espera muchos cuadros o un boton;
- tarjeta de memoria (func_80051298, func_800522E4): faltaria un modelo de la tarjeta;
- herramientas que leen del PC (SIN_CAPTURAS), BIOS/asm (setjmp, BuclePrincipal, func_800521AC...);
- func_8003E9FC: la captura sintetica tiene el puntero en 0 (haria falta una con D_80074EBC valido).
Ideas si se quiere seguir: modelo de la tarjeta de memoria; capturas sinteticas con globales elegidas.
- **Limpieza 04-10 (Meme lo pidio):** borrados `decomp/build/ctx` (2.1 GB, contextos de m2c: se rehacen solos
  con auto.py si hacen falta), `disco.zip` (copia de `disco/`), `herramientas/_zip` (los zips ya
  descomprimidos; arrancar.ps1 los vuelve a bajar solo si falta una herramienta), los logs de las tandas
  (`decomp/build/*.txt`, ya anotados en auditoria.tsv) y los `decomp/tmp_*`. No se toco: capturas,
  capturas_sint, disco/ (con las versiones del mod), extraido, estados, herramientas instaladas.

### CIERRE FINAL 04-10 noche (EMPIEZA AQUI)

**Reales 77.6 % + sinteticas 17.4 % = 95.0 %** (`py decomp/verif/cuenta.py`). Todo pusheado en main.
Despues del cierre de la tarde:
- `SABRINA_LIMITE` (tope de instrucciones por corrida, defecto 20 M) para las funciones largas. Con 300 M y
  6 variantes func_80019D80 (la actualizacion de cada cuadro, 572 bytes) dio IGUAL (`verif/lanzar_largas.sh`).
- func_8003E9FC IGUAL_SINT con capturas sinteticas armadas a mano (`verif/capturas_8003E9FC.sh`, usa
  `sint.py crear_con` con datos en la RAM: el puntero de la tabla valido).
- **PENDIENTE (parado a mano por Meme):** `verif/lanzar_largas2.sh` verifica la PantallasLegales nueva
  (`src/Screen/pantallas_legales_g14.c`), escrita con el marco de pila del original (0xB8): las funciones
  que llama copian bytes sin inicializar de la pila, y con el marco de GCC (0xD8) la basura cambiaba (la
  version de video_g13.c dio DISTINTO solo por eso, en D_8006D31C). Truco para bajar el marco: armar las
  direcciones de las globales y las constantes del bucle con asm volatile (`DIR`, `CUATRO`) para que GCC no
  las guarde en registros. Lanzar con `verif/fondo.sh verif/lanzar_largas2.sh build/largas2.out` (~1 h) y
  anotar con `py verif/anotar.py build/largas2.txt`. El mismo truco puede servir para otras cuyas llamadas
  leen basura de pila (no para las que la leen en su propio marco).
- func_800522E4 (InitCARD): limite, func_800521AC guarda la direccion de retorno en memoria.
- Las SIN_CAPTURAS chicas que quedan (func_800294F0, 80029518, 80029530, 80052114/40/84, 800161C8) son asm
  puro o llamadas al PC de desarrollo (break de PCdrv): no van a C.

### 04-10, ULTIMA SESION (EMPIEZA AQUI)

**Reales 78.8 % + sinteticas 17.5 % = 96.4 %** (`py decomp/verif/cuenta.py`). Pasaron:
- PantallasLegales IGUAL (la tanda `verif/lanzar_largas2.sh` que quedo pendiente, 1 h 40 min).
- func_8002D714 IGUAL_V0 (2332 bytes, la mas grande que quedaba), func_800189A4 IGUAL, CargarANI IGUAL,
  CargarWRLDDATA IGUAL, func_8004EBD0 IGUAL_SINT (nuevo `src/varios/tarjeta_iconos_g15.c`).

**El truco: marco a mano para la basura de pila** (como CrearRecogible en `objetos/crear_g13.c`). El original
deja bytes sin llenar en su marco (un CdlLOC de 3 bytes en 4, una paleta sin llenar, el archivo y la ruta
que lee ArchivoAbrir) y los copia. La funcion pasa a ser un stub con asm que arma el marco del tamano del
original y llama a un cuerpo en C (`static`, `noinline, used`) con punteros a los lugares de la pila del
original (`addiu $aN, $sp, off`, sacados del asm). Detalles:
- `__attribute__((naked))` va en SU PROPIA LINEA: verificar.py busca `void` al principio de la linea de la
  definicion (es_void); con el atributo delante no la ve como void y compara v0 (func_8002D714 daba DISTINTO
  solo por v0). GCC avisa que ignora naked en MIPS: no importa, la funcion solo tiene el asm.
- Si ademas las funciones que llama leen basura de SU pila (func_80017D80: CdSearchFile deja D_8006D31C
  distinto), el cuerpo tiene que quedar con el sp del original: stub de (marco original - marco del
  cuerpo) y ra en una palabra que el original no usa. Ver func_80017D80 en `File/archivo_entero_g14.c`.
  func_80017D80 quedo asi en 687 de 689 (antes 610): en las 2 que faltan `nombre` apunta a la pila y la
  cadena cruza la unica palabra libre del marco (sp+0x28, donde el stub guarda ra), y printf no termina ni
  con 300 M. No hay otro lugar libre: limite.
- Con 4 argumentos ocupados se aprovecha uno que la funcion no usa (CargarANI: a0) o se calcula un puntero
  desde otro (ruta + 0x80).

Lo que queda (`py verif/cuenta.py --pendientes`), todo limite conocido: herramientas de desarrollo de
texturas TGA que no estan en el disco (func_8001B0C8/B698/B9C0, Herramienta*, func_8001B000 su cache,
func_80018CB8, func_80024450) y PCdrv; video (func_8005D50C, ReproducirSTR); tarjeta (func_80051298,
func_8004F50C, func_800522E4); InitGeom (ra en memoria); setjmp/BuclePrincipal; func_8002153C (la captura
rompe la original); func_80018218 (monton lleno).

### 04-10 NOCHE, PARADO A MANO PARA ACTUALIZAR LA PC (EMPIEZA AQUI)

**Reales 79.3 % + sinteticas 17.9 % = 97.2 %** (`py decomp/verif/cuenta.py`). Pasaron esta noche:
func_80018218 y func_8002153C IGUAL (malloc de la BIOS), func_80051298 IGUAL (tarjeta), func_8004F50C
IGUAL_V0_SINT, func_8001B000 IGUAL_SINT, func_8001B9C0 IGUAL_SINT (fuente). D_800609B0 salio de la cuenta (es
una tabla de datos, no codigo). func_80017D80 queda en 687/689: limite real (con nombre apuntando al codigo
CdSearchFile desborda su pila y pisa registros guardados; el original y GCC guardan variables distintas ahi).

**Modelos nuevos en verificar.py / modelo_cd.py** (documentados en el encabezado de cada uno):
- malloc/free de la BIOS (MALLOC, zona MONTON_BIOS aparte y comparada);
- tarjeta de memoria (TARJETA: tarjeta en blanco, _card_read/_card_write/_card_status, eventos IOE, y un cuadro
  de VBlank cuando el juego espera el aviso D_800D52C8);
- PCdrv (PCDRV: ganchos en los break de func_800294F0/80029518/80029530; lo escrito a la PC se compara);
- archivos de la PC de desarrollo: CdSearchFile de un .TGA en GRAPHICS\TARGA|SPRITE|PICTURES|FONT da un archivo
  virtual (modelo_cd.archivo_virtual, 16x16; las fuentes 24x32 con 4 letras) servido despues del final del disco;
- CD: si el juego consulta el lector sin VSync y hay respuesta en cola, llega a las 64 consultas
  (ESPERA_DIRECTA; el Pause desde dentro de la interrupcion al terminar CdRead).

**PENDIENTE, en este orden** (todo escrito, original y C ya comparados iguales a mano con dbg; falta la tanda
con variantes, que se corto). Lanzar de a una con `verif/fondo.sh verif/lanzar_X.sh build/X.out` y anotar con
`py verif/anotar.py build/X.txt --sint`:
1. `lanzar_tga1.sh` func_8001B0C8 (`src/varios/textura_tga_g15.c`, capturas_sint con 00 y 01 hechas a mano);
2. `lanzar_tga2.sh` func_8001B698 (`textura_sprite_g15.c`);
3. `lanzar_tga4.sh` func_80018CB8 (`fuente_a_pc_g15.c`, solo difiere v0: deberia dar IGUAL_V0);
4. `lanzar_tga5.sh` func_80024450 (reescrita en `herramienta_tex_g14.c` con el marco del original);
5. HerramientaConvertirPIC (`src/varios/convertir_pic_g15.c`) escrita y con captura (a0 = "LEGAL.PIC"), sin
   comparar todavia: el marco del cuerpo dio 0x28 (s0-s3) y tiene que ser 0x20; usar DIR() para las globales
   como en herramienta_tex_g14.c antes de probar.
Despues: HerramientaArmarModelos y HerramientaArmarCuadricula (leen GRAPHICS\ y escriben con PCdrv).
Trucos de esta noche: marco a mano con el cuerpo en el sp exacto del original (stub = marco original - marco
del cuerpo; locales con PILA(off)); el s3/s4 que trae el que llama se pasa desde el stub (`move $5, $19`),
porque leerlo con asm dentro del cuerpo falla si GCC ya uso ese registro.

### 04-10 TARDE-NOCHE, SESION SOLA (EMPIEZA AQUI)

**Reales 79.3 % + sinteticas 18.1 % = 97.4 %** antes de anotar la cadena de herramientas (`py decomp/verif/cuenta.py`).
Pasaron: func_8001B0C8 (lector de .TGA) IGUAL_SINT; func_800502DC (paso de lectura de la tarjeta), func_800521AC,
func_80052240 y func_800523B4 (parches de libcard a la BIOS) IGUAL_SINT.

**Modelos nuevos (encabezados de verificar.py y modelo_cd.py):**
- Sectores despues de los archivos virtuales: vacios pero con su cabecera. El lector sigue leyendo el sector de
  detras antes del Pause y libcd revisa la cabecera: con 00:00:00 daba "CdRead: sector error" y repetia cada
  lectura 600 veces (por eso las tandas de texturas tardaban tanto).
- .TNF, .bud y .XDX virtuales de GRAPHICS (HerramientaArmarModelos y HerramientaArmarCuadricula).
- open/lseek/read/write/close de la BIOS sobre archivos de la tarjeta ("bu00:"), asincronos como los usa libcard.
- GetB0Table (B0 0x57) y la pagina de las tablas de la BIOS se compara (antes no: ni el parche de func_80017BC0
  se veia; se reverifico y sigue IGUAL).

**Trampa nueva: la BIOS libre del emulador toca el juego.** OpenBIOS reconoce el parche de libcard en
func_80052240 y lo anula reescribiendo 3 palabras del codigo (80052260-6C: nop y un salto al final). Las capturas
traen esa RAM, asi que la "original" corria el codigo anulado. Su captura sintetica lleva restaurados los bytes del
ejecutable (00.MANO). Revisado: en esa RAM es la unica zona de codigo distinta del ejecutable.

**Truco nuevo:** cuando una funcion llamada lee un s-registro del que llama (func_8001B0C8 lee s4) y GCC no
respeta `register ... asm("$20")`, hacer la llamada con asm en linea que carga el registro antes del jal y lo
declara pisado (ver `src/varios/armar_modelos_g15.c`).

**PENDIENTE (corriendo en WSL al escribir esto, de a una):** `verif/lanzar_tga_todas.sh` = tga2, tga4, tga5, pic,
modelos y despues `lanzar_tras_modelos.sh` (cuadricula). Al terminar cada una: `py verif/anotar.py build/X.txt --sint`.
Si se cortaron, relanzar con `verif/fondo.sh verif/lanzar_tga_todas.sh build/tga_todas.out` (quitar tga1 de la
lista, ya esta anotada). Las 3 nuevas (PIC, modelos, cuadricula) ya dieron IGUAL sin variantes a mano.
La prueba de mutantes de func_800502DC se corto por falta de memoria en Windows (no se repitio).
Lo que queda despues es limite: video, BuclePrincipal, setjmp, InitCARD/InitGeom (ra dentro del C), func_80017D80,
trampolines de la BIOS en asm (func_800161BC/C8, func_800142FC) y el manejador de excepciones (func_80017B8C).

**CIERRE de esta sesion: reales 79.3 % + sinteticas 19.4 % = 98.7 % (1015 de 1034).** Toda la cadena anotada:
func_8001B0C8, func_8001B698, func_80018CB8, func_80024450, HerramientaConvertirPIC, HerramientaArmarModelos,
HerramientaArmarCuadricula y las 5 de la tarjeta, todas IGUAL_SINT.
- func_80018CB8 tenia un error real del C (8 bytes por letra en vez de 12): lo escondia la fuente virtual que llegaba
  rota antes del arreglo de los sectores.
- Otro arreglo de fondo: los archivos virtuales ahora son de cada corrida (`Cd.__init__` los borra). Quedaban de la
  corrida de la original y la del C encontraba con datos sectores que la original habia leido vacios (el lector lee
  por delante): func_80024450 daba DISTINTO en el grupo 1 solo por eso.
- Video confirmado como limite: func_8005D50C no termina ni con 1000 millones de instrucciones (22 min una corrida).
Lo que queda (`py verif/cuenta.py --pendientes`) es todo limite: video (func_8005D50C, ReproducirSTR),
BuclePrincipal (carga niveles enteros) y main (func_800106C8, no vuelve), ra guardado que cae dentro del C
(func_800163E4 setjmp, func_800177B4 InitGeom, func_800522E4 InitCARD), func_80017D80 (687/689), y asm puro:
trampolines de BIOS/PCdrv (func_800294F0/29518/29530, 800161BC/C8, 800142FC), func_80052114/40/84 (usan v1 del que
llama o son datos), func_80016170 (setjmp) y func_80017B8C (manejador de excepciones).

### 04-10 NOCHE, REPASO DE SINTETICAS DEBILES (EMPIEZA AQUI)

Se buscaron las IGUAL_SINT que pasaron con menos de 10 variantes (`progreso_sint.tsv` y la auditoria). Varias eran
**falsos verdes**: borradores de m2c o C a mano con errores que la unica captura no recorria.
- func_8001CB4C (lector de .bud): restaba los hijos antes de mirarlos (con 0 hijos, 65535 vueltas).
- func_8001B600: no pasaba el nombre al gancho D_8007CA44 ni la linea a Reservar.
- func_800185A8 y HerramientaConvertirTEX: argumentos de mas o de menos (41 inventados en TEX).
- func_800171CC: m2c declaro las globales u8[] y las escrituras de 16 bits guardaban solo el byte bajo.
- func_8004AB24: faltaba recortar a 16 bits un argumento; su donante traia a0 = 0xD (objeto en la direccion 13).
- func_8001F524 (a mano): usaba s3 y func_8001B698 lee el s3 del que llama.
- func_8001A620: el rectangulo en otro lugar de la pila (SubirAVRAM guarda su direccion en la cola del GPU).
- func_80052388 bajo a limite (func_800523B4 guarda su ra y en el C apunta al C).
Las demas estaban bien escritas: solo les faltaban capturas con punteros validos (donantes con a0 = 3, a1 = 0...).

**Herramientas nuevas:**
- `verif/cascada.py padre captura hija [n]`: corre la original del padre y guarda la captura al entrar a la hija
  (argumentos de verdad: un .bud abierto, una textura pedida por nombre).
- verificar: no se compara el marco de pila entero de la original (+0x4000) cuando pasa de 0x4000
  (`marco_original`); el de HerramientaConvertirTEX es 0x800A0 con un bufer de media VRAM.
- Truco: `__attribute__((optimize("no-optimize-sibling-calls")))` en el cuerpo de un stub, o GCC lo convierte en un
  salto y el sp queda corrido. Y separar `t = f(); m[n] = t;` para que GCC no precalcule &m[n] en un s-registro.
- Capturas armadas con `sint.crear_con` (objeto real en 0x80180000, cada estado del switch, cada rama).

**Para anotar al terminar:** `build/refuerzo.txt` (18 funciones) con `py verif/anotar.py build/refuerzo.txt --sint`,
y func_800185A8 con `SABRINA_LIMITE=400000000` (la herramienta INO entera, ~1 min por corrida).

**Mutantes (verif/lanzar_mut4.sh, 8 por funcion):** func_800502DC se paso del tope de 90 min sin resultado;
HerramientaArmarCuadricula 7/8 y HerramientaConvertirPIC 7/8 (el vivo corria el sp que restaura el stub: hueco
del verificador, ya cerrado comparando los registros conservados al volver); func_80018CB8 7/8 (el vivo cambia el
numero de linea que se le pasa a Reservar, que Reservar no usa: equivalente). Se paro para ahorrar bateria; lo que
falta esta en `verif/lanzar_mut5.sh`. Tambien `verif/lanzar_conservados.sh` (en cola tras la INO): repasa las 18
funciones con stub en asm con la comparacion nueva de registros.

### CIERRE DE LA NOCHE 04-10 (EMPIEZA AQUI EL CHAT SIGUIENTE)

**98.7 %: reales 79.3 % (701 fn) + sinteticas 19.4 % (313 fn) = 1014 de 1034.** Todo pusheado.
Lo que queda (20 fn) es limite conocido; ver "CIERRE de esta sesion" mas arriba y `py verif/cuenta.py --pendientes`.
Esta noche, ademas de lo de arriba:
- func_800185A8 (la herramienta INO entera, con SABRINA_LIMITE=400M) IGUAL_SINT.
- verificar endurecido: registros conservados al volver, secciones criticas (syscall) y el manejador de la BIOS con
  lui/ori de verdad. func_800521AC/523B4/80017BC0 se reverificaron y siguen IGUAL.
- La laptop estaba a bateria (sin cargador) al dormir Meme: la cola quedo en WSL y cada resultado se pusheo.

**Cola que quedo corriendo (de a una, en WSL; si la PC se apago, relanzar desde la que falte):**
1. `verif/lanzar_conservados.sh` -> build/conservados.txt y conservados_sint.txt (18 con stub en asm);
2. `verif/lanzar_criticas.sh` -> build/criticas.txt y criticas_sint.txt (13 con secciones criticas);
3. `verif/lanzar_mut5_log.sh` -> build/mut5.txt (mutantes que faltaron).
Relanzar con `verif/fondo.sh verif/lanzar_X.sh /dev/null`. Revisar: cualquier "DISTINTO" con "al volver distintos" o
"secciones criticas distintas" es un error real del C nuevo de detectar; las sint se anotan con
`py verif/anotar.py build/X_sint.txt --sint` (las reales ya estaban IGUAL en la auditoria; solo hay que confirmar).

**Progreso del repaso de stubs al bajar la bateria (29 %):**
  func_800189A4: 8 de 8 capturas y 177 de 177 variantes iguales -> IGUAL
  func_8002D714: 2 de 2 capturas y 1 de 1 variantes iguales -> IGUAL
  CargarANI: 6 de 6 capturas y 76 de 76 variantes iguales -> IGUAL
A 18 % de bateria el repaso iba por CargarWRLDDATA (4 de 17). Si la PC se apago: al prender, conectar el cargador
y relanzar `verif/fondo.sh verif/lanzar_conservados.sh /dev/null` (empieza de cero, ~1-2 h), despues
`verif/lanzar_criticas.sh` y `verif/lanzar_mut5_log.sh`. Hasta aqui ninguna funcion repasada cambio de estado:
las tres que llegaron siguen IGUAL con la comparacion nueva de registros.
  Las 7 reales del repaso de stubs IGUAL con los registros conservados: func_800189A4, func_8002D714, CargarANI,
  CargarWRLDDATA, CrearRecogible, ImprimirDepuracion, func_8005ED8C. Siguen las 10 sinteticas y PantallasLegales.
  HerramientaArmarCuadricula (sint) IGUAL con los registros conservados (la del mutante del sp). A 9 % de bateria
  seguian las otras 9 sinteticas del repaso, PantallasLegales, las criticas y los mutantes: relanzar como dice arriba.
  Las 10 sinteticas con stub tambien IGUAL con los registros conservados (anotadas). Falta PantallasLegales.

### PAUSA 05-10 (Meme pidio pausar) — EMPIEZA AQUI

**98.7 %: reales 79.3 % (701 fn) + sinteticas 19.4 % (313 fn) = 1014 de 1034. Todo pusheado.**
Repaso de stubs con los registros conservados: 17 de 18 siguen IGUAL (7 reales y 10 sinteticas, anotadas).
La cola se paro a mano (`verif/parar_cola.sh`) con PantallasLegales a medias (llevaba ~1 h de ~2 h).

**Lo que falta, en este orden** (cada uno con `bash verif/fondo.sh verif/X.sh /dev/null` desde WSL, de a uno):
1. PantallasLegales con los registros conservados: `SABRINA_VARIANTES=8 SABRINA_LIMITE=300000000 bash verif/vfull.sh
   src/Screen/pantallas_legales_g14.c PantallasLegales` (~2 h; ya era IGUAL, solo confirma el stub).
2. `verif/lanzar_criticas.sh` (13 que usan Enter/ExitCriticalSection, con la comparacion nueva; 8 variantes).
3. `verif/lanzar_mut5_log.sh` (mutantes que faltaron; func_800521AC, 80052240, 800523B4, 80024450,
   HerramientaArmarModelos, Cuadricula y PIC, estas dos para confirmar que el mutante del sp ya se caza).
Si algo da "al volver distintos" o "secciones criticas distintas", es un error real del C (stub o asm).
Lo que queda sin verificar es limite conocido (`py verif/cuenta.py --pendientes`, explicado en "CIERRE de esta sesion").

### 05-10 MANANA, SESION SOLA (EMPIEZA AQUI)

**98.8 %: reales 79.4 % (702 fn) + sinteticas 19.4 % (313 fn) = 1015 de 1034.**

**func_80017D80 (cargar un archivo entero del CD, 468 bytes) pasa a IGUAL: 6 de 6 capturas y 689 de 689 variantes.**
No era limite. Las 2 variantes que fallaban (a0 = 0x10000 y 0x10001, el nombre apunta al codigo del juego) se
trazaron con `verif/traza17d80.py` (gancho de codigo sobre printf, CdSearchFile y _putchar): con ese nombre
CdSearchFile desborda su propia pila y al volver deja basura en los registros s del que llama. La original sale del
bucle de reintentos a la primera llamada (la basura en s0, su contador, ya pasa de 10); el C repetia CdSearchFile
2800 veces, porque GCC habia hecho una cuenta regresiva en s0 y guardaba el puntero al archivo en s1.
Arreglo en `src/File/archivo_entero_g14.c`, con la misma asignacion de registros que la original:
- `register s32 i asm("$16")` y `register s32 listo asm("$17")`, y un `__asm__ volatile("" : "+r"(i), "+r"(listo))`
  despues de cada llamada (sin eso GCC vuelve a cambiar el bucle y no respeta el registro).
- El archivo, la ruta y pos se leen de sp cada vez (`EN_PILA(t, off)`, un addiu sobre $sp en asm volatile), como la
  original, en vez de llevarlos como argumentos en registros s. Vale porque el cuerpo corre con el sp de la original
  (el stub de 0xA0 mas el marco de 0x28 del cuerpo dan los 0xC8 de la original).
- Asi GCC quedo con s0 = i, s1 = listo, s2 = nombre y luego datos, s3 = primero, s4 = ultimo, y ra y s0-s4 en los
  mismos lugares del marco.
OJO: con `SABRINA_VARIANTES=8` (172 variantes) la version vieja tambien daba IGUAL; esas dos variantes solo salen
con las 60 por defecto. Para confirmar un arreglo de una funcion con variantes raras, correr con las 60.

**Truco nuevo (para otras con stub):** si una funcion llamada desborda o pisa los registros s del que llama, el
C tiene que tener cada variable en el mismo registro s que la original: `register ... asm("$N")` mas el asm volatile
vacio con "+r" despues de cada llamada, y los punteros al marco recalculados desde sp.

Mutantes: la primera prueba (8 de 8 cazados) muto solo el stub. **mutantes.py ahora muta el cuerpo en C de los stubs
de asm** (detecta el `jal cuerpo` del stub; `--en` para elegirlo a mano) y anota la linea de cada mutante. En el
cuerpo de func_80017D80 sobrevivio `<` por `<=` (linea 60, `ultimo < primero`): ninguna captura carga un archivo de
un solo sector. `verif/caso17d80.py` corre la captura 00 con WRLDDATA\FRONT\FRW.BIN (368 bytes): el C IGUAL y el
mutante DISTINTO. (La original devuelve 0 con un archivo de un sector: pide leer 0 sectores, falla 10 veces y lo
libera. Error del juego, el C lo copia.)
Tambien sobrevivio quitar cada `Liberar(datos)` de los caminos de error (el modelo del CD nunca falla). caso17d80.py
suma "CdControl falla" (su primera instruccion cambiada por `jr ra; move v0, zero` en la RAM, igual para las dos):
mata el de la linea 73; el de un sector mata el de la linea 86. El C da IGUAL en los cuatro casos. "CdRead falla" no
sirve: CdSearchFile tambien usa CdRead para leer el directorio y la busqueda falla antes.
Resultado final del cuerpo de func_80017D80 (`lanzar_mut_cuerpos.sh`): 4 de 8 cazados por el verificador; los otros 4
(y el de la linea 73) caen con caso17d80.py: lineas 60, 76, 86 y 87 con el de un sector, 73 con CdControl falla.
PantallasLegales con los registros conservados: IGUAL (26 de 26). Las 18 con stub siguen IGUAL.
Las 13 con secciones criticas (`lanzar_criticas.sh`) siguen IGUAL / IGUAL_SINT con la comparacion nueva.
Cola `verif/lanzar_mut_cuerpos.sh` -> build/mut_cuerpos.txt: mutantes en el cuerpo de las 15 funciones con stub.

Trampa: un `open(p, "w")` de python en Windows sin `encoding="utf-8"` escribe en cp1252 y rompe los acentos de este
archivo (paso en fa3d3e1, arreglado en el commit siguiente).

Lo que queda (19 fn) sigue siendo limite: setjmp, InitGeom e InitCARD guardan en memoria una direccion de vuelta
que en el C apunta al C (en un ejecutable rearmado en su direccion daria igual), video, BuclePrincipal, main y asm puro.
Cola de la PAUSA 05-10 relanzada como `verif/lanzar_pausa0510.sh` (PantallasLegales, criticas, mutantes), por WMI
para que no muera con el turno; resultado en build/pausa_pl.txt, build/criticas*.txt y build/mut5.txt.

### 05-10 MEDIODIA, EL CHAT SE CERRO A MEDIAS (EMPIEZA AQUI)

**Llamadas a la BIOS en la comparacion.** En mut5 sobrevivio quitar `FlushCache();` en func_800521AC y func_800523B4
(parchean codigo de la BIOS y luego vacian la cache): el modelo no hace nada en FlushCache y no queda rastro en la RAM.
verificar.py ahora guarda la secuencia de llamadas a la BIOS (tabla 0xA0/0xB0/0xC0 y numero de funcion en t1, sin
argumentos) y la compara: "llamadas a la BIOS distintas". Las que llaman a una envoltura de la BIOS estan en
build/llaman_bios.txt y se reverifican con eso (`verif/lanzar_bios.sh`): Afirmar, Liberar, func_80012B0C y
func_80014774 siguen IGUAL.

El chat se cerro con tres colas a medias (bios en func_800161D4, mut5 en func_80024450, mut_cuerpos en
func_800189A4) y murieron. `verif/lanzar_reanudar0510.sh` sigue cada una desde donde quedo, de a una, lanzada por
WMI. Resumen en build/reanudar.txt; detalle en build/bios.txt, build/bios_sint.txt y build/mut_cuerpos.txt.
Si una da "llamadas a la BIOS distintas", el C llama de mas o de menos a la BIOS: es un error real del C.

Los otros vivos de mut5 en tarjeta_bios_g15.c (0x74 por 117, 0x9C8 por 2505, 0x70 por 113) son mutantes
equivalentes: van dentro de `d[x / 4]` y la division entera da el mismo indice (29, 626, 28). No hay nada que cazar.
Con la comparacion nueva, quitar `FlushCache();` ya muere en las dos: func_800521AC y func_800523B4 dan 7 de 8, y el
unico vivo de cada una es el equivalente. Quedan 0 mutantes reales vivos en tarjeta_bios_g15.c.

**Resultado de la reverificacion con la BIOS (cola partida en `verif/reanudar_a.sh` y `reanudar_b.sh` para usar
mas RAM):** 17 de 19 reales y 21 de 23 sinteticas siguen IGUAL. Salieron tres:
- func_800161D4 (la espera de cuadros) DISTINTO, pero es del verificador: el modelo de VSync pone un gancho en la
  ENTRADA de la original, asi que al verificar esa misma funcion la original salia enseguida y el C (en BASE_C, sin
  gancho) esperaba hasta el limite y llamaba a puts/ChangeClearPAD. Arreglo: no poner ese gancho cuando la funcion
  bajo prueba es func_800161D4 (`EN_PRUEBA`, en verificar_ra.py, ver abajo).
- func_80050AB8 y func_800513B4 (sinteticas) DISTINTO, y esas SI eran errores del C: `include/prototipos.h` declara
  `open(void)`, `close(void)`, `lseek(void)` y `write(void)`, y los borradores de m2c las llamaban sin argumentos
  (sin nombre de archivo ni modo). Igual estaban func_80050418, 80050554, 80050694 y 80050C40 (IGUAL_SINT en falso).
  Las seis reescritas a mano con los argumentos de la original en `src/varios/tarjeta_archivo_g16.c`; cola
  `verif/lanzar_tarjeta16.sh` -> build/tarjeta16.txt (sinteticas y mutantes). func_800509E8 y 80050A50 solo
  declaraban open, no la llaman: estan bien.

**verificar_ra.py (copia de trabajo, se arma con un parche sobre verificar.py; pasarla a verificar.py cuando no
corra ninguna cola):**
- Direcciones de vuelta como reubicacion: se anotan las llamadas que la funcion hace hacia afuera de su codigo
  (destino, ra y sp en el jal/jalr) y una palabra de RAM distinta vale si en la original es el ra o el sp de la
  llamada k y en el C el de la llamada k, con los mismos destinos en el mismo orden. Es lo que daria un ejecutable
  rearmado con el C en su lugar. Para InitGeom (func_800177B4), InitCARD (func_800522E4) y el setjmp de
  func_800163E4.
- Se compara el GTE al final (datos y control) y la secuencia de escrituras al cop0 (mtc0: registro y valor). El
  registro de estado de Unicorn no sirve: no deja poner el bit 30 (CU2).
- **InitGeom (func_800177B4) IGUAL, 32 de 32, y 8 de 8 mutantes cazados** (antes de comparar el GTE y el cop0 caian
  0 de 8: todo lo que hace es escribir ahi).
- Prueba de func_800161D4, InitCARD y func_800163E4 con `verif/probar_ra.sh` -> build/probar_ra.txt.
  `verif/vfull_ra.sh` y `verif/mutantes_ra.sh` son vfull y mutantes con verificar_ra.
- **func_800161D4 IGUAL con el arreglo de la espera: 8 de 8 capturas, 198 de 198 variantes.**

**verificar.py YA ES EL NUEVO (05-10 tarde).** Se arma con `py verif/parche_ra.py build/verificar_antes_0510.py
verificar.py` (copia vieja en build/, fuera de git; el parche esta en el repo). verificar_ra.py queda igual a
verificar.py (solo para los *_ra.sh). Ademas de lo de arriba:
- **Argumentos de la BIOS**: la secuencia de llamadas a la BIOS lleva los argumentos que dice `ARGS_BIOS` (cuantos
  toma cada funcion de la BIOS que usa el juego); un argumento que en las dos apunta a la pila local vale igual (un
  nombre armado en la pila queda en otro lugar del marco). Con eso func_80051D14 (TestEvent sin argumento) da 0 de 3.
- **Llamadas a funciones del mismo .c**: en el C una llamada a la copia en C de una funcion del juego se anota como
  llamada a la original (MAPA_C); si no, las listas de llamadas no coincidian y no se reubicaba nada.
- `verif/depurar_ra.py src/x.c funcion [captura]` muestra las palabras distintas y las llamadas de las dos.

**Borradores con la BIOS sin argumentos, reescritos en `src/varios/bios_eventos_g16.c`** (14): func_80014910,
80014988 (SysEnq/DeqIntRP), 80016874 (HookEntryInt), 80029808/30/58 (DeliverEvent del CD), 8003E554 (DeliverEvent
del SPU), 800515B0 (erase), 80051A84 (8 OpenEvent y EnableEvent), 80051C60 (CloseEvent), 80051D14/1E1C/1EF4
(TestEvent), 80052350 (ChangeClearPAD). Cola `verif/lanzar_eventos16.sh` -> build/eventos16*.txt.
OJO: `anotar.py` no baja un estado; si alguna de estas no da IGUAL con el archivo nuevo, hay que sacarla a mano de
auditoria.tsv / progreso*.tsv (el borrador viejo ya no vale).

**func_800163E4 (el setjmp de libetc)**: con el verificador nuevo solo diferian ra (se reubica) y s0, que el setjmp
guarda: en la original s0 = D_80063918. Arreglo en libetc_g13.c: `register u8 *base asm("$16")` con asm volatile
antes de la llamada, y `noinline` en func_800168EC, 80016AF4 y 80016DA0 (GCC las metia dentro y faltaban llamadas;
solo las llama func_800163E4). Cola `verif/lanzar_limites0510.sh` -> build/limites0510*.txt (setjmp, InitGeom,
InitCARD y mutantes). Cola `verif/lanzar_revisar.sh` -> build/revisar_real.txt / revisar_sint.txt: las 61 contadas
que llaman a la BIOS o usan cop2/mtc0 (`verif/lista_revisar.py`), con el verificador nuevo.

### 05-10 TARDE: RESULTADOS (EMPIEZA AQUI)

**98.5 %: reales 79.1 % (703 fn) + sinteticas 19.4 % (314 fn) = 1017 de 1034.** Pasaron a IGUAL las que eran
limite por guardar una direccion de vuelta: setjmp de libetc (func_800163E4, 8 de 8 mutantes), InitGeom
(func_800177B4, 8 de 8) e InitCARD (func_800522E4, sintetica, 8 de 8). Bajo func_8001FD50 (ver abajo).
- Eventos (bios_eventos_g16.c): las 8 reales y las 6 sinteticas IGUAL con los argumentos de la BIOS. Mutantes:
  func_80051A84 8 de 8; func_8003E554 3 de 8 con la captura sintetica de la funcion de usuario (los 5 vivos son
  equivalentes: el bucle de espera de func_8003EA90 no deja rastro y el bucle del SPU ocupado no se puede activar).
- Tarjeta (tarjeta_archivo_g16.c) con capturas a mano (`verif/capturas_tarjeta16.sh`): func_80050418 176 de 176,
  func_80050554 y 80050694 254 de 254, func_800513B4 84 de 84 y **8 de 8 mutantes** (antes 0 de 8).
- **Truco de stub para funciones con un bufer en la pila**: func_800513B4 (crear) y func_800515B0 (borrar) arman
  ruta[32] en sp+0x10 y guardan resultado en sp+0x30, justo despues; un nombre de mas de 32 letras (variante con
  a1 = 0x200) desborda ruta y pisa resultado y los registros guardados. Con el marco de GCC daba otro nombre de
  archivo. Ahora un stub en asm arma el marco de la original (registros en los mismos lugares) y el cuerpo en C usa
  `ruta + 32` como resultado. El atributo optimize("no-move-loop-invariants") NO sirve (cambia el lugar de los
  registros guardados y queda peor).
- **gte.py**: los registros de datos de 16 bits guardan solo eso (VZ0-2, IR0-3 con signo; OTZ, SZ0-3 sin signo),
  como la consola. func_80024A48 daba "coprocesador geometrico distinto" por un lw contra un lhu del mismo dato:
  ahora 149 de 149.
- **mutantes.py** ya no muta los comentarios (un "05-10" en un comentario lo hacia caer).
- **func_8001FD50 bajo a DISTINTO** (1348 bytes): 2 de 162 variantes con fin = 0xA3C20040. Con
  `verif/depurar_args.py src/geometria/arbol.c func_8001FD50 1 800178cc 801074ac a3c20040 2c40000 ff000000` se ve
  que el C deja de recorrer los hermanos despues del nodo 30 (visible, entra al dibujo) y la original sigue con 210
  mas; la RAM queda igual y solo difiere el GTE. Lo mas probable: con ese fin, los partidores (D_80068878[corte]) o
  AddPrim escriben en la pila del que llama y pisan otra cosa en el marco de GCC que en el de la original (0x70).
  Siguiente paso: confirmar con un gancho de escritura en la pila del C, y si es eso, stub con el marco de la original.
- Cola B (`reanudar_b.sh`) PARADA a mano por falta de RAM, en los mutantes de func_80024450 (85 min). Faltan el
  resto de mut5 y mut_cuerpos desde func_800189A4: relanzar `verif/reanudar_b.sh` cuando haya memoria.
- `verif/lanzar_revisar.sh` sigue (reverificacion de las 61); los DISTINTO de borradores viejos de src/auto ya
  reemplazados (func_80014910, 80014988, 80016874, 80029808/30/58, 8003E554) no cuentan: las versiones de
  bios_eventos_g16.c son las que estan en auditoria.tsv.

### 05-10 NOCHE 2: REVERIFICACION TERMINADA, DIBUJO DEL ESCENARIO PROBADO (EMPIEZA AQUI)

Sesion sola, sin agentes, con Roblox Studio y otras sesiones abiertas (2-3 GB libres): una o dos colas a la vez.
- **Las 24 de `verif/revisar_falta.txt` terminaron** (logs `build/revisar_real.txt` y `revisar_sint.txt`). IGUAL todas
  salvo: los borradores de `src/auto/` de 800515B0, 80052350, 80051A84, 80051C60, 80051D14, 80051E1C, 80051EF4 (no
  cuentan: la auditoria apunta a `bios_eventos_g16.c`), func_80050AB8 (se corto a la hora, ver abajo), func_80051764 y
  los tres partidores (arreglados abajo).
- **func_8001FD50 IGUAL, 22 de 22 capturas y 954 de 954 variantes.** No era la pila. Con a2 = 0xFF000000 el C se
  saltaba las matrices: la original guarda la bandera con `sb` y la relee con `lbu` (se queda con el byte) y con `u8`
  en la firma GCC da por hecho que quien llama ya la recorto. Ahora entra como s32 y se recorta adentro. Se barrieron
  las demas funciones con parametros cortos (u8/s16...): en las otras cuatro el recorte sale igual (sb/sh, lhu de la pila).
- **Lo mas importante: las 8 capturas viejas de func_8001FD50 no probaban el dibujo.** Eran de los primeros cuadros, con
  la camara sin poner: un solo triangulo pasaba los descartes y caia fuera de pantalla (6 de 12 mutantes vivos, uno era
  `D_8007CAC0 -= 0x28`). Nuevo `scripts/capt_dibujo.py` (entra a cada nivel, espera 1300 cuadros y captura en dos
  puntos): 14 capturas mas de func_8001FD50 y de func_800204F0, con hasta 13 triangulos por captura llegando a AddPrim,
  recorte y partidores. Lo mismo puede pasar con otras funciones de dibujo verificadas con capturas del arranque.
- **verificar.py**: llegar a la vuelta de las interrupciones (VUELTA_INT) sin ninguna en curso ya no revienta la
  verificacion entera con un TypeError; es un error de esa corrida y se compara como cualquier otro.
- **func_80051764 IGUAL_SINT 136 de 136** (formatea la tarjeta, ahora en `bios_eventos_g16.c`): el borrador llamaba a
  `_card_load()` sin el puerto y era void (sin el -1). Ademas el puerto se lee de D_800D52D0 como en la original: con
  D_800D52C0[4] GCC usaba s1, el marco crecia a 0x20 y el bufer de pila de func_80052578 que va a `_card_read` quedaba 8
  bytes mas abajo (el verificador compara ese argumento). Leccion: un argumento de pila distinto en la BIOS desde una
  funcion llamada es un marco de otro tamano en el C.
- **Partidores func_800589EC, 80058EE4, 800593E0**: con el GTE comparado daban DISTINTO en todo, solo por VXY2/VZ2. La
  original manda a rtpt un tercer vector que nunca llena (sp+0x3C de su marco de 0x60) y el C mandaba su propia basura.
  Pasaron a stub con el marco de la original + cuerpo en C que carga ese vector desde sp+0x3C (el truco de la basura de
  pila); con la captura 0 el GTE ya sale igual en los tres. Cola `verif/lanzar_0510b.sh` (log `build/cola_0510b.txt`)
  con la verificacion completa y los mutantes; anotar con `py verif/anotar.py build/cola_0510b.txt --solo ...`.
- La cola `lanzar_0510b.sh` dio **IGUAL a los tres partidores** (139, 142 y 141 variantes, con 2 capturas) y 8 de 8
  mutantes muertos en func_80051764; sigue con los mutantes de los partidores. Despues se capturaron con
  `py capt_dibujo.py 1,3,5,7,9,11,13 func_80057F34,...,func_80020294` entre 11 y 14 capturas de juego para los siete
  partidores y func_80020294.
- **Cola encadenada `verif/lanzar_dibujo.sh`** (log `build/cola_dibujo.txt`), lanzada por WMI: espera el "TODO FIN" de
  `cola_0510b.txt` y reverifica con las capturas nuevas func_800204F0, func_80020294 y los siete partidores, y al final
  los mutantes de func_8001FD50 (los primeros se pararon a mano por RAM: Windows llego a 0.9 GB libres por las otras
  sesiones; WSL solo ocupaba 0.5 GB). Al terminar: `py verif/anotar.py build/cola_dibujo.txt` y
  `py verif/anotar.py build/cola_0510b.txt --solo func_800589EC,func_80058EE4,func_800593E0`.
- **PARADO A MANO por Meme ("mata todo")**: se mataron las dos colas y se apago la maquina de WSL. De los mutantes de
  `lanzar_0510b.sh` alcanzaron a salir func_80051764 8 de 8 y func_800589EC 8 de 8; func_80058EE4 y func_800593E0
  quedaron sin mutantes y `lanzar_dibujo.sh` no llego a empezar. Para seguir: quitar de `lanzar_0510b.sh` lo ya hecho
  (o correr solo los mutantes que faltan) y relanzar `lanzar_dibujo.sh` (espera el "TODO FIN" de `cola_0510b.txt`:
  agregarlo a mano o quitar esa espera).
- func_80050AB8: no es un error, es costo. Cuando el modelo de la tarjeta responde 3 la original reintenta sin fin y
  esa variante gasta el tope de instrucciones en las dos versiones; con 8 variantes pasa de una hora. Correrla sola
  con `timeout` largo (4 h) cuando la PC este libre.
- Pendiente ademas: mutantes de tarjeta16b; cola B; revisar si otras funciones de dibujo tienen solo capturas del
  arranque (como func_8001FD50) y darles capturas con `capt_dibujo.py`.

### 05-10 NOCHE: SE APAGO LA PC

**98.5 % (1017 de 1034), todo pusheado.** Meme apago la PC; las colas que corrian en WSL murieron.
- La reverificacion destapo dos mas con la BIOS sin argumentos: func_8004FD34 y func_80050034 (callbacks de
  eventos de la tarjeta) llamaban a `_card_info()` / `_card_load()` sin el puerto. Copias de los borradores con el
  puerto en `src/varios/tarjeta_evento_fd34_g16.c` y `tarjeta_evento_0034_g16.c` (alias en asm
  `extern void tarjeta_info(s32) __asm__("_card_info")` para no chocar con prototipos.h): **IGUAL 77 de 77 y 73 de 73**.
- De la reverificacion de las 61 (`verif/lanzar_revisar.sh`) van 37: todas IGUAL salvo los borradores viejos ya
  reemplazados (lista arriba), func_8001FD50 (pendiente, arriba) y las dos de la tarjeta de este punto (ya arregladas).
  **Faltan 24, en `verif/revisar_falta.txt`.** Para seguir, desde WSL (los logs se agregan, no se borran):
  `LISTA=/mnt/c/Proyectos/SABRINA/decomp/verif/revisar_falta.txt bash verif/lanzar_revisar.sh`, lanzado por WMI
  (`Invoke-CimMethod Win32_Process Create` con `wsl.exe -d Ubuntu-24.04 -- bash ...`) para que no muera con el turno.
  Un DISTINTO con "llamadas a la BIOS distintas" casi siempre es un borrador que llama a la BIOS sin argumentos:
  mirar el asm de la original y pasarlos.
- Murieron a medias: los mutantes de `lanzar_eventos16.sh` (iba en func_80051E1C; los de func_80051D14 dieron 3 de
  8, los vivos son las cadenas b[3]=0... con banderas ya en 0, equivalentes con esas capturas), `lanzar_tarjeta16b.sh`
  (la verificacion termino; faltaban los mutantes de 80050418, 80050AB8 y los de abrir_y_pasar) y la cola B.
- Orden sugerido al volver: 1) revisar_falta.txt; 2) mutantes de tarjeta16b; 3) func_8001FD50; 4) cola B.
  Con poca RAM (bajo 2 GB) correr de a una cola.

### 07-10: VIDEO DESTRABADO, PARADO A MANO (EMPIEZA AQUI)

**Sigue 99.0 % (1018 de 1034).** Meme pidio apagar todo; colas muertas y WSL apagado.
- **El video no era limite.** `func_8005D50C` no se colgaba: el modelo del CD entregaba como datos los sectores de
  audio XA que los .STR traen cada 8 de video (submodo 0x64) y la biblioteca de video no armaba los cuadros.
  `modelo_cd.py` ahora los salta sin INT1 cuando el modo tiene 0x40 (XA-ADPCM), como la consola que los manda al
  sonido. Con eso la original termina, tambien con la captura real (`capturas/func_8005D50C/00`).
- Queda un detalle del modelo: el video corta en el cuadro 4 (el 3 llega desde el trozo 2: se pierden dos sectores,
  14003 y 14004) y termina por "cuadro menor que la cuenta". En la consola no pasa. Original y C ven lo mismo, asi
  que la comparacion es justa, pero no recorre el video entero.
- Capturas sinteticas armadas (fuera de git, `decomp/capturas_sint/`): func_8005D50C con el cuadro final del pedido
  (`m801FFDE4`) en 12, 30 y 40 (esta con fundido D_8007CC94=0x80); ReproducirSTR con a1 = 0x10 y 0x22 (el cuadro final
  es a1 - 4). Ojo: si la real ya termina, verificar primero con la real (`vfull.sh`), que cuenta como real.
- Al volver: 1) `SABRINA_LIMITE=300000000 bash verif/vfull.sh src/Screen/video_reproductor_g14.c func_8005D50C`
  (y `vsint.sh` si no); lo mismo con ReproducirSTR (src/Screen/video_g13.c); 2) reverificar lo que lee audio XA
  (la musica de los niveles, CdRead con modo 0x40) porque el cambio del modelo les toca; 3) `verif/lanzar_0710.sh`
  sin los mutantes de func_80058EE4 (ya dieron 5 de 8; los vivos cambian m[0]/m[1] y sxy[1]/sxy[2] en las lineas
  69-71 de partir_80058EE4.c: vertices que coinciden en las capturas, cobertura y no error del C).
- Herramientas de diagnostico usadas (en el scratchpad, no en el repo): parchear `V.Uc.emu_start` para poner un
  gancho en 0x8005CEF0 (vuelta de StGetNext en func_8005CEBC) y ver el numero de cuadro y trozo de cada uno.
- Truco escondido del juego (para la seccion de secretos): `truco_invencible` en 0x8007CB74 (nadie lo enciende),
  hechizos 6 y 7 vacios en la tabla D_80074BC4, selector de niveles por 0x8007CA00.

### 08-10: VIDEO IGUAL (EMPIEZA AQUI)

**99.3 % (1020 de 1034).** GitHub no tenia nada nuevo del amigo (7bbb749 era lo ultimo).
- Con el modelo del CD que salta el audio XA, **func_8005D50C IGUAL** (1 de 1 capturas, 10 de 10 variantes) y
  **ReproducirSTR IGUAL** (1 de 1, 22 de 22), con `SABRINA_LIMITE=300000000` y la captura real. Anotadas.
- El audio XA del disco esta solo en FMV (LBA 14140 a 40596). La musica va en las pistas de CD-DA 2 a 7 y los .WAV
  de AUDIO1-4 apuntan a esas pistas, asi que el cambio del 07-10 solo toca al reproductor de video.
- Colas encadenadas en WSL, lanzadas por WMI, una a la vez (2.9 GB libres):
  `verif/lanzar_0810.sh` (log `build/cola_0810.txt`: video, mutantes de func_800593E0, dibujo con capturas nuevas,
  mutantes de func_8001FD50); `verif/lanzar_0810b.sh` (log `cola_0810b.txt`: reverifica las 17 del reproductor de
  video); `verif/lanzar_0810c.sh` (log `cola_0810c.txt`: mutantes de las dos del video). Cada una espera el
  "TODO FIN" de la anterior. Al terminar: `py verif/anotar.py build/cola_0810.txt` y lo mismo con `cola_0810b.txt`.
- Lo que queda (14) es limite ya documentado: BuclePrincipal y main no vuelven, setjmp y manejador de excepciones en
  asm, trampolines de BIOS/PCdrv, func_80052114/40/84 (usan v1 del que llama), func_80052388.

### 08-10 NOCHE: PARADO A MANO (Meme, RAM llena)

**99.4 % (79.9 reales + 19.4 sint, 1024 de 1034), SIN commitear.** Anotadas en auditoria.tsv las colas 0810 y 0810b.
- WSL apagado a mano (`wsl --shutdown`); la cola `verif/lanzar_0810d.sh` (cortes que faltan de BuclePrincipal, log
  `build/cola_corte2.txt`, y despues mutantes del video `lanzar_0810c.sh`) se mato al empezar: relanzarla por WMI.
- func_8005CEBC salio DISTINTO en 1 de 199 variantes (la que hace fallar la afirmacion): el C llamaba a Afirmar sin
  archivo ni linea. Arreglado en `src/auto/func_8005CEBC.c` (alias Afirmar3 con D_8007C930 y 0x384), FALTA verificarlo.
- Mutantes vivos por revisar: func_8001FD50 (4 de 12) y func_800593E0 (1 de 8), en `build/cola_0810.txt`.

### 08-10 NOCHE 2: CASI TODO (EMPIEZA AQUI)

**99.4 % (79.9 reales + 19.5 sint), 1030 de 1034.** Despues del apagado de WSL se retomo todo.
- func_8005CEBC IGUAL (199/199) tras pasar archivo y linea a Afirmar.
- **PCdrv en C** (`src/psyq/pcdrv.c`): func_800294F0 (PCcreat), func_80029518 (PCclose), func_80029530 (PCwrite) con
  el mismo break en asm y variables de registro, y func_80052114 (trozo del mando con v1/v0 de entrada). Las cuatro
  IGUAL_SINT. verificar.py ahora pone el gancho de PCdrv tambien en cada break del codigo del C, y
  `SABRINA_PCDRV_FALLA=1` hace que la PC conteste que no (recorre la rama de error de PCcreat; su mutante muere asi).
  Mutantes vivos que quedan: equivalentes (registros temporales, una vuelta menos en la espera).
- `sint.py crear_con` acepta v0= y v1= (ademas de a0-a3).
- malloc y free de la BIOS ahora comparan su argumento (ARGS_BIOS). free (func_800161C8) IGUAL_SINT; malloc,
  func_80017CBC/CE4, Reservar (960/960), Liberar (1088/1088) y func_8004DC10 siguen IGUAL.
- func_80052388 IGUAL_SINT: con `__asm__ volatile("")` despues de la ultima llamada (GCC la hacia salto y
  func_800523B4 guardaba en D_800D53C0 el ra del que llamo). Sin la barrera da DISTINTO justo ahi (probado).
- func_80052140/84 y func_80017B8C son trozos que se copian a la RAM de la BIOS (en la captura 0xDFAC tiene la
  primera instruccion de func_80052140) y vuelven al manejador de la BIOS (0x3488): limite.
- BuclePrincipal: cortes en `build/cola_corte2.txt` (corriendo); al terminar, mutantes del video (cola_0810c.txt).
- func_8001FD50: el mutante "7 por 8" vive porque ninguna captura tiene un triangulo con el lado 0-2 largo (el +7
  de la tabla D_80068878); falta una captura con un triangulo grande muy cerca de la camara.

### 08-10 NOCHE 3: PARADO A MANO (EMPIEZA AQUI)

**99.4 % (79.9 reales + 19.5 sint), 1030 de 1034, todo pusheado.** Meme pidio parar; colas paradas y WSL apagado.
- **GTE con la pantalla del juego** (`SABRINA_GTE_JUEGO=1` en verificar.py): las capturas no guardan el estado del
  coprocesador y arrancaba en ceros (H = 0, centro en 0,0): cada triangulo se proyectaba a un punto. Con los valores
  del juego (SetGeomOffset(0x100, 0x6E), SetGeomScreen(0x190)) func_8001FD50 sigue IGUAL (22/22, 832/832) y el
  mutante "7 por 8" de la tabla de partidores ya muere. Vivos: bordes exactos (z 0x400 y 0xB, lado 0x3D) y el
  bit de semitransparencia (`codigo |= 2`, ninguna textura de las capturas tiene banderas & 1).
- Repetidas con la pantalla del juego, todas IGUAL: func_800177B4, func_80017B5C, func_80017B7C, func_8001C404,
  func_8001F6C8, func_8001FA3C, func_80020294, func_800204F0, func_80024A48. Faltan las 7 de partir_*.c
  (`build/gte2.sh` las corre de lista_gte.txt; parado en func_80057F34). Si pasan, dejar GTE_JUEGO por defecto.
- **BuclePrincipal**: el corte 0x8004E268:1 no dejo resultado (lo corto el `timeout 10800` sin escribir nada);
  faltan 0x8004B320:1 y 0x80019D80:30. Subir el timeout o bajar SABRINA_VARIANTES antes de relanzar
  `verif/lanzar_0810d.sh` (despues corre solo los mutantes del video, lanzar_0810c.sh).
- Lo demas que queda (func_80017B8C, func_80052140/84) son trozos que se copian a la BIOS: limite.
