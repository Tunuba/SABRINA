# Capturas sinteticas (aprobado por Meme el 2026-10-02)

Para las funciones que no se ejecutaron en ninguna ronda de capturas (SIN_CAPTURAS), `decomp/sint.py`
arma una captura "sintetica": la RAM, el scratchpad y los registros de una captura REAL de otra funcion
(la donante, la mas cercana en direccion que tenga capturas; queda anotada en `capturas_sint/F/DONANTE`),
con el pc en la funcion a probar. El verificador corre igual el original y el C sobre esa memoria y sobre
sus variantes (argumentos y memoria al azar), asi que la comparacion es la misma; la diferencia es que la
funcion no fue llamada de verdad en ese momento del juego, asi que la cobertura puede ser menor.

Por eso NO se mezcla con lo verificado con capturas reales:

- las capturas van en `decomp/capturas_sint/` (fuera de git, como `capturas/`);
- el lote escribe en `decomp/progreso_sint.tsv` con estados `IGUAL_SINT` / `IGUAL_V0_SINT` (y los demas
  como siempre), no en `progreso.tsv`;
- lo escrito a mano y verificado asi va en `notas/fases/auditoria.tsv` con estado `IGUAL_SINT` o
  `IGUAL_V0_SINT`.

Prueba de que el metodo detecta errores: `python3 sint.py mutantes src/auto/func_80026DB0.c func_80026DB0`
mato 8 de 8 mutantes.

Uso: ver el encabezado de `decomp/sint.py` (candidatas, crear, lote, verificar, mutantes). Candidatas:
SIN_CAPTURAS de hasta 0x180 bytes, con 2 llamadas como mucho, 6 accesos a globales como mucho y sin
coprocesador ni syscall.

## Resultados de mutantes (02-10 noche)

Sobre las 5 IGUAL_SINT mas grandes (`--max 12`): func_80060170 12/12, func_8003C528 11/12,
func_80039EBC 8/12, func_80039DD0 7/12, func_80053038 4/12. En las chicas el metodo detecta casi todo; en
las que tienen varios caminos la captura sintetica suele recorrer uno solo y los mutantes de los otros
sobreviven. Un IGUAL_SINT de una funcion con muchas ramas vale menos que uno de capturas reales.

## Ampliacion

`sint.py candidatas --tope 0x400 --llamadas 4 --globales 10 --nuevas` (y despues 0x800/8/20): las
opciones `--llamadas` y `--globales` sueltan los limites y `--nuevas` salta las que ya estan en
progreso_sint.tsv. Al 02-10 quedan 326 SIN_CAPTURAS; con los limites mas sueltos entran 114 (las demas usan
el GTE, mtc0 o syscall).

## Estado al cierre del 02-10 (noche)

- Lote (progreso_sint.tsv): 140 IGUAL_SINT y 51 IGUAL_V0_SINT.
- A mano (auditoria.tsv): 59 IGUAL_SINT (casi todas las que el lote dejo DISTINTO, NO_COMPILA o IGUAL_V0).
- No se pueden verificar asi: las que esperan al hardware (NO_TERMINA en la original), las que copian
  codigo a la BIOS (func_800521AC, func_80052240, func_800523B4) y los trozos de codigo sueltos
  (func_80052114, func_80052140, func_80052184, func_800161C8, func_8004E2CC ya esta).
- `sint.py candidatas --gte` deja pasar las que usan el GTE (gte.py lo emula igual que con capturas reales).
