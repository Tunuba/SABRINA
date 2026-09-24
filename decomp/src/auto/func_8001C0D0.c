#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8001C0D0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 var_v0;

    temp_s2 = func_80014AEC(arg0);
    temp_s0 = func_80014AEC(arg1);
    temp_s1 = func_80014AEC(arg2);
    if (temp_s0 < temp_s2) {
        if (temp_s1 < temp_s2) {
            return temp_s2 + ((s32) (temp_s0 + temp_s1) >> 2);
        }
        var_v0 = (s32) (temp_s0 + temp_s2) >> 2;
        goto block_7;
    }
    if (temp_s1 < temp_s0) {
        return temp_s0 + ((s32) (temp_s2 + temp_s1) >> 2);
    }
    var_v0 = (s32) (temp_s0 + temp_s2) >> 2;
block_7:
    return temp_s1 + var_v0;
}
