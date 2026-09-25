#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8009147C[];
extern u8 D_8009147D[];
extern u8 D_8009147E[];
extern u8 D_80091480[];
extern u8 D_80091484[];
extern u8 D_80091A58[];
extern u8 D_8009307C[];
extern u8 D_8009387C[];
extern u8 D_80061610[];
extern u8 D_80061630[];
extern u16 D_8006164C;
extern s16 D_80061650;
extern s8 D_80061652;
extern u8 D_80061654[];
extern u8 D_80061670[];
extern s32 D_8006D30C;
extern s32 D_8006D3C8;


s32 func_8002BB78(s32 arg0) {
    M2C_UNK sp1B;
    s32 var_s1;
    s32 var_s2;
    s32 var_v0;
    u8 *temp_v0;
    u8 *var_s0;
    u8 *var_s3;
    u8 *var_s4;
    u8 *var_v0_2;

    if (arg0 != D_8006D3C8) {
        var_s0 = D_8009307C;
        if (func_8002BE14(1, *(D_80091A58 + (arg0 * 0x2C)), (s32) D_8009307C) != 1) {
            var_v0 = -1;
            if (D_8006D30C > 0) {
                printf((s32) "CD_cachefile: dir not found\n");
                return -1;
            }
            /* Duplicate return node #24. Try simplifying control flow for better match */
            return var_v0;
        }
        var_v0_2 = D_8009307C + 0x800;
        if (D_8006D30C >= 2) {
            printf((s32) "CD_cachefile: searching...\n");
            var_v0_2 = D_8009307C + 0x800;
        }
        var_s2 = 0;
        if ((u32) D_8009307C < (u32) var_v0_2) {
            var_s3 = D_8009147C + 8;
            var_s1 = 0;
            var_s4 = D_8009147C;
loop_8:
            if (M2C_FIELD(var_s0, u8 *, 0) != 0) {
                sp1B = M2C_UNALIGNED32(M2C_FIRST3BYTES(M2C_FIELD(var_s0, u8 *, 0)));
                func_80029F18((s32) sp18, (s32) var_s4, /* extra? */ M2C_FIRST3BYTES(M2C_FIELD(var_s0, u8 *, 0)));
                temp_v0 = &(D_8009147C + 4)[var_s1];
                M2C_FIELD(temp_v0, M2C_UNK *, 3) = M2C_UNALIGNED32(M2C_FIRST3BYTES(M2C_FIELD(var_s0, M2C_UNK *, 8)));
                M2C_FIELD(temp_v0, M2C_UNK *, -2) = M2C_FIRST3BYTES(M2C_FIELD(var_s0, M2C_UNK *, 8));
                if (var_s2 != 0) {
                    if (var_s2 != 1) {
                        memcpy((s32) var_s3, (s32) (var_s0 + 0x21), (s32) M2C_FIELD(var_s0, u8 *, 0x20));
                        var_s3[M2C_FIELD(var_s0, u8 *, 0x20)] = 0;
                    } else {
                        M2C_FIELD(D_8009147C, s16 *, 0x20) = (s16) D_80061650;
                        M2C_FIELD(D_8009147C, s8 *, 0x22) = (s8) D_80061652;
                    }
                } else {
                    M2C_FIELD(D_8009147C, u16 *, 8) = (u16) D_8006164C;
                }
                if (D_8006D30C >= 2) {
                    printf((s32) "\t(%02x:%02x:%02x) %8d %s\n", D_8009147C[var_s1], D_8009147D[var_s1], D_8009147E[var_s1], D_80091480[var_s1], var_s3);
                }
                var_s3 += 0x18;
                var_s1 += 0x18;
                var_s2 += 1;
                var_s0 = &var_s0[M2C_FIELD(var_s0, u8 *, 0)];
                var_s4 += 0x18;
                if ((var_s2 < 0x40) && ((u32) var_s0 < (u32) D_8009387C)) {
                    goto loop_8;
                }
            }
        }
        D_8006D3C8 = arg0;
        if (var_s2 < 0x40) {
            *(D_80091484 + (var_s2 * 0x18)) = 0;
        }
        var_v0 = 1;
        if (D_8006D30C >= 2) {
            printf((s32) "CD_cachefile: %d files found\n", var_s2);
            goto block_23;
        }
        /* Duplicate return node #24. Try simplifying control flow for better match */
        return var_v0;
    }
block_23:
    var_v0 = 1;
    return var_v0;
}
