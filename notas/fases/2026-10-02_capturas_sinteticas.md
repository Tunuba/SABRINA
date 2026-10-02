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
