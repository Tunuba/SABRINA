#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_8007CB20;
extern s16 D_8007CB22;


void func_80022FD8(s32 arg0_reg, s32 arg1) {
    s8 arg0 = (s8) arg0_reg;
    D_8007CB20 = arg0;
    if (D_8007CB20 < 0) {
        D_8007CB20 = 0;
    }
    D_8007CB22 = (0x80 / arg1) * D_8007CB20;
    if (D_8007CB20 == arg1) {
        D_8007CB22 = 0x80;
    }
    if (D_8007CB22 < 0) {
        D_8007CB22 = 0;
    }
}
