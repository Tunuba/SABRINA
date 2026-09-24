#include "objeto.h"

/* Choque entre dos formas de colision (ver forma.c). Cada par de tipos tiene su prueba y la forma de tipo
 * menor va primero; si son del mismo tipo van al reves (b, a). Devuelven 1 si se tocan. */

extern s32 func_80039D4C(Forma *a, Forma *b);    /* tipo 3 con tipo 3 */
extern s32 func_80039DD0(Forma *a, Forma *b);    /* tipo 2 con tipo 3 */
extern s32 func_80039EBC(Forma *a, Forma *b);    /* tipo 1 con tipo 3 */
extern s32 func_80039FA4(Forma *a, Forma *b);    /* tipo 2 con tipo 2 */
extern s32 func_8003A070(Forma *a, Forma *b);    /* tipo 1 con tipo 2 */
extern s32 func_8003A17C(Forma *a, Forma *b);    /* tipo 1 con tipo 1 */

extern s32 func_8001C33C(s32 *a, s32 *b);        /* con el mismo vector dos veces, su largo */

/* Si las banderas de a (_20) coinciden con las de b, prueba el choque segun los tipos; si no, 0. */
s32 func_80039BC8(Forma *a, Forma *b) {
    if (a->_20 & b->banderas) {
        switch (a->tipo) {
        case 3:
            switch (b->tipo) {
            case 3:
                return func_80039D4C(a, b);
            case 2:
                return func_80039DD0(b, a);
            case 1:
                return func_80039EBC(b, a);
            }
            break;
        case 2:
            switch (b->tipo) {
            case 3:
                return func_80039DD0(a, b);
            case 2:
                return func_80039FA4(b, a);
            case 1:
                return func_8003A070(b, a);
            }
            break;
        case 1:
            switch (b->tipo) {
            case 3:
                return func_80039EBC(b, a);
            case 2:
                return func_8003A070(a, b);
            case 1:
                return func_8003A17C(b, a);
            }
            break;
        }
    }
    return 0;
}

/* Tipo 1 (a: medio alto en m[0], radio en m[1]) contra tipo 2 (b: medio alto en m[0], radio en m[2]).
 * Se tocan si la distancia en x-z es menor que la suma de los radios y las alturas se cruzan. */
s32 func_8003A070(Forma *a, Forma *b) {
    s32 v[3];
    s32 radios;
    s32 ya, ha;

    v[1] = 0;
    v[0] = (a->centro[0] - b->centro[0]) >> 8;
    v[2] = (a->centro[2] - b->centro[2]) >> 8;
    radios = (a->m[1] + b->m[2]) >> 8;
    if (func_8001C33C(v, v) >= radios) {
        return 0;
    }
    ya = a->centro[1];
    ha = a->m[0];
    if (b->centro[1] < ya - ha) {
        return 0;
    }
    if (ya + ha < b->centro[1] - b->m[0]) {
        return 0;
    }
    return 1;
}

/* Tipo 1 contra tipo 1: se tocan si la distancia no pasa de la suma de los radios (m[1]). */
s32 func_8003A17C(Forma *a, Forma *b) {
    s32 v[3];
    s32 d;

    v[0] = (a->centro[0] - b->centro[0]) >> 8;
    v[1] = (a->centro[1] - b->centro[1]) >> 8;
    v[2] = (a->centro[2] - b->centro[2]) >> 8;
    d = func_8001C33C(v, v);
    if (((b->m[1] + a->m[1]) >> 8) < d) {
        return 0;
    }
    return 1;
}
