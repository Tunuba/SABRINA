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

extern s32 func_8001C33C(s32 *a, s32 *b);  /* producto escalar de dos vectores */

/* Producto escalar de (ax, ay, az) y (bx, by, bz): los argumentos quedan seguidos en la pila del que llama
 * y se pasan como dos vectores. */
s32 func_8001C390(s32 ax, ...) {
    /* variadica: GCC deja los argumentos en su lugar de la pila del que llama, seguidos */
    __builtin_va_list ap;

    __builtin_va_start(ap, ax);
    return func_8001C33C(&ax, &ax + 3);
}

extern s32 func_8001C280(s32 *a, s32 *b);

/* Como func_8001C390, con func_8001C280: los dos vectores son los argumentos seguidos en la pila. */
s32 func_8001C2D0(s32 ax, ...) {
    __builtin_va_list ap;

    __builtin_va_start(ap, ax);
    return func_8001C280(&ax, &ax + 3);
}
