#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80053B98(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4_reg) {
    u8 arg4 = (u8) arg4_reg;
    s32 var_v0;

    if (arg1 < M2C_FIELD(arg0, s32 *, 0)) {
        return 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0xC) < arg1) {
        return 0;
    }
    if (arg3 < M2C_FIELD(arg0, s32 *, 8)) {
        return 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x14) < arg3) {
        return 0;
    }
    if (arg4 == 1) {
        return 1;
    }
    if (arg2 < M2C_FIELD(arg0, s32 *, 4)) {
        return 0;
    }
    var_v0 = 1;
    if (M2C_FIELD(arg0, s32 *, 0x10) < arg2) {
        var_v0 = 0;
    }
    return var_v0;
}
