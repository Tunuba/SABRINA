#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 (*D_8006CF88)(s32);


s32 func_80026ECC(s32 arg0) {
    s32 var_v0;
    u16 temp_a0_2;
    u16 temp_v1_3;
    u8 temp_v0;
    u8 temp_v1;
    void *temp_a0;
    void *temp_v1_2;
    void *temp_v1_4;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x46);
    if (temp_v1 != 3) {
        if ((s32) temp_v1 < 4) {
            if (temp_v1 != 2) {
                return 1;
            }
            temp_a0 = M2C_FIELD(arg0, void **, 0x3C);
            var_v0 = 0;
            if (M2C_FIELD(temp_a0, u8 *, 7) == 0) {
                if ((M2C_FIELD(arg0, u8 *, 0xE3) == M2C_FIELD(temp_a0, u8 *, 3)) && (M2C_FIELD(arg0, u8 *, 0xE4) == M2C_FIELD(temp_a0, u8 *, 4)) && (M2C_FIELD(arg0, u8 *, 0xE9) == M2C_FIELD(temp_a0, u8 *, 5)) && (M2C_FIELD(arg0, u8 *, 0xEA) == M2C_FIELD(temp_a0, u8 *, 6))) {
                    M2C_FIELD(arg0, u16 *, 0xEE) = 0U;
                } else {
                    M2C_FIELD(arg0, u16 *, 0xEE) = 0xFFFFU;
                }
                M2C_FIELD(arg0, u8 *, 0xE3) = (u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 3);
                M2C_FIELD(arg0, u16 *, 0xE6) = 0U;
                M2C_FIELD(arg0, u8 *, 0xE4) = (u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 4);
                M2C_FIELD(arg0, u8 *, 0xE9) = (u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 5);
                M2C_FIELD(arg0, u16 *, 0xEC) = 0U;
                M2C_FIELD(arg0, u8 *, 0xEA) = (u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 6);
                if (M2C_FIELD(arg0, u16 *, 0xEE) == 0) {
                    M2C_FIELD(arg0, s8 *, 0xEB) = 0;
                    goto block_29;
                }
                goto block_19;
            }
            /* Duplicate return node #30. Try simplifying control flow for better match */
            return var_v0;
        }
        if (temp_v1 != 4) {
            return 1;
        }
        temp_v1_2 = M2C_FIELD(arg0, void **, 0x3C);
        var_v0 = 0;
        if (M2C_FIELD(temp_v1_2, u8 *, 2) == 0) {
            var_v0 = 0;
            if (M2C_FIELD(temp_v1_2, u8 *, 3) == 0) {
                temp_v0 = M2C_FIELD(arg0, u8 *, 0x47) + 1;
                M2C_FIELD(arg0, u8 *, 0x47) = temp_v0;
                M2C_FIELD(arg0, u16 *, 0xEC) = (u16) (M2C_FIELD(arg0, u16 *, 0xEC) + 8 + ((M2C_FIELD(temp_v1_2, u8 *, 4) + 3) & 0x1FC));
                if ((u32) (temp_v0 & 0xFF) >= (u8) M2C_FIELD(arg0, u8 *, 0xEA)) {
                    if (func_8002713C(arg0) >= 0x81) {
                        D_8006CF88(arg0);
                        M2C_FIELD(arg0, u8 *, 0x46) = 0xFEU;
                        M2C_FIELD(arg0, s8 *, 0x49) = 2;
                        goto block_19;
                    }
                    temp_v1_3 = M2C_FIELD(arg0, u16 *, 0xEC);
                    if (M2C_FIELD(arg0, u16 *, 0xEE) != temp_v1_3) {
                        M2C_FIELD(arg0, u16 *, 0xEE) = temp_v1_3;
                        M2C_FIELD(arg0, u8 *, 0x47) = 0U;
                        M2C_FIELD(arg0, u16 *, 0xEC) = 0U;
                        return 0;
                    }
                    M2C_FIELD(arg0, u16 *, 0xEE) = 0U;
                    M2C_FIELD(arg0, s8 *, 0xEB) = 0;
                    M2C_FIELD(arg0, u8 *, 0x46) = 0xFFU;
                    func_80027174(arg0, arg0 + 0x63);
                    M2C_FIELD(arg0, u8 *, 0x46) = 2U;
                    goto block_19;
                }
                goto block_19;
            }
        }
        /* Duplicate return node #30. Try simplifying control flow for better match */
        return var_v0;
    }
    temp_v1_4 = M2C_FIELD(arg0, void **, 0x3C);
    var_v0 = 0;
    if (M2C_FIELD(temp_v1_4, u8 *, 2) == 0) {
        var_v0 = 0;
        if (M2C_FIELD(temp_v1_4, u8 *, 3) == 0) {
            temp_a0_2 = M2C_FIELD(temp_v1_4, u8 *, 5) + (M2C_FIELD(temp_v1_4, u8 *, 4) << 8);
            M2C_FIELD(arg0, u16 *, 0xE6) = temp_a0_2;
            if (M2C_FIELD(arg0, u16 *, 0xEE) != (temp_a0_2 & 0xFFFF)) {
                M2C_FIELD(arg0, u16 *, 0xEE) = temp_a0_2;
block_19:
                return 0;
            }
            M2C_FIELD(arg0, u16 *, 0xEE) = 0xFFFFU;
            M2C_FIELD(arg0, s8 *, 0xEB) = 0;
            M2C_FIELD(arg0, u8 *, 0x47) = 0U;
block_29:
            var_v0 = 1;
            /* Duplicate return node #30. Try simplifying control flow for better match */
            return var_v0;
        }
    }
    return var_v0;
}
