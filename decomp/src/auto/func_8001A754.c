#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006561C[];


s32 func_8001A754(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    u32 sp48;
    s32 sp4C;
    s16 temp_s4;
    s16 temp_s4_2;
    s16 temp_s5;
    s16 temp_s5_2;
    s16 temp_v1_2;
    s16 temp_v1_4;
    s16 var_fp_2;
    s16 var_s6;
    s16 var_s6_2;
    s16 var_s7;
    s32 temp_a3;
    s32 temp_s7;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_s2_4;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_t9;
    s32 var_v0;
    s32 var_v1;
    u16 temp_v0;
    u32 var_a0;
    u32 var_a0_2;
    u32 var_fp;
    u32 var_s2;
    u32 var_s2_2;
    u8 var_s0;
    u8 var_s2_3;
    void *temp_a0;
    void *temp_v1;
    void *temp_v1_3;

    var_s6 = 1;
    var_s0 = 0;
    sp3C = Reservar(arg3, (s32) D_8006561C);
    var_t9 = arg3 >> 1;
    if (arg3 < 0) {
        var_t9 = (s32) (arg3 + 1) >> 1;
    }
    sp40 = Reservar(var_t9, (s32) D_8006561C);
    sp48 = 0;
loop_4:
    if (sp48 != arg3) {
        *(sp3C + sp48) = 0;
        sp48 += 1;
        goto loop_4;
    }
    sp48 = 0;
    var_v0 = 0;
    var_v1 = 0;
loop_14:
    if (sp48 != arg3) {
        if (*(sp3C + sp48) == 0) {
            var_s2 = sp48;
            *(arg2 + var_v1) = *(arg1 + var_v0);
            temp_a3 = sp48 * 2;
            var_a2 = temp_a3;
loop_11:
            if (var_s2 < (u32) arg3) {
                if (*(arg1 + temp_a3) == *(arg1 + var_a2)) {
                    *(sp3C + var_s2) = 1;
                }
                var_s2 += 1;
                var_a2 += 2;
                goto loop_11;
            }
            var_s0 += 1;
            var_v1 += 2;
        }
        var_v0 += 2;
        sp48 += 1;
        goto loop_14;
    }
loop_39:
    if ((u16) M2C_FIELD(arg0, u16 *, 0x1A) < var_s0) {
        sp48 = 0;
        var_fp = 1;
loop_36:
        if ((sp48 < var_s0) && (var_s0 != M2C_FIELD(arg0, u16 *, 0x1A))) {
            var_s2_2 = var_fp;
            var_s3 = var_fp * 2;
            temp_s7 = sp48 * 2;
loop_33:
            if ((var_s2_2 < var_s0) && (var_s0 != M2C_FIELD(arg0, u16 *, 0x1A))) {
                temp_v0 = *(arg2 + temp_s7);
                if ((temp_v0 == 0) || (*(arg2 + var_s3) == 0)) {
                    if (temp_v0 == *(arg2 + var_s3)) {
                        var_a0 = var_s2_2;
                        var_a1 = var_s2_2 * 2;
loop_23:
                        if (var_a0 < (u32) (var_s0 - 1)) {
                            temp_v1 = var_a1 + arg2;
                            var_a0 += 1;
                            M2C_FIELD(temp_v1, u16 *, 0) = (u16) M2C_FIELD(temp_v1, u16 *, 2);
                            var_a1 += 2;
                            goto loop_23;
                        }
                        goto block_31;
                    }
                } else {
                    temp_s5 = func_80014AEC((s32) (temp_v0 & 0x7C00) >> 0xA) - ((s32) (*(arg2 + var_s3) & 0x7C00) >> 0xA);
                    temp_s4 = func_80014AEC((s32) (*(arg2 + temp_s7) & 0x3C0) >> 5) - ((s32) (*(arg2 + var_s3) & 0x3C0) >> 5);
                    temp_v1_2 = func_80014AEC(*(arg2 + temp_s7) & 0x1F) - (*(arg2 + var_s3) & 0x1F);
                    if ((var_s6 >= temp_s5) && (var_s6 >= temp_s4) && (var_s6 >= temp_v1_2)) {
                        var_a0_2 = var_s2_2;
                        var_a1_2 = var_s2_2 * 2;
loop_30:
                        if (var_a0_2 < (u32) (var_s0 - 1)) {
                            temp_v1_3 = var_a1_2 + arg2;
                            var_a0_2 += 1;
                            M2C_FIELD(temp_v1_3, u16 *, 0) = (u16) M2C_FIELD(temp_v1_3, u16 *, 2);
                            var_a1_2 += 2;
                            goto loop_30;
                        }
block_31:
                        var_s0 -= 1;
                    }
                }
                var_s2_2 += 1;
                var_s3 += 2;
                goto loop_33;
            }
            var_fp += 1;
            sp48 += 1;
            goto loop_36;
        }
        var_s6 += 1;
        goto loop_39;
    }
    sp48 = 0;
loop_52:
    if (sp48 != arg3) {
        var_s6_2 = 0xA;
        var_s7 = 0xA;
        var_fp_2 = 0xA;
        sp44 = 0;
        var_s2_3 = 0;
        var_s3_2 = 0;
        sp4C = sp48 * 2;
loop_49:
        if ((var_s2_3 != M2C_FIELD(arg0, u16 *, 0x1A)) && (sp44 == 0)) {
            temp_s5_2 = func_80014AEC(((s32) (*(arg1 + sp4C) & 0x7C00) >> 0xA) - ((s32) (*(arg2 + var_s3_2) & 0x7C00) >> 0xA));
            temp_s4_2 = func_80014AEC(((s32) (*(arg1 + sp4C) & 0x3C0) >> 5) - ((s32) (*(arg2 + var_s3_2) & 0x3C0) >> 5));
            temp_v1_4 = func_80014AEC((*(arg1 + sp4C) & 0x1F) - (*(arg2 + var_s3_2) & 0x1F));
            if ((var_fp_2 >= temp_s5_2) && (var_s7 >= temp_s4_2) && (var_s6_2 >= temp_v1_4)) {
                var_fp_2 = temp_s5_2;
                var_s7 = temp_s4_2;
                var_s6_2 = temp_v1_4;
                if ((temp_v1_4 + (temp_s5_2 + temp_s4_2)) <= 0) {
                    sp44 = 1;
                }
                var_s0 = var_s2_3;
            }
            var_s2_3 += 1;
            var_s3_2 += 2;
            goto loop_49;
        }
        *(sp3C + sp48) = var_s0;
        sp48 += 1;
        goto loop_52;
    }
    if (M2C_FIELD(arg0, u8 *, 0x1D) == 0) {
        sp48 = 0;
        var_s2_4 = 0;
loop_56:
        if (sp48 < (u32) arg3) {
            temp_a0 = sp48 + sp3C;
            *(sp40 + var_s2_4) = M2C_FIELD(temp_a0, u8 *, 0) | (M2C_FIELD(temp_a0, u8 *, 1) * 0x10);
            var_s2_4 += 1;
            sp48 += 2;
            goto loop_56;
        }
        Liberar(sp3C);
        Liberar(arg1);
        return sp40;
    }
    Liberar(sp40);
    Liberar(arg1);
    return sp3C;
}
