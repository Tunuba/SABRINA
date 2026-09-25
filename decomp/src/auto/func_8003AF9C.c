#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_8007CBD6;


s32 func_8003AF9C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s16 temp_a2;
    s16 temp_t0;
    s16 temp_t0_2;
    s16 temp_t1_2;
    s16 temp_t1_3;
    s16 temp_t2;
    s16 temp_t2_2;
    s16 var_a0;
    s16 var_a1;
    s16 var_v0_2;
    s16 var_v1;
    s32 temp_a0;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 var_fp;
    s32 var_s2;
    s32 var_s3;
    s32 var_s6;
    s32 var_v0;
    void *temp_a2_2;
    void *temp_s0;
    void *temp_t1;
    void *temp_v0_4;

    var_s3 = saved_reg_s3;
    temp_v0 = (s32) M2C_FIELD(arg0, s32 *, 0) >> 8;
    sp38 = temp_v0;
    var_s6 = 0;
    temp_v0_2 = (s32) M2C_FIELD(arg0, s32 *, 4) >> 8;
    sp3C = temp_v0_2;
    var_s2 = 0;
    temp_v0_3 = (s32) M2C_FIELD(arg0, s32 *, 8) >> 8;
    sp40 = temp_v0_3;
    sp44 = temp_v0;
    sp4C = temp_v0_3;
    sp48 = temp_v0_2 + 0x1E80;
    temp_s5 = (s32) M2C_FIELD(arg0, s32 *, 0) >> 8;
    temp_s4 = (s32) M2C_FIELD(arg0, s32 *, 8) >> 8;
    func_8003B38C(arg0, (s32) &sp38, (s32) &sp44);
    var_fp = 0;
loop_43:
    if (var_s6 < arg2) {
        var_s6 += 1;
        temp_t2 = *(arg3 + var_fp);
        var_fp += 2;
        temp_s0 = arg1 + (temp_t2 * 0x1C);
        temp_v0_4 = M2C_FIELD(temp_s0, void **, 0);
        var_v1 = M2C_FIELD(temp_v0_4, s16 *, 0);
        temp_a2 = M2C_FIELD(temp_v0_4, s16 *, 2);
        var_a0 = M2C_FIELD(temp_v0_4, s16 *, 4);
        var_v0_2 = var_v1;
        var_a1 = var_a0;
        if (var_v1 < var_v1) {

        } else if (var_v0_2 < var_v1) {

        }
        if (var_a0 < var_a0) {

        } else if (var_a1 < var_a0) {
            var_a1 = var_a0;
        }
        if (temp_a2 < temp_a2) {

        } else if (temp_a2 < temp_a2) {

        }
        temp_t1 = M2C_FIELD(temp_s0, void **, 4);
        temp_t0 = M2C_FIELD(temp_t1, s16 *, 0);
        temp_t2_2 = M2C_FIELD(temp_t1, s16 *, 2);
        temp_t1_2 = M2C_FIELD(temp_t1, s16 *, 4);
        if (temp_t0 < var_v1) {
            var_v1 = temp_t0;
        } else if (var_v0_2 < temp_t0) {
            var_v0_2 = temp_t0;
        }
        if (temp_t1_2 < var_a0) {
            var_a0 = temp_t1_2;
        } else if (var_a1 < temp_t1_2) {
            var_a1 = temp_t1_2;
        }
        if (temp_t2_2 < temp_a2) {

        } else if (temp_a2 < temp_t2_2) {

        }
        temp_a2_2 = M2C_FIELD(temp_s0, void **, 8);
        temp_t0_2 = M2C_FIELD(temp_a2_2, s16 *, 0);
        temp_t1_3 = M2C_FIELD(temp_a2_2, s16 *, 4);
        if (temp_t0_2 < var_v1) {
            var_v1 = temp_t0_2;
        } else if (var_v0_2 < temp_t0_2) {
            var_v0_2 = temp_t0_2;
        }
        if (temp_t1_3 < var_a0) {
            var_a0 = temp_t1_3;
        } else if (var_a1 < temp_t1_3) {
            var_a1 = temp_t1_3;
        }
        if ((temp_s5 >= var_v1) && (var_v0_2 >= temp_s5) && (temp_s4 >= var_a0) && (var_a1 >= temp_s4) && (func_8003A524(arg0, (s32) temp_s0) != 0)) {
            if (var_s2 == 0) {
                var_s3 = M2C_FIELD(arg0, s32 *, 0x34) - sp3C;
                if (var_s3 >= 0) {
                    var_s2 = 1;
                    sp50 = M2C_FIELD(arg0, s32 *, 0x3C);
                    sp54 = M2C_FIELD(arg0, s32 *, 0x40);
                    sp58 = M2C_FIELD(arg0, s32 *, 0x44);
                    sp5C = M2C_FIELD(arg0, s32 *, 0x30);
                    sp60 = M2C_FIELD(arg0, s32 *, 0x34);
                    sp64 = M2C_FIELD(arg0, s32 *, 0x38);
                    goto block_42;
                }
            } else {
                temp_a0 = M2C_FIELD(arg0, s32 *, 0x34);
                temp_v0_5 = temp_a0 - sp3C;
                if ((temp_v0_5 >= 0) && (temp_v0_5 < var_s3)) {
                    var_s3 = temp_v0_5;
                    var_s2 = 1;
                    sp5C = M2C_FIELD(arg0, s32 *, 0x30);
                    sp60 = temp_a0;
                    sp64 = M2C_FIELD(arg0, s32 *, 0x38);
                    sp50 = M2C_FIELD(arg0, s32 *, 0x3C);
                    sp54 = M2C_FIELD(arg0, s32 *, 0x40);
                    sp58 = M2C_FIELD(arg0, s32 *, 0x44);
block_42:
                    M2C_FIELD(arg0, u16 *, 0x48) = M2C_FIELD(temp_s0, u16 *, 0x16);
                }
            }
        }
        goto loop_43;
    }
    var_v0 = 0;
    if (var_s2 == 1) {
        M2C_FIELD(arg0, s32 *, 0x3C) = sp50;
        M2C_FIELD(arg0, s32 *, 0x40) = sp54;
        M2C_FIELD(arg0, s32 *, 0x44) = sp58;
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (sp5C << 8);
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) (sp60 << 8);
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) (sp64 << 8);
        var_v0 = 1;
        D_8007CBD6 = 1;
    }
    return var_v0;
}
