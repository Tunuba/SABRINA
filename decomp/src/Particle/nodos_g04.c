#include "nodo.h"

/* Los 0xF0 nodos de piezas (D_8008AB78), hijos de D_8007C9F4. */

extern Nodo *func_8001E164(Nodo *padre);
extern void func_8001E2DC(Nodo *n, char *nombre);
extern Nodo *D_8007C9F4;
extern Nodo *D_8008AB78[];
extern char D_800688B4[];

void func_800206F0(void) {
    u8 i;

    for (i = 0; i != 0xF0; i++) {
        D_8008AB78[i] = func_8001E164(D_8007C9F4);
        func_8001E2DC(D_8008AB78[i], D_800688B4);
    }
}
