#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80048374(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_a3;
    s32 var_v0;

    temp_a2 = arg2 >> 8;
    temp_a3 = (s32) (M2C_FIELD(arg1, s32 *, 0x24) - M2C_FIELD(arg0, s32 *, 0x24)) >> 8;
    temp_a0 = (s32) (M2C_FIELD(arg1, s32 *, 0x2C) - M2C_FIELD(arg0, s32 *, 0x2C)) >> 8;
    var_v0 = 0;
    if (((s32) (temp_a2 * temp_a2) >> 8) >= (((s32) (temp_a3 * temp_a3) >> 8) + ((s32) (temp_a0 * temp_a0) >> 8))) {
        var_v0 = 1;
    }
    return var_v0;
}
