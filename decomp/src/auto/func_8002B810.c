#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80091A7C[];
extern u8 D_80091A80[];
extern u8 D_80091A84[];
extern u8 D_8009307C[];
extern u8 D_80061530[];
extern u8 D_8006155C[];
extern u8 D_80061564[];
extern u8 D_80061594[];
extern u8 D_800615B8[];
extern u8 D_800615D8[];
extern u8 D_800615EC[];
extern s32 D_8006D30C;
extern s32 D_8006D3C8;


s32 func_8002B810(void) {
    M2C_UNK sp1B;
    s32 temp_s0;
    s32 temp_s3;
    s32 temp_v0;
    s32 var_a3;
    s32 var_v0;
    u8 *temp_v1;
    u8 *var_s1;
    u8 temp_v1_2;
    void *temp_s2;
    void *temp_v0_2;

    temp_v0 = func_8002BE14(1, 0x10, (s32) D_8009307C);
    if (temp_v0 != 1) {
        var_v0 = 0;
        if (D_8006D30C > 0) {
            printf((s32) D_80061530);
            return 0;
        }
        /* Duplicate return node #22. Try simplifying control flow for better match */
        return var_v0;
    }
    if (strncmp((s32) (D_8009307C + 1), (s32) D_8006155C, 5) != 0) {
        var_v0 = 0;
        if (D_8006D30C > 0) {
            printf((s32) D_80061564);
            return 0;
        }
        /* Duplicate return node #22. Try simplifying control flow for better match */
        return var_v0;
    }
    sp1B = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    if (func_8002BE14(1, (s32) sp18, (s32) D_8009307C) != temp_v0) {
        var_v0 = 0;
        if (D_8006D30C > 0) {
            printf((s32) D_80061594, (s32) sp18);
            return 0;
        }
        /* Duplicate return node #22. Try simplifying control flow for better match */
        return var_v0;
    }
    var_s1 = D_8009307C;
    if (D_8006D30C >= 2) {
        printf((s32) D_800615B8);
    }
    temp_v1 = D_8009307C + 0x800;
    var_a3 = 0;
    if ((u32) D_8009307C < (u32) temp_v1) {
loop_13:
        if (M2C_FIELD(var_s1, u8 *, 0) != 0) {
            temp_s0 = var_a3 * 0x2C;
            temp_v0_2 = temp_s0 + D_80091A84;
            M2C_FIELD(temp_v0_2, M2C_UNK *, 3) = M2C_UNALIGNED32(M2C_FIRST3BYTES(M2C_FIELD(var_s1, u8 *, 0)));
            M2C_FIELD(temp_v0_2, M2C_UNK *, -2) = M2C_FIRST3BYTES(M2C_FIELD(var_s1, u8 *, 0));
            temp_s2 = temp_s0 + (D_80091A84 + 4);
            temp_s3 = var_a3 + 1;
            *(D_80091A7C + temp_s0) = temp_s3;
            *(D_80091A80 + temp_s0) = (s32) M2C_FIELD(var_s1, u8 *, 6);
            memcpy((s32) temp_s2, (s32) (var_s1 + 8), (s32) M2C_FIELD(var_s1, u8 *, 0));
            *(temp_s2 + M2C_FIELD(var_s1, u8 *, 0)) = 0;
            temp_v1_2 = M2C_FIELD(var_s1, u8 *, 0);
            var_s1 = &var_s1[temp_v1_2 + ((temp_v1_2 & 1) + 8)];
            if (D_8006D30C >= 2) {
                printf((s32) D_800615D8, *(D_80091A84 + temp_s0), *(D_80091A7C + temp_s0), *(D_80091A80 + temp_s0), temp_s2);
            }
            var_a3 = temp_s3;
            if (var_a3 < 0x80) {
                if ((u32) var_s1 >= (u32) temp_v1) {
                    goto block_18;
                }
                goto loop_13;
            }
        } else {
            goto block_18;
        }
    } else {
block_18:
        if (var_a3 < 0x80) {
            *(D_80091A80 + (var_a3 * 0x2C)) = 0;
        }
    }
    D_8006D3C8 = 0;
    var_v0 = 1;
    if (D_8006D30C >= 2) {
        printf((s32) D_800615EC, var_a3);
        var_v0 = 1;
    }
    return var_v0;
}
