#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8005CD98(s32 arg0) {
    s16 temp_v0;
    s16 var_s0;
    s16 var_s2;

    var_s2 = 0;
    var_s0 = 0;
loop_3:
    if (func_80029AB8(0x15, arg0, 0) != 0) {
        var_s2 = 0;
        var_s0 += 1;
        if (var_s0 == 5) {
            return 0;
        }
        if (func_8002CB2C(0x1C0) != 0) {
            return 1;
        }
        goto loop_3;
    }
    temp_v0 = var_s2 + 1;
    var_s2 = temp_v0;
    if (temp_v0 == 5) {
        return 0;
    }
    goto loop_3;
}
