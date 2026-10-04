#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80090A98[];
extern u8 D_80090C78[];

s32 func_800282D8(s32 arg0) {
    s32 var_a1;
    s32 var_a3;
    s32 var_t2;
    u8 *var_a2;
    u8 *var_v1;

    var_a3 = 0x10;
    var_t2 = 0;
    var_a2 = D_80090A98;
loop_1:
    var_a1 = 0;
    if (arg0 == var_a2) {
        return var_a3;
    }
    var_v1 = D_80090C78;
loop_4:
    if (arg0 == &var_v1[var_t2]) {
        return var_a3 | (var_a1 + 1);
    }
    var_a1 += 1;
    var_v1 += 0xF0;
    if (var_a1 >= 4) {
        var_a3 += 0x10;
        var_a2 += 0xF0;
        var_t2 += 0x3C0;
        if ((s32) var_a2 >= (s32) (D_80090A98 + 0x1E0)) {
            return 0xFF;
        }
        goto loop_1;
    }
    goto loop_4;
}
