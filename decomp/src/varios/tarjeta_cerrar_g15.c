#include "juego.h"

/* Deja la tarjeta de memoria en reposo: pone el contador en 0xF2 y borra los pasos pendientes; si estaba en
 * la operacion 2, la cierra (func_80051764), espera que termine (func_80051298) y marca D_8007CC44 en 2. */

extern s16 D_8007CA20;
extern u16 D_8007CC56;
extern s16 D_8007CC5A;
extern s16 D_8007CC58;
extern s16 D_8007CC4E;
extern s32 D_8007CC44;

extern void func_80051764(void);
extern s32 func_80051298(s32 sin_esperar, s32 *resultado, s32 *dato);

void func_8004F50C(void) {
    s32 dato;

    D_8007CA20 = 0xF2;
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC4E = 0;
    if (D_8007CC56 == 2) {
        func_80051764();
        func_80051298(0, 0, &dato);
        D_8007CC44 = 2;
        D_8007CA20 = 0;
    }
}
