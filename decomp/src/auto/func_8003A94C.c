#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8003A94C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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
    s32 sp68;
    s32 sp6C;
    s32 spA4;
    s32 spA8;
    s32 spAC;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_a3;
    s16 temp_a3_3;
    s16 temp_a3_5;
    s16 var_a0;
    s16 var_a1;
    s16 var_v0;
    s16 var_v1;
    s32 *var_t7;
    s32 temp_s4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_fp;
    s32 var_s2;
    s32 var_s3;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    s32 var_t8;
    s32 var_t9;
    void **temp_s1;
    void *temp_a3_2;
    void *temp_a3_4;
    void *temp_v1;

    var_s2 = saved_reg_s2;
    var_fp = 0;
    var_s3 = 0;
    var_t7 = &sp58;
    var_t9 = 0x13;
    var_t8 = arg0;
    do {
        var_t9 -= 1;
        *var_t7 = *var_t8;
        var_t8 += 4;
        var_t7 += 4;
    } while (var_t9 > 0);
    temp_v0 = sp58 >> 8;
    sp58 = temp_v0;
    temp_v0_2 = sp5C >> 8;
    sp5C = temp_v0_2;
    temp_v0_3 = sp60 >> 8;
    sp60 = temp_v0_3;
    sp64 = sp64 >> 8;
    sp68 = sp68 >> 8;
    sp6C = sp6C >> 8;
    sp40 = sp64 - temp_v0;
    sp44 = sp68 - temp_v0_2;
    sp48 = sp6C - temp_v0_3;
    var_s5 = sp58;
    temp_s4 = func_8001C33C((s32) &sp40, (s32) &sp40);
    sp38 = var_s5;
    if (sp64 < var_s5) {
        sp38 = sp64;
    } else {
        var_s5 = sp64;
    }
    var_s6 = sp60;
    var_s7 = var_s6;
    if (sp6C < var_s7) {
        var_s7 = sp6C;
    } else {
        var_s6 = sp6C;
    }
    sp3C = 0;
loop_44:
    if (var_fp < arg2) {
        var_fp += 1;
        temp_s1 = arg1 + (*(arg3 + sp3C) * 0x1C);
        temp_v1 = M2C_FIELD(temp_s1, void **, 0);
        temp_a3 = M2C_FIELD(temp_v1, s16 *, 4);
        temp_a2 = M2C_FIELD(temp_v1, s16 *, 0);
        sp3C += 2;
        var_v0 = temp_a2;
        var_a0 = temp_a3;
        var_v1 = temp_a2;
        var_a1 = temp_a3;
        if (temp_a2 < var_v0) {
            var_v0 = temp_a2;
        } else if (var_v1 < temp_a2) {

        }
        if (temp_a3 < var_a0) {
            var_a0 = temp_a3;
        } else if (var_a1 < temp_a3) {
            var_a1 = temp_a3;
        }
        temp_a3_2 = M2C_FIELD(temp_s1, void **, 4);
        temp_a2_2 = M2C_FIELD(temp_a3_2, s16 *, 0);
        temp_a3_3 = M2C_FIELD(temp_a3_2, s16 *, 4);
        if (temp_a2_2 < var_v0) {
            var_v0 = temp_a2_2;
        } else if (var_v1 < temp_a2_2) {
            var_v1 = temp_a2_2;
        }
        if (temp_a3_3 < var_a0) {
            var_a0 = temp_a3_3;
        } else if (var_a1 < temp_a3_3) {
            var_a1 = temp_a3_3;
        }
        temp_a3_4 = M2C_FIELD(temp_s1, void **, 8);
        temp_a2_3 = M2C_FIELD(temp_a3_4, s16 *, 0);
        temp_a3_5 = M2C_FIELD(temp_a3_4, s16 *, 4);
        if (temp_a2_3 < var_v0) {
            var_v0 = temp_a2_3;
        } else if (var_v1 < temp_a2_3) {
            var_v1 = temp_a2_3;
        }
        if (temp_a3_5 < var_a0) {
            var_a0 = temp_a3_5;
        } else if (var_a1 < temp_a3_5) {
            var_a1 = temp_a3_5;
        }
        if ((var_s5 >= var_v0) && (var_s6 >= var_a0) && (var_a1 >= var_s7) && (var_v1 >= sp38) && (func_8003A750((s32) &sp58, (s32) temp_s1) != 0)) {
            if (var_s3 == 0) {
                spA4 = sp88 - sp58;
                spA8 = sp8C - sp5C;
                spAC = sp90 - sp60;
                var_s2 = func_8001C33C((s32) &spA4, (s32) &spA4);
                if (var_s2 < temp_s4) {
                    sp40 = sp94;
                    sp44 = sp98;
                    sp48 = sp9C;
                    sp4C = sp88;
                    sp50 = sp8C;
                    sp54 = sp90;
                    var_s3 = 1;
                    goto block_43;
                }
            } else {
                spA4 = sp88 - sp58;
                spA8 = sp8C - sp5C;
                spAC = sp90 - sp60;
                temp_v0_4 = func_8001C33C((s32) &spA4, (s32) &spA4);
                if ((temp_v0_4 < temp_s4) && (temp_v0_4 < var_s2)) {
                    var_s2 = temp_v0_4;
                    sp40 = sp94;
                    sp44 = sp98;
                    sp48 = sp9C;
                    sp4C = sp88;
                    sp50 = sp8C;
                    sp54 = sp90;
block_43:
                    M2C_FIELD(arg0, u16 *, 0x48) = M2C_FIELD(temp_s1, u16 *, 0x16);
                }
            }
        }
        goto loop_44;
    }
    if (var_s3 != 0) {
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (sp4C << 8);
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) (sp50 << 8);
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) (sp54 << 8);
        M2C_FIELD(arg0, s32 *, 0x3C) = sp40;
        M2C_FIELD(arg0, s32 *, 0x40) = sp44;
        M2C_FIELD(arg0, s32 *, 0x44) = sp48;
    }
    return var_s3;
}
