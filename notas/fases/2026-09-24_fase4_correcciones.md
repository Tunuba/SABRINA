# Fase 4 (2026-09-24, de noche): las 11 DISTINTO de la auditoria

Retomando `notas/fases/2026-09-24_fase1-3_auditoria.md`: de las 11 funciones que la auditoria a mano dejo en
DISTINTO, 10 resultaron ser bugs del propio verificador (`decomp/verificar.py`), no del C escrito a mano.
Solo queda una de verdad pendiente.

## Bugs de infraestructura encontrados y corregidos en `verificar.py`

1. **`syscall` sin manejar**: `func_800143E4` y `func_800143F4` (EnterCriticalSection/ExitCriticalSection,
   `psyq_g01.c`) usan la instruccion real `syscall`. Unicorn no la implementa: la marca como excepcion no
   manejada tanto en el original como en el C, pero como cada uno la ejecuta en una direccion de memoria
   distinta, el verificador comparaba el mensaje de error completo (con la direccion incluida) y siempre daba
   DISTINTO aunque los dos fallaran exactamente igual. Se agrego un hook `UC_HOOK_INTR` que reconoce la
   instruccion `syscall` y deja v0 en 1 (el valor real que devuelve la BIOS), igual para las dos versiones.

2. **`es_void()` no reconocia macros de atributo**: `func_80019374` (`Font/letras_g03.c`) esta declarada
   `TOCA_NULL void func_80019374(...)`. El chequeo de "es void" exigia que el tipo capturado fuera
   exactamente `"void"`, y con la macro delante daba `"TOCA_NULL void"` -> no coincidia -> trataba la funcion
   como si de verdad devolviera algo y comparaba v0 (que es basura: los 3 lugares que la llaman lo ignoran).
   Ahora se compara solo la ultima palabra del tipo capturado.

3. **El C compilado choca con un puntero fuzzeado**: el verificador compila el C de la funcion y lo carga en
   `BASE_C = 0x80400000`, fuera de los 2 MB reales de la PS1 pero dentro del mismo bloque de 256 MB. Cuando
   el generador de variantes de prueba (argumentos al azar o memoria parchada) produce por pura casualidad un
   puntero que cae justo en esa zona, la version original lo lee como RAM en cero (nunca la toca) y la
   version en C lee ahi su propio codigo maquina: mismos datos de entrada, comportamiento distinto, sin que
   la funcion tenga ningun error real. Le paso a `func_80027F08` (a traves de un argumento) y a `func_8002ECFC`,
   `func_80031538`, `func_80039A70`, `func_80039B1C` (a traves de un dato de memoria parchado que resulto ser
   un puntero). Se agrego `_evitar_base_c()`, que aleja cualquier valor generado al azar de esa ventana de 64
   KB, aplicada tanto a los argumentos (`variantes()`) como a los parches de memoria.

`func_800483F8` y `func_8004E618` tambien pasaron a IGUAL al re-verificar con estos arreglos (mismo tipo de
choque, no hizo falta tocar nada especifico de esas dos).

## La que sigue pendiente de verdad

**`func_8003A46C`** (`colision/triangulo_g09.c`, prueba si un punto cae en un triangulo de colision): con
ciertos datos de memoria parchados, `PuntoEnTriangulo` (la funcion real del juego, no una reimplementacion:
se linkea directo a su direccion real tanto desde el original como desde el C) devuelve resultados distintos
en las dos corridas. Se descarto por comparacion directa contra el desensamblado que:
- los offsets del struct `ConsultaSuelo` (`punto_x` 0x30, `altura` 0x34, `punto_z` 0x38, `normal` 0x3C) son
  correctos,
- el orden y los registros de los 3 argumentos pasados a `PuntoEnTriangulo` (`normal`, `&p`, `t`) coinciden
  exactamente con el original,
- `t->v0[1]` (el segundo vertice) se lee igual en las dos versiones.

Falta averiguar por que, con esos mismos datos de entrada, la llamada a la misma funcion real da un resultado
distinto entre la corrida "original" y la corrida "C" -sospecha sin confirmar: el arreglo de `p[3]` podria
terminar en una direccion de pila distinta a la que asume el original en alguna de las dos versiones, y el
puntero que de verdad le llega a `PuntoEnTriangulo` seria diferente aunque el valor final en memoria coincida
al terminar.

## Resultado

Auditoria a mano: DISTINTO 1 (antes 11), IGUAL 100 (antes 91), IGUAL_V0 7 (antes 6), el resto sin cambios.
**Verificado en total: 331 funciones, 68164 de 293812 bytes = 23.2 %** (antes 22.8 %).

`notas/fases/auditoria.tsv` ya quedo actualizado a mano con estos resultados (no se corrio `auditar.py`
completo de nuevo, para no rehacer los 29 TOPE_DE_TIEMPO; se reverifico funcion por funcion con
`verificar.py` sobre los 8 archivos tocados).

## Siguiente

1. Investigar a fondo `func_8003A46C` (la unica DISTINTO real que queda).
2. Repetir las 29 TOPE_DE_TIEMPO con `python3 auditar.py --tope 3600`.
3. Terminar el lote automatico (`COMO_RETOMAR.md`, paso 1).
