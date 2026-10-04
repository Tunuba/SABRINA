#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C98C4[];
extern u8 D_800C98C8[];
extern s32 D_8007CC1C;


void func_8004DAC4(s32 arg0) {
    s32 var_a1;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a3;

    var_a1 = 0;
    var_a2 = 0;
loop_4:
    if (var_a1 < 4) {
        if (arg0 == D_800C98C4[var_a2]) {
            *(D_800C98C4 + (var_a1 * 4)) = 0;
        } else {
            var_a1 += 1;
            var_a2 += 4;
            goto loop_4;
        }
    }
    var_a2_2 = var_a1 * 4;
    var_a3 = var_a1 + 1;
loop_7:
    if (var_a3 < 4) {
        D_800C98C4[var_a2_2] = (s32) D_800C98C8[var_a2_2];
        var_a3 += 1;
        var_a2_2 += 4;
        goto loop_7;
    }
    D_8007CC1C -= 1;
    thunk_FUN_8004866c(arg0);
}
