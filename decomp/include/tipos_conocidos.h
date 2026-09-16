/* Prototipos escritos a mano de las funciones cuyos tipos ya se entienden. Lo que este aqui manda sobre
 * prototipos.h (aridad.py salta estos nombres) y m2c escribe los accesos con nombres de campo en vez de
 * `M2C_FIELD(arg0, s32 *, 0x24)`.
 *
 * Al agregar una funcion aqui hay que volver a correr `python3 aridad.py`. */
#ifndef TIPOS_CONOCIDOS_H
#define TIPOS_CONOCIDOS_H

#include "objeto.h"
#include "banco.h"

void DanoPorEnemigo(Objeto *sabrina, Objeto *enemigo);
EstadoAnim *func_8002ECFC(Objeto *o);
void func_8002ED30(Objeto *o);
void func_8003018C(Objeto *o);
s32 func_8002218C(Objeto *o, s32 a, s32 b);

s32 func_8004E2A4(u32 tam);
void func_8004E86C(Banco *b, Bloque *bl, s32 clase);
Bloque *func_8004E774(Banco *b, s32 clase);

#endif
