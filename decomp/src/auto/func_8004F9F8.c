#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA20;
extern s32 D_8007CC44;
extern s16 D_8007CC56;


void func_8004F9F8(void) {
    D_8007CC44 = 1;
    D_8007CA20 = 0;
    D_8007CC56 = 0xF;
}
