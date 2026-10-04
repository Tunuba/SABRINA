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
