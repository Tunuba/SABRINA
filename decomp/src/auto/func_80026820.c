#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u32 D_800909F8;

s32 func_80026820(void *arg0) {
    s32 var_a3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u16 temp_v1_3;
    u32 temp_v1_4;
    u8 *var_a0;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 temp_v1;
    u8 temp_v1_5;
    void *temp_a0;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_t0;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x46);
    if (temp_v1 != 3) {
        if ((s32) temp_v1 < 4) {
            if (temp_v1 != 2) {
                return 1;
            }
            temp_v1_2 = M2C_FIELD(arg0, void **, 0x3C);
            var_v0 = 0;
            if (M2C_FIELD(temp_v1_2, u8 *, 2) == 0) {
                var_v0 = 0;
                if (M2C_FIELD(temp_v1_2, u8 *, 3) == 0) {
                    *((M2C_FIELD(arg0, u8 *, 0x47) * 2) + M2C_FIELD(arg0, s32 *, 0)) = M2C_FIELD(temp_v1_2, u8 *, 5) + (M2C_FIELD(temp_v1_2, u8 *, 4) << 8);
                    temp_v1_3 = *((M2C_FIELD(arg0, u8 *, 0x47) * 2) + M2C_FIELD(arg0, s32 *, 0));
                    if (M2C_FIELD(arg0, u16 *, 0xEE) != temp_v1_3) {
                        M2C_FIELD(arg0, u16 *, 0xEE) = temp_v1_3;
                        goto block_10;
                    }
                    M2C_FIELD(arg0, u16 *, 0xEE) = 0U;
                    M2C_FIELD(arg0, s8 *, 0xEB) = 0;
                    temp_v0 = M2C_FIELD(arg0, u8 *, 0x47) + 1;
                    M2C_FIELD(arg0, u8 *, 0x47) = temp_v0;
                    var_v0 = 0;
                    if ((u32) (temp_v0 & 0xFF) >= (u8) M2C_FIELD(arg0, u8 *, 0xE3)) {
                        M2C_FIELD(arg0, u8 *, 0x47) = 0U;
                        goto block_47;
                    }
                    /* Duplicate return node #48. Try simplifying control flow for better match */
                    return var_v0;
                }
            }
            /* Duplicate return node #48. Try simplifying control flow for better match */
            return var_v0;
        }
        if (temp_v1 != 4) {
            return 1;
        }
        temp_a2 = M2C_FIELD(arg0, void **, 0x3C);
        if (M2C_FIELD(temp_a2, u8 *, 2) != 0) {
            M2C_FIELD(arg0, u8 *, 0x48) = 0U;
block_10:
            return 0;
        }
        temp_t0 = M2C_FIELD(arg0, s32 *, 8) + (M2C_FIELD(arg0, u8 *, 0x47) * 8);
        if (M2C_FIELD(arg0, u8 *, 0x48) == 0) {
            temp_v0_2 = M2C_FIELD(temp_a2, u8 *, 4);
            M2C_FIELD(arg0, u8 *, 0x48) = temp_v0_2;
            M2C_FIELD(temp_t0, u8 *, 0) = temp_v0_2;
            var_a0 = M2C_FIELD(arg0, void **, 0x3C) + 5;
            if (M2C_FIELD(arg0, u8 *, 0x47) == 0) {
                var_v1 = M2C_FIELD(arg0, s32 *, 8);
                var_v0_2 = M2C_FIELD(arg0, u8 *, 0xEA) * 8;
            } else {
                var_v1 = M2C_FIELD(temp_t0, s32 *, -4);
                var_v0_2 = (M2C_FIELD(temp_t0, u8 *, -8) + 3) & 0x1FC;
            }
            temp_v1_4 = var_v1 + var_v0_2;
            M2C_FIELD(temp_t0, u32 *, 4) = temp_v1_4;
            D_800909F8 = temp_v1_4;
            var_a3 = 2;
        } else {
            var_a0 = temp_a2 + 3;
            var_a3 = 4;
        }
        if (var_a3 != -1) {
loop_35:
            if (M2C_FIELD(arg0, u8 *, 0x48) != 0) {
                if ((u32) D_800909F8 < (u32) (arg0 + 0xE3)) {
                    if (*D_800909F8 != *var_a0) {
                        M2C_FIELD(arg0, u16 *, 0xEE) = 0xFFFFU;
                    }
                    temp_v1_5 = *var_a0;
                    var_a0 += 1;
                    *D_800909F8 = temp_v1_5;
                    D_800909F8 += 1;
                    var_a3 -= 1;
                    M2C_FIELD(arg0, u8 *, 0x48) = (u8) (M2C_FIELD(arg0, u8 *, 0x48) - 1);
                    if (var_a3 == -1) {
                        goto block_40;
                    }
                    goto loop_35;
                }
                M2C_FIELD(arg0, u8 *, 0x47) = 0U;
                M2C_FIELD(arg0, u8 *, 0x48) = 0U;
                return 0;
            }
            goto block_41;
        }
block_40:
        var_v0 = 0;
        if (M2C_FIELD(arg0, u8 *, 0x48) == 0) {
block_41:
            if (M2C_FIELD(arg0, u16 *, 0xEE) != 0) {
                M2C_FIELD(arg0, u16 *, 0xEE) = 0U;
                M2C_FIELD(arg0, u8 *, 0x48) = 0U;
                return 0;
            }
            temp_v0_3 = M2C_FIELD(arg0, u8 *, 0x47) + 1;
            M2C_FIELD(arg0, u8 *, 0x47) = temp_v0_3;
            if ((u32) (temp_v0_3 & 0xFF) >= (u8) M2C_FIELD(arg0, u8 *, 0xEA)) {
                M2C_FIELD(arg0, s8 *, 0x49) = 6;
                M2C_FIELD(arg0, u8 *, 0x46) = 0xFEU;
                M2C_FIELD(arg0, s8 *, 0xEB) = 0;
                return 0;
            }
            M2C_FIELD(arg0, u8 *, 0x48) = 0U;
            M2C_FIELD(arg0, s8 *, 0xEB) = 0;
            return 0;
        }
        /* Duplicate return node #48. Try simplifying control flow for better match */
        return var_v0;
    }
    temp_a2_2 = M2C_FIELD(arg0, void **, 0x3C);
    var_v0 = 0;
    if (M2C_FIELD(temp_a2_2, u8 *, 2) == 0) {
        var_v0 = 0;
        if (M2C_FIELD(temp_a2_2, u8 *, 3) == 0) {
            temp_a0 = M2C_FIELD(arg0, s32 *, 4) + (M2C_FIELD(arg0, u8 *, 0x47) * 5);
            if ((M2C_FIELD(temp_a0, u8 *, 0) == M2C_FIELD(temp_a2_2, u8 *, 4)) && (M2C_FIELD(temp_a0, u8 *, 1) == (M2C_FIELD(temp_a2_2, u8 *, 5) & 0x7F)) && (M2C_FIELD(temp_a0, u8 *, 2) == M2C_FIELD(temp_a2_2, u8 *, 6)) && (M2C_FIELD(temp_a0, u8 *, 3) == M2C_FIELD(temp_a2_2, u8 *, 7)) && (M2C_FIELD(temp_a0, u8 *, 4) == ((s32) M2C_FIELD(temp_a2_2, u8 *, 5) >> 7))) {
                M2C_FIELD(arg0, u16 *, 0xEE) = 0U;
            } else {
                M2C_FIELD(arg0, u16 *, 0xEE) = 0xFFFFU;
            }
            M2C_FIELD(temp_a0, u8 *, 0) = (u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 4);
            M2C_FIELD(temp_a0, u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 5) & 0x7F);
            M2C_FIELD(temp_a0, u8 *, 2) = (u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 6);
            M2C_FIELD(temp_a0, u8 *, 3) = (u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 7);
            M2C_FIELD(temp_a0, u8 *, 4) = (u8) ((s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 5) >> 7);
            var_v0 = 0;
            if (M2C_FIELD(arg0, u16 *, 0xEE) == 0) {
                M2C_FIELD(arg0, s8 *, 0xEB) = 0;
                temp_v0_4 = M2C_FIELD(arg0, u8 *, 0x47) + 1;
                M2C_FIELD(arg0, u8 *, 0x47) = temp_v0_4;
                var_v0 = 0;
                if ((u32) (temp_v0_4 & 0xFF) >= (u8) M2C_FIELD(arg0, u8 *, 0xE9)) {
                    M2C_FIELD(arg0, u8 *, 0x47) = 0U;
                    M2C_FIELD(arg0, u8 *, 0x48) = 0U;
block_47:
                    var_v0 = 1;
                }
            }
        }
    }
    return var_v0;
}
