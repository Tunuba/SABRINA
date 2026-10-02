#include "juego.h"

/* La tabla de numeros al azar del juego. */

extern s16 D_8007CAF0, D_8007CAF2;   /* el ultimo lugar y el que sigue */
extern u16 *D_8007CAF4;              /* la tabla */
extern char D_8006C468[];            /* el nombre del archivo fuente */
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern s32 func_80014F10(void);      /* rand */

/* Arma una tabla de n numeros al azar (pares, hasta 0xFFFE), llenandola de atras para adelante. Devuelve -1
 * (o el ultimo lugar, si la tabla queda vacia). */
s32 func_80021C48(s32 n) {
    s16 i;

    D_8007CAF0 = n - 1;
    D_8007CAF2 = 0;
    D_8007CAF4 = Reservar(n * 2, D_8006C468, 0x2E);
    i = D_8007CAF0;
    if (i < 0) {
        return (u16)D_8007CAF0;
    }
    for (; i >= 0; i--) {
        D_8007CAF4[i] = (func_80014F10() & 0x7FFF) << 1;
    }
    return -1;
}
