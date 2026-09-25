#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8008AF88[];
extern u8 D_8008AFD8[];

s32 func_8002506C(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    u8 *var_s0;
    u8 *var_s7;

    var_s2 = 0x0FFFFFFF;
    temp_s5 = (s32) M2C_FIELD(arg0, s32 *, 0) >> 8;
    temp_s4 = (s32) M2C_FIELD(arg0, s32 *, 4) >> 8;
    var_s7 = NULL;
    temp_s3 = (s32) M2C_FIELD(arg0, s32 *, 8) >> 8;
    var_s0 = D_8008AFD8;
    if ((u32) arg1 >= 0x38U) {
        var_s1 = 0;
loop_7:
        if (var_s1 < 0x50) {
            if (((s8) D_8008AF88[var_s1] != 0) && (var_s0 != arg2)) {
                sp3C = ((s32) M2C_FIELD(var_s0, s32 *, 0x24) >> 8) - temp_s5;
                sp40 = ((s32) M2C_FIELD(var_s0, s32 *, 0x28) >> 8) - temp_s4;
                sp44 = ((s32) M2C_FIELD(var_s0, s32 *, 0x2C) >> 8) - temp_s3;
                temp_v0 = func_8001C33C((s32) &sp3C, (s32) &sp3C);
                if (temp_v0 < var_s2) {
                    var_s2 = temp_v0;
                    var_s7 = var_s0;
                }
            }
            var_s1 += 1;
            var_s0 += 0x120;
            goto loop_7;
        }
    } else {
        var_s1_2 = 0;
loop_16:
        if (var_s1_2 < 0x50) {
            if (((s8) D_8008AF88[var_s1_2] != 0) && (var_s0 != arg2) && (M2C_FIELD(var_s0, u16 *, 0x22) == arg1)) {
                sp3C = ((s32) M2C_FIELD(var_s0, s32 *, 0x24) >> 8) - temp_s5;
                sp40 = ((s32) M2C_FIELD(var_s0, s32 *, 0x28) >> 8) - temp_s4;
                sp44 = ((s32) M2C_FIELD(var_s0, s32 *, 0x2C) >> 8) - temp_s3;
                temp_v0_2 = func_8001C33C((s32) &sp3C, (s32) &sp3C);
                if (temp_v0_2 < var_s2) {
                    var_s2 = temp_v0_2;
                    var_s7 = var_s0;
                }
            }
            var_s1_2 += 1;
            var_s0 += 0x120;
            goto loop_16;
        }
    }
    return (s32) var_s7;
}
