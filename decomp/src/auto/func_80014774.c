#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80084B0C;
extern u8 D_80084B14;
extern s32 func_80014670();

s32 func_80014774(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_v1;
    s32 var_v1_2;
    u32 temp_v1;
    u32 temp_v1_2;
    u32 var_s0;
    u32 var_s0_2;
    u8 *var_a0;
    u8 temp_v0;

    var_a0 = &D_80084B14;
    var_v1 = arg0;
    if (*arg0 >= 0x3B) {
        do {
            temp_v0 = *var_v1;
            var_v1 += 1;
            *var_a0 = temp_v0;
            var_a0 += 1;
        } while (*var_v1 >= 0x3B);
    }
    *var_a0 = 0;
    var_s0 = *(u32 *)0x150;
    temp_v1 = var_s0 + ((*(s32 *)0x154 / 80) * 0x50);
    if (var_s0 < temp_v1) {
loop_4:
        temp_a0 = M2C_FIELD(var_s0, s32 *, 0);
        if ((temp_a0 == 0) || (strcmp(temp_a0, (s32) &D_80084B14) != 0)) {
            var_s0 += 0x50;
            if (var_s0 >= temp_v1) {
                goto block_7;
            }
            goto loop_4;
        }
        D_80084B0C = M2C_FIELD(var_s0, s32 *, 0x34);
        var_v1_2 = 1;
    } else {
block_7:
        var_v1_2 = 0;
    }
    if (var_v1_2 == 0) {
        return 0;
    }
    var_s0_2 = *(void *)0x150;
    temp_v1_2 = var_s0_2 + ((*(void *)0x154 / 80) * 0x50);
    if (var_s0_2 < temp_v1_2) {
loop_14:
        temp_a0_2 = M2C_FIELD(var_s0_2, s32 *, 0);
        if ((temp_a0_2 == 0) || (strcmp(temp_a0_2, (s32) &D_80084B14) != 0)) {
            var_s0_2 += 0x50;
            if (var_s0_2 < temp_v1_2) {
                goto loop_14;
            }
        } else {
            M2C_FIELD(var_s0_2, s32 (**)(s32, s32, s32), 0x34) = func_80014670;
        }
    }
    return firstfile2();
}
