#include "juego.h"

/* El arranque: los constructores globales y la entrada al bucle principal. */

typedef void (*Constructor)(void);

extern Constructor D_800609B0[];     /* los constructores globales, terminan en NULL */
extern void *D_8007C9D8;
extern u8 D_80060A58[], D_800758CC[], D_8007CCB0[];
extern void func_80010670(void);
extern s32 func_80017C6C(void **p, void (*f)(void), void *q);
extern void BuclePrincipal(void);

/* Llama a los constructores globales y entra al bucle principal. */
void func_800106C8(void) {
    Constructor *c;

    for (c = D_800609B0; *c != NULL; c++) {
        (*c)();
    }
    BuclePrincipal();
}

/* Anota el objeto global (primero D_80060A58 y enseguida D_800758CC) y registra su destructor. */
s32 func_80010000(void) {
    D_8007C9D8 = D_80060A58;
    *(void * volatile *)&D_8007C9D8 = D_800758CC;
    return func_80017C6C(&D_8007C9D8, func_80010670, D_8007CCB0);
}

extern void func_80017CE4(void *p);  /* delete */

/* El destructor del objeto global: le pone su tabla de funciones y, si se pide, libera la memoria. */
void *func_8001062C(void **p, s32 liberar) {
    if (p != NULL) {
        *p = D_80060A58;
        if (liberar > 0) {
            func_80017CE4(p);
        }
    }
    return p;
}
