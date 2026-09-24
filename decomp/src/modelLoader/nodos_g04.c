#include "nodo.h"

/* Copia de arboles de nodos. */

extern Nodo *func_8001E164(Nodo *padre);   /* nodo nuevo en blanco, ultimo hijo de padre */
extern Nodo *func_8001E06C(Nodo *n, Nodo *padre);

#define CAMPO(tipo, n, desp) (*(tipo *)((u8 *)(n) + (desp)))

/* Copia el nodo n (y, por recursion, sus hijos y los hermanos que le siguen) como hijo de padre. Copia la
 * palabra 0, la matriz local, 0x54, el dibujo, visible, triangulos, 0x60 y los bytes 0x65 a 0x67; la matriz
 * de mundo y las banderas no. Devuelve la copia de n. */
Nodo *func_8001E06C(Nodo *n, Nodo *padre) {
    Nodo *c = func_8001E164(padre);
    s32 *de;
    s32 *a;
    s32 k;

    CAMPO(s32, c, 0x00) = CAMPO(s32, n, 0x00);
    CAMPO(s32, c, 0x54) = CAMPO(s32, n, 0x54);
    c->visible = n->visible;
    c->dibujo = n->dibujo;
    c->triangulos = n->triangulos;
    CAMPO(s16, c, 0x60) = CAMPO(s16, n, 0x60);
    CAMPO(u8, c, 0x65) = CAMPO(u8, n, 0x65);
    CAMPO(u8, c, 0x66) = CAMPO(u8, n, 0x66);
    CAMPO(u8, c, 0x67) = CAMPO(u8, n, 0x67);
    de = (s32 *)&n->local;
    a = (s32 *)&c->local;
    for (k = 8; k > 0; k--) {
        *a++ = *de++;
    }
    if (n->hijo != NULL) {
        func_8001E06C(n->hijo, c);
    }
    if (n->sig != NULL) {
        func_8001E06C(n->sig, padre);
    }
    return c;
}
