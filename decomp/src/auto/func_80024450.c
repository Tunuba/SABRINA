#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006CBE0[];
extern u8 D_8006CCE4[];
extern u8 D_8006CDD4[];
extern u8 D_8007C86C[];
extern u8 D_8007C9D4[];

u8 D_8006CDD4[0x3C];                                /* unable to generate initializer: cannot parse D_8006CBE0 as integer */

void func_80024450(s32 arg0, s32 arg1) {
    s32 sp20;
    M2C_UNK sp1B4;
    s32 sp234;
    s32 temp_a0;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_s0;

    sp20 = 0;
    temp_s0 = *(D_8006CDD4 + (arg0 * 4));
    do {
        sprintf((s32) &sp1B4, (s32) D_8007C86C, D_8007C9D4, *(temp_s0 + (sp20 * 4)));
        if (*(temp_s0 + (sp20 * 4)) != 0) {
            temp_v0 = func_8001B0C8((s32) &sp1B4);
            temp_a0 = sp20;
            sp20 = temp_a0 + 1;
            M2C_FIELD((sp + (temp_a0 * 4)), s32 *, 0x24) = temp_v0;
        }
    } while (*(temp_s0 + (sp20 * 4)) != 0);
    func_80029530(arg1, (s32) &sp20);
    var_s0 = 0;
    sp234 = 0;
loop_6:
    if (var_s0 != sp20) {
        func_80029530(arg1, M2C_FIELD((sp + sp234), s32 *, 0x24));
        var_s0 += 1;
        sp234 += 4;
        goto loop_6;
    }
}
