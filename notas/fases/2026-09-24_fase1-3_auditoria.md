# Fases 1 a 3 (2026-09-24): C a mano y auditoria

Los tres workflows de agentes (las 23 funciones perdidas en la mudanza, las 7 GTE que parten triangulos y
la oleada de ~100 funciones chicas) se pararon a medias a las 19:00 porque la PC se apagaba a las 20:30. El C
que alcanzaron a escribir quedo en `decomp\src`. En vez de creerle a los reportes de los agentes, se
verifico todo de nuevo con `decomp\auditar.py`.

## Resultado (tabla completa por funcion: `auditoria.tsv`)

149 funciones escritas a mano en 65 archivos:

| estado | funciones | que significa |
|---|---|---|
| IGUAL | 91 | verificada contra capturas reales y variantes |
| IGUAL_V0 | 6 | todo igual menos v0, que solo se usa por punteros |
| TOPE_DE_TIEMPO | 29 | la verificacion paso de 20 min; hay que repetirla con mas tiempo (`--tope`) |
| DISTINTO | 11 | hay diferencias: corregir |
| NO_TERMINA | 9 | esperan al hardware (CD, sonido); no se pueden verificar asi |
| SIN_CAPTURAS | 2 | nunca se ejecutaron en las capturas |
| NO_ESTA | 1 | CrearParticula: el nombre no esta en funciones_juego.tsv (revisar el nombre) |

**Verificado en total: 321 funciones, 66984 de 293812 bytes = 22.8 % del codigo del juego** (224 del lote
automatico y 97 a mano). Antes de la mudanza era 15.0 %.

El lote automatico quedo a medias (623 funciones de ~1000 revisadas); al terminarlo puede subir.

## Hallazgo: capturas nuevas que cazan errores viejos

`func_80039A70` y `func_80039B1C` (`objetos\forma.c`, formas de colision) estaban verificadas desde antes
de la mudanza y **ahora dan DISTINTO** sin que su C haya cambiado. Lo nuevo son las capturas de las rondas 2
y 3 (niveles que antes no se visitaban). Sin confirmar todavia, pero lo mas probable es que esas capturas
recorran una rama que las viejas no tocaban y que el C tenga un error real ahi. Hay que revisarlas primero.

## DISTINTO, para corregir

func_800143E4, func_800143F4 (psyq\psyq_g01.c); func_80019374 (Font\letras_g03.c); func_80027F08
(membank\tarjeta_g06.c); func_8002ECFC (varios\varios.c); func_80031538 (sabrina\sabrina_g07.c);
func_80039A70, func_80039B1C (objetos\forma.c); func_8003A46C (colision\triangulo_g09.c);
func_800483F8 (objetos\objetos_g10.c); func_8004E618 (varios\banco_b.c).

## Siguiente

1. Repetir las 29 TOPE_DE_TIEMPO con `python3 auditar.py --tope 3600` (o solo esos archivos).
2. Corregir las 11 DISTINTO, empezando por las dos de forma.c.
3. Terminar el lote automatico (`COMO_RETOMAR.md`, paso 1).
4. Probar el nivel fantasma con el piso arreglado y el cubo (`COMO_RETOMAR.md`).
