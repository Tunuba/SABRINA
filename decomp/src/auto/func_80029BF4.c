#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006D030[];
extern s32 D_8006D304;
extern u8 D_8006D310;


void func_80029BF4(s32 arg0, s32 arg1) {
    s32 temp_s2;
    s32 temp_s4;
    s32 var_s0;

    var_s0 = 3;
    temp_s2 = arg0 & 0xFF;
    temp_s4 = D_8006D304;
loop_1:
    D_8006D304 = 0;
    if ((temp_s2 != 1) && (D_8006D310 & 0x10)) {
        func_8002AC18(1, 0, 0, 0);
    }
    if (((arg1 != 0) && (D_8006D030[temp_s2] != 0) && (func_8002AC18(2, arg1, 0, 0) != 0)) || (D_8006D304 = temp_s4, (func_8002AC18(arg0 & 0xFF, arg1, 0, 1) != 0))) {
        var_s0 -= 1;
        if (var_s0 == -1) {
            D_8006D304 = temp_s4;
        } else {
            goto loop_1;
        }
    }
}
