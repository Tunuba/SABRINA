#include "nodo.h"

/* Entre loadtga.c y modelLoader.c (modulo sin nombre conocido). */

extern Nodo *D_80086368;
extern Nodo *D_8007C9F8;             /* nodo del mundo */
extern char D_8007C7D0[];            /* "gWorld" */
extern u8 D_8007CAE8;                /* secciones del .INO leidas */
extern void func_8001E2DC(Nodo *n, char *nombre);

/* Producto escalar de dos vectores de 32 bits en punto fijo 20.12, con la suma en 64 bits. */
s32 func_8001C1D4(s32 *a, s32 *b) {
    s64 suma = (s64)a[1] * b[1];

    suma += (s64)a[0] * b[0];
    suma += (s64)a[2] * b[2];
    return (s32)(suma >> 12);
}

/* Toma el nodo del mundo y le pone de nombre "gWorld". */
void func_8001C794(void) {
    D_8007C9F8 = D_80086368;
    func_8001E2DC(D_8007C9F8, D_8007C7D0);
    D_8007CAE8++;
}
