#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8002244C(s32 arg0) {
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 var_v0;

    sp1C = M2C_FIELD(arg0, s32 *, 0x24);
    sp20 = M2C_FIELD(arg0, s32 *, 0x28);
    sp24 = M2C_FIELD(arg0, s32 *, 0x2C);
    var_v0 = 0;
    if (func_8003AF48((s32) &sp1C) != 0) {
        M2C_FIELD(arg0, s32 *, 0x50) = sp50;
        var_v0 = M2C_FIELD(arg0, s32 *, 0x50);
    }
    return var_v0;
}
