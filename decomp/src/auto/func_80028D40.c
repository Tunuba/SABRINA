#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



static M2C_UNK (*D_8006CF88)(void *, u8) = NULL;

void func_80028D40(void *arg0) {
    s32 var_s2;
    u32 temp_s3;
    u8 temp_a0;
    u8 temp_a1;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 var_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *var_a0;
    void *var_s0;
    void *var_s0_2;

    temp_s3 = (u8) *M2C_FIELD(arg0, u8 **, 0x3C) >> 4;
    if (M2C_FIELD(arg0, u8 *, 0xE8) != 8) {
        if ((temp_s3 == 8) && (arg0 == M2C_FIELD(arg0, void **, 0x10))) {
            M2C_FIELD(arg0, u8 *, 0xE8) = (u8) temp_s3;
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s8 *, 0) = 0xFF;
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s8 *, 1) = 0x80;
            M2C_FIELD(arg0, s8 *, 0x35) = 2;
        }
        if (M2C_FIELD(arg0, u8 *, 0xE8) == 8) {
            goto block_5;
        }
    } else {
block_5:
        var_s0 = M2C_FIELD(arg0, void **, 0xC);
        var_a0 = var_s0;
        if (var_s0 != NULL) {
            var_s2 = 0;
            do {
                var_s0 += 0xF0;
                func_80028D40(var_a0, -1);
                var_s2 += 1;
                var_a0 = var_s0;
            } while (var_s2 < 4);
        }
    }
    var_s0_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, 0xC);
    if (M2C_FIELD(arg0, void **, 0xC) != NULL) {
        if ((M2C_FIELD(arg0, u8 *, 0x37) != 0) || ((temp_s0 = var_s0_2 + 0xF0, (M2C_FIELD(var_s0_2, u8 *, 0x38) == 0)) && (temp_s0_2 = temp_s0 + 0xF0, (M2C_FIELD(temp_s0, u8 *, 0x38) == 0)) && (M2C_FIELD(temp_s0_2, u8 *, 0x38) == 0) && (M2C_FIELD((temp_s0_2 + 0xF0), u8 *, 0x38) == 0))) {
            var_s0_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, 0xC);
            if (M2C_FIELD(arg0, void **, 0xC) == NULL) {
                goto block_15;
            }
            goto block_23;
        }
        goto block_21;
    }
block_15:
    if ((M2C_FIELD(arg0, u8 *, 0x38) == 0) && ((M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), u8 *, 0x37) != 0) || (temp_s0_3 = var_s0_2 + 0xF0, (M2C_FIELD(var_s0_2, u8 *, 0x38) != 0)) || (temp_s0_4 = temp_s0_3 + 0xF0, (M2C_FIELD(temp_s0_3, u8 *, 0x38) != 0)) || (M2C_FIELD(temp_s0_4, u8 *, 0x38) != 0) || (M2C_FIELD((temp_s0_4 + 0xF0), u8 *, 0x38) != 0))) {
block_21:
        if (M2C_FIELD(arg0, u8 *, 0x4A) == 0) {
            M2C_FIELD(arg0, u8 *, 0x4A) = 1U;
        }
    } else {
block_23:
        temp_v0 = M2C_FIELD(arg0, u8 *, 0x37);
        temp_a1 = M2C_FIELD(arg0, u8 *, 0x46);
        M2C_FIELD(arg0, u8 *, 0x37) = 0U;
        M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) + 1);
        M2C_FIELD(arg0, u8 *, 0x39) = (u8) M2C_FIELD(arg0, u8 *, 0x38);
        M2C_FIELD(arg0, u8 *, 0x38) = temp_v0;
        if (temp_a1 != 0) {
            if (temp_a1 == 1) {
                temp_a0 = M2C_FIELD(arg0, u8 *, 0x4A);
                if ((temp_a0 < 0xBU) && (M2C_FIELD(arg0, u8 *, 0xE8) != 8)) {
                    M2C_FIELD(arg0, u8 *, 0x4A) = (u8) (temp_a0 + 1);
                    return;
                }
                if (M2C_FIELD(arg0, u16 *, 0xE6) != 0) {
                    temp_v1 = M2C_FIELD(arg0, u8 *, 0x4A);
                    var_v0 = temp_v1 + 1;
                    if (temp_v1 >= 0x15U) {
                        D_8006CF88(arg0, temp_a1);
                        goto block_31;
                    }
                    goto block_37;
                }
block_31:
                M2C_FIELD(arg0, u8 *, 0x49) = 2U;
                if (M2C_FIELD(arg0, u8 *, 0xE8) != 8) {
                    if (M2C_FIELD(arg0, void **, 0xC) != NULL) {
                        M2C_FIELD(arg0, u8 *, 0x38) = 0U;
                        M2C_FIELD(arg0, u8 *, 0x37) = 0U;
                    }
                    M2C_FIELD(arg0, u8 *, 0x46) = 0xFFU;
                    return;
                }
                M2C_FIELD(arg0, u8 *, 0x46) = 0xFEU;
                return;
            }
            temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x4A);
            var_v0 = temp_v1_2 + 1;
            if (temp_v1_2 < 0xBU) {
block_37:
                M2C_FIELD(arg0, u8 *, 0x4A) = var_v0;
                return;
            }
            goto block_38;
        }
block_38:
        if (M2C_FIELD(arg0, u8 *, 0x49) != 0) {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s8 *, 0) = 0xFF;
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s8 *, 1) = 0;
            M2C_FIELD(arg0, u8 *, 0xE8) = 0U;
            M2C_FIELD(arg0, s8 *, 0x35) = 0;
            D_8006CF88(arg0, temp_a1);
        }
        if (temp_s3 != 8) {
            if (M2C_FIELD(arg0, u8 *, 0xE8) == 8) {
                M2C_FIELD(arg0, u8 *, 0xE8) = 0U;
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s8 *, 1) = 0;
            }
        } else if (M2C_FIELD(arg0, void **, 0xC) != NULL) {
            M2C_FIELD(arg0, u8 *, 0xE8) = (u8) temp_s3;
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s8 *, 1) = 0x80;
        }
    }
}
