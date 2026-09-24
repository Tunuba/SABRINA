#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8001C004(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;
    s32 var_v1;

    temp_s1 = func_80014AEC(arg0 - arg3);
    temp_s0 = func_80014AEC(arg1 - arg4);
    temp_v0 = func_80014AEC(arg2 - arg5);
    if (temp_s0 < temp_s1) {
        if (temp_v0 < temp_s1) {
            return temp_s1 + ((s32) (temp_s0 + temp_v0) >> 2);
        }
        var_v1 = (s32) (temp_s0 + temp_s1) >> 2;
        goto block_7;
    }
    if (temp_v0 < temp_s0) {
        return temp_s0 + ((s32) (temp_s1 + temp_v0) >> 2);
    }
    var_v1 = (s32) (temp_s0 + temp_s1) >> 2;
block_7:
    return temp_v0 + var_v1;
}
