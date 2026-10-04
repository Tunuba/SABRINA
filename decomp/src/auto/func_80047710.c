#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C7960[];
extern u8 D_800C7994[];
extern u8 D_800C8450[];
extern u8 recogidos[];
extern s32 D_8007CC0C;


void func_80047710(void) {
    s16 temp_v0;
    s32 *temp_a1;
    s32 *var_t8;
    s32 temp_a2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_t9;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    u8 *temp_a0;
    u8 *var_s1;
    u8 *var_t7;

    var_s1 = D_800C7960;
    memset((s32) D_800C8450, 0, 0xC8);
    var_s0 = 0;
    var_s2 = 0;
    var_s3 = 0;
loop_13:
    if (var_s0 < D_8007CC0C) {
        temp_v0 = M2C_FIELD(var_s1, s16 *, 0x2A);
        if (temp_v0 != 2) {
            if (temp_v0 != 1) {
                var_v0 = -1;
                if (temp_v0 == 0) {
                    var_v0 = func_800479D8((s32) var_s1);
                }
            } else {
                var_v0 = func_800479E8((s32) var_s1);
            }
        } else {
            var_v0 = func_80047AA4((s32) var_s1);
        }
        if (var_v0 >= 0x38401) {
            var_v1 = 1;
            goto block_11;
        }
        if (var_v0 < 0) {
            var_v1 = 2;
block_11:
            D_800C8450[var_s2] = var_v1;
        }
        temp_a0 = &D_800C7994[var_s3];
        M2C_FIELD(*temp_a0, s16 *, 0x40) = 0x64;
        var_s0 += 1;
        M2C_FIELD(*temp_a0, s32 *, 4) = (s32) M2C_FIELD(var_s1, s32 *, 0);
        var_s3 += 0x38;
        M2C_FIELD(*temp_a0, s32 *, 8) = (s32) M2C_FIELD(var_s1, s32 *, 4);
        temp_v1 = M2C_FIELD(var_s1, s32 *, 8);
        var_s1 += 0x38;
        M2C_FIELD(*temp_a0, s32 *, 0xC) = temp_v1;
        var_s2 += 4;
        goto loop_13;
    }
    var_s0_2 = 0;
loop_28:
    if (var_s0_2 < D_8007CC0C) {
        temp_a1 = D_800C8450 + (var_s0_2 * 4);
        if (*temp_a1 != 0) {
            temp_v1_2 = var_s0_2 * 0x38;
            M2C_FIELD(*(D_800C7994 + temp_v1_2), s16 *, 0x40) = 1;
            if (*temp_a1 == 2) {
                M2C_FIELD(*(recogidos + temp_v1_2), s16 *, 0x1A) = 2;
            } else {
                M2C_FIELD(*(recogidos + temp_v1_2), s16 *, 0x1A) = 0;
            }
            temp_a2 = D_8007CC0C - 1;
            if (var_s0_2 < temp_a2) {
                var_v0_2 = var_s0_2;
                var_v1_2 = var_s0_2 + 1;
                var_a0 = var_s0_2 * 0x38;
                var_a1 = var_s0_2 * 4;
loop_24:
                if (var_v0_2 < temp_a2) {
                    var_t8 = D_800C7960 + (var_v1_2 * 0x38);
                    var_t7 = &D_800C7960[var_a0];
                    var_t9 = 0xE;
                    do {
                        var_t9 -= 1;
                        *var_t7 = (s32) *var_t8;
                        var_t8 += 4;
                        var_t7 += 4;
                    } while (var_t9 > 0);
                    var_v0_2 += 1;
                    D_800C8450[var_a1] = (s32) *(D_800C8450 + (var_v1_2 * 4));
                    var_a1 += 4;
                    var_a0 += 0x38;
                    var_v1_2 += 1;
                    goto loop_24;
                }
                var_s0_2 -= 1;
                D_8007CC0C -= 1;
            } else {
                D_8007CC0C = temp_a2;
            }
        }
        var_s0_2 += 1;
        goto loop_28;
    }
}
