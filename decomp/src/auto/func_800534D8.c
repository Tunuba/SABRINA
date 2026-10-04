#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086324[];
extern u8 D_80086328[];
extern s32 D_8007CA24;


void func_800534D8(s32 arg0) {
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;

    var_a1 = 0;
    var_v1 = 0;
loop_7:
    if (var_a1 >= D_8007CA24) {
        D_8007CA24 -= 1;
        thunk_FUN_8004866c(arg0);
        return;
    }
    if (arg0 == D_80086324[var_v1]) {
        var_a0 = var_a1 * 4;
loop_4:
        if (var_a1 < D_8007CA24) {
            var_a1 += 1;
            D_80086324[var_a0] = (s32) D_80086328[var_a0];
            var_a0 += 4;
            goto loop_4;
        }
        D_8007CA24 -= 1;
        return;
    }
    var_a1 += 1;
    var_v1 += 4;
    goto loop_7;
}
