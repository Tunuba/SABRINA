#include "juego.h"

/* El arranque: los constructores globales y la entrada al bucle principal. */

typedef void (*Constructor)(void);

extern Constructor D_800609B0[];     /* los constructores globales, terminan en NULL */
extern void *D_8007C9D8;
extern u8 D_80060A58[], D_800758CC[], D_8007CCB0[];
extern void *func_80010670(void **p, s32 liberar);
extern s32 func_80017C6C(void **p, void (*f)(void), void *q);
extern void BuclePrincipal(void);

/* Llama a los constructores globales y entra al bucle principal. */
void func_800106C8(void) {
    Constructor *c;

    for (c = D_800609B0; *c != NULL; c++) {
        (*c)();
    }
    BuclePrincipal();
    /* 08-10: la original llama con jal y conserva su marco; sin esto GCC salta al final ya sin marco y el bucle
     * corre 0x18 bytes mas arriba en la pila (D_8007C9DC, el objeto del juego en su pila, quedaba distinto) */
    __asm__ volatile("");
}

/* Anota el objeto global (primero D_80060A58 y enseguida D_800758CC) y registra su destructor. */
s32 func_80010000(void) {
    D_8007C9D8 = D_80060A58;
    *(void * volatile *)&D_8007C9D8 = D_800758CC;
    return func_80017C6C(&D_8007C9D8, (void (*)(void))func_80010670, D_8007CCB0);
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

extern u8 D_800758CC[];

/* Igual que func_8001062C pero de una clase hija: pone primero su tabla (D_800758CC) y despues la de la
   base, como un destructor de C++. */
void *func_80010670(void **p, s32 liberar) {
    if (p != NULL) {
        *p = D_800758CC;
        if (p != NULL) {
            *p = D_80060A58;
        }
        if (liberar > 0) {
            func_80017CE4(p);
        }
    }
    return p;
}

extern u8 D_800758F8[], D_80075900[];

/* Destructor de un objeto con dos tablas (en +8 y en +4); la de +4 vuelve a la base al final. */
void *func_8004E6C0(u8 *p, s32 liberar) {
    if (p != NULL) {
        *(void **)(p + 8) = D_800758F8;
        *(void **)(p + 4) = D_80075900;
        if (p + 4 != NULL) {
            *(void **)(p + 4) = D_80060A58;
        }
        if (liberar > 0) {
            func_80017CE4(p);
        }
    }
    return p;
}

/* Llamada virtual de C++: la entrada 0x30 de la tabla de p (en p+8), con los mismos argumentos. */
s32 func_8004E2CC(u8 *p, s32 a, s32 b, s32 c) {
    return (*(s32 (**)(u8 *, s32, s32, s32))(*(u8 **)(p + 8) + 0x30))(p, a, b, c);
}
