#include "juego.h"

/* Mando: cortar la comunicacion de un puerto. */

extern s32 (*D_8006CF9C)(u8 *p);     /* deshabilitar las interrupciones del mando */
extern s32 D_8006CFEC;               /* lo que estaban */
extern s32 func_8002622C(u8 *p, s32 orden);

/* Guarda el estado de las interrupciones, limpia el primer byte del bufer del puerto y le manda la orden -2. */
s32 func_80027368(u8 *p) {
    D_8006CFEC = D_8006CF9C(p);
    **(u8 **)(p + 0x3C) = 0;
    return func_8002622C(p, -2);
}
