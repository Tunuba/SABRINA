#include "juego.h"

extern u16 D_8007CAF0;               /* mascara de la tabla de azar (su largo menos uno) */
extern u16 D_8007CAF2;               /* por donde va leyendo la tabla */
extern u16 *D_8007CAF4;              /* la tabla de numeros al azar, de 16 bits */

/* Escala el numero por el siguiente de la tabla de azar, tomado como fraccion de 0x10000: la parte alta
 * se multiplica entera y la baja se multiplica y se corre 16 bits. Avanza la posicion de la tabla, que da
 * la vuelta con la mascara. */
s32 func_80021CE4(s32 n) {
    u16 pos = D_8007CAF2;
    u32 azar;

    D_8007CAF2 = pos + 1;
    azar = D_8007CAF4[pos];
    D_8007CAF2 &= D_8007CAF0;
    return (n >> 16) * (s32) azar + (((u32) (n & 0xFFFF) * azar) >> 16);
}
