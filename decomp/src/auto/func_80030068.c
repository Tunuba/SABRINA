#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80030068(s32 arg0) {
    s32 temp_s0;
    s32 var_s0;

    var_s0 = 0;
    if (arg0 != 0) {
        temp_s0 = ((1 & 0xFFFF) + func_80030068(M2C_FIELD(arg0, s32 *, 8))) & 0xFFFF;
        var_s0 = (temp_s0 + func_80030068(M2C_FIELD(arg0, s32 *, 4))) & 0xFFFF;
    }
    return var_s0;
}
