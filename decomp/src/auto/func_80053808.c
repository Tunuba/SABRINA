#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086338[];
extern s32 D_8007CA28;


void func_80053808(s32 arg0) {
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;

    var_a2 = 0;
loop_7:
    if (var_a2 < D_8007CA28) {
        var_t0 = var_a2 * 4;
        if (*(D_80086338 + var_t0) == arg0) {
            var_a3 = var_a2 + 1;
loop_4:
            if (var_a2 < D_8007CA28) {
                var_a2 += 1;
                D_80086338[var_t0] = (s32) *(D_80086338 + (var_a3 * 4));
                var_t0 += 4;
                var_a3 += 1;
                goto loop_4;
            }
            D_8007CA28 -= 1;
        }
        var_a2 += 1;
        goto loop_7;
    }
    thunk_FUN_8004866c(arg0);
}
