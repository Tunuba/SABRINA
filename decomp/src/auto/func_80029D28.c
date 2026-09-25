#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006D030[];
extern s32 D_8006D304;
extern u8 D_8006D310;


s32 func_80029D28(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s3;
    s32 temp_s5;
    s32 var_s0;
    s32 var_v0;

    var_s0 = 3;
    temp_s3 = arg0 & 0xFF;
    temp_s5 = D_8006D304;
loop_1:
    D_8006D304 = 0;
    if ((temp_s3 != 1) && (D_8006D310 & 0x10)) {
        func_8002AC18(1, 0, 0, 0);
    }
    if (((arg1 != 0) && (D_8006D030[temp_s3] != 0) && (func_8002AC18(2, arg1, arg2, 0) != 0)) || (D_8006D304 = temp_s5, var_v0 = 0, (func_8002AC18(arg0 & 0xFF, arg1, arg2, 0) != 0))) {
        var_s0 -= 1;
        var_v0 = -1;
        if (var_s0 == -1) {
            D_8006D304 = temp_s5;
        } else {
            goto loop_1;
        }
    }
    if (var_v0 == 0) {
        return func_8002A6D0(0, arg2) == 2;
    }
    return 0;
}
