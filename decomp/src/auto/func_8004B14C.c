#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u32 D_8007CB3C;
extern s32 D_8007CB40;


void func_8004B14C(void) {
    s16 temp_v0;
    s32 var_a0;
    u32 var_v1;

    var_v1 = 0;
    var_a0 = 0;
loop_14:
    if (var_v1 < (u32) D_8007CB3C) {
        temp_v0 = M2C_FIELD((var_a0 + D_8007CB40), s16 *, 0xC);
        if ((temp_v0 == 0x29) || (temp_v0 == 0x28) || (temp_v0 == 0x18) || (temp_v0 == 8) || (temp_v0 == 0x11) || (temp_v0 == 0xF) || (temp_v0 == 2) || (temp_v0 == 0x2F) || (temp_v0 == 0x16) || (temp_v0 == 0x10) || (temp_v0 == 0xE)) {
            M2C_FIELD((var_a0 + D_8007CB40), s16 *, 0x1A) = 0;
        }
        var_v1 += 1;
        var_a0 += 0x9C;
        goto loop_14;
    }
}
