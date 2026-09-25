#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CB3C;
extern s32 D_8007CB40;
extern s32 D_8007CCAC;


void func_800249B8(void) {
    D_8007CB3C = 0;
    D_8007CCAC = 0;
    Liberar(D_8007CB40);
}
