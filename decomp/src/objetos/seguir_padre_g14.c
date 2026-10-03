#include "juego.h"

/* Un objeto que se pega a otro (el de 0x74). */

#define C(o, d) (*(s32 *)((u8 *)(o) + (d)))

/* Copia la posicion del otro, pone la altura en su 0x50 y la escala en 0x1000 menos la diferencia de altura
 * / 32; si la escala del otro es menor que 1000 toma la del otro. Lee todo antes de escribir, como el
 * original (cuenta si los dos objetos se pisan). Devuelve lo que el original deja en v0. */
s32 func_80053400(u8 *o) {
    u8 *p = *(u8 **)(o + 0x74);
    s32 x = C(p, 0x24), y = C(p, 0x28), z = C(p, 0x2C);
    s32 e;

    C(o, 0x24) = x;
    C(o, 0x28) = y;
    C(o, 0x2C) = z;
    C(o, 0x28) = C(*(u8 **)(o + 0x74), 0x50);
    e = RESTA_TRAMPA(0x1000, RESTA_TRAMPA(C(o, 0x28), C(*(u8 **)(o + 0x74), 0x28)) >> 5);
    C(o, 0x54) = e;
    C(o, 0x5C) = e;
    p = *(u8 **)(o + 0x74);
    x = C(p, 0x54);
    if (x < 0x3E8) {
        y = C(p, 0x58);
        z = C(p, 0x5C);
        C(o, 0x54) = x;
        C(o, 0x58) = y;
        C(o, 0x5C) = z;
        return z;
    }
    return (s32)p;
}
