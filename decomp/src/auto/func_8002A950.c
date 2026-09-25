#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80091448[];
extern u8 D_80091450;
extern u8 D_80091458;
extern s32 D_80091460;
extern s32 D_80091464;
extern u8 D_80091468[];
extern u8 D_80061244[];
extern u8 D_80061250[];
extern u8 D_8006125C[];
extern u8 D_80061268[];
extern u8 D_80061274[];
extern u8 D_80061280[];
extern u8 D_8006128C[];
extern u8 D_80061298[];
extern u8 D_8006129C[];
extern u8 D_800612A8[];
extern u8 D_800612B8[];
extern u8 D_800612C4[];
extern u8 D_800612CC[];
extern u8 D_800612D8[];
extern u8 D_800612E4[];
extern u8 D_800612EC[];
extern u8 D_800612F8[];
extern u8 D_80061304[];
extern u8 D_80061310[];
extern u8 D_8006131C[];
extern u8 D_80061324[];
extern u8 D_80061330[];
extern u8 D_80061338[];
extern u8 D_80061340[];
extern u8 D_8006134C[];
extern u8 D_80061354[];
extern u8 D_80061360[];
extern u8 D_8006136C[];
extern u8 D_80061378[];
extern u8 D_80061380[];
extern u8 D_80061390[];
extern u8 D_80061410[];
extern u8 * D_8006D2B0;
extern u8 D_8006D2C8[];
extern u8 D_8006D321;
extern u8 D_8006D328[];
extern u8 D_8006D3A8[];

static M2C_UNK (*D_8006D304)(u8, u8 *) = NULL;
static M2C_UNK (*D_8006D308)(u8, u8 *) = NULL;
u8 D_8006D328[0x80];                                /* unable to generate initializer: cannot parse D_80061338 as integer */
u8 D_8006D3A8[0x20];                                /* unable to generate initializer: cannot parse D_80061378 as integer */

s32 func_8002A950(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    u8 *var_a0;
    u8 *var_a0_2;
    u8 temp_s1;
    u8 temp_v0_2;
    u8 temp_v0_3;

    D_80091460 = func_8001626C(-1) + 0x3C0;
    D_80091464 = 0;
    *D_80091468 = "CD_ready";
loop_1:
    if ((D_80091460 < func_8001626C(-1)) || (temp_v1 = D_80091464, D_80091464 += 1, ((temp_v1 > 0x3C0000) != 0))) {
        puts((s32) "CD timeout: ");
        printf((s32) "%s:(%s) Sync=%s, Ready=%s\n", *D_80091468, *((D_8006D321 * 4) + D_8006D328), *((M2C_FIELD(D_8006D2C8, u8 *, 0) * 4) + D_8006D3A8), *((M2C_FIELD(D_8006D2C8, u8 *, 1) * 4) + D_8006D3A8));
        func_8002B0AC();
        var_v0_2 = -1;
    } else {
        var_v0_2 = 0;
    }
    var_v0 = -1;
    if (var_v0_2 == 0) {
        if (func_80016A04() != 0) {
            temp_s1 = *D_8006D2B0 & 3;
loop_8:
            temp_v0 = func_8002A09C();
            if (temp_v0 != 0) {
                var_v0_3 = temp_v0 & 2;
                if (temp_v0 & 4) {
                    if (D_8006D308 != NULL) {
                        D_8006D308(M2C_FIELD(D_8006D2C8, u8 *, 1), &D_80091450);
                    }
                    var_v0_3 = temp_v0 & 2;
                }
                if ((var_v0_3 != 0) && (D_8006D304 != NULL)) {
                    D_8006D304(M2C_FIELD(D_8006D2C8, u8 *, 0), D_80091448);
                }
                goto loop_8;
            }
            *D_8006D2B0 = temp_s1;
        }
        var_a2 = M2C_FIELD(D_8006D2C8, u8 *, 2) & 0xFF;
        if (var_a2 != 0) {
            M2C_FIELD(D_8006D2C8, u8 *, 2) = 0U;
            var_a0 = &D_80091458;
            var_a1 = arg1;
            if (arg1 != 0) {
                var_v1 = 7;
                do {
                    temp_v0_2 = *var_a0;
                    var_a0 += 1;
                    var_v1 -= 1;
                    *var_a1 = temp_v0_2;
                    var_a1 += 1;
                } while (var_v1 != -1);
                return var_a2;
            }
            goto block_26;
        }
        var_a2 = M2C_FIELD((D_8006D2C8 + 2), u8 *, -1) & 0xFF;
        if (var_a2 != 0) {
            M2C_FIELD(D_8006D2C8, u8 *, 1) = 0U;
            var_a1_2 = arg1;
            var_a0_2 = &D_80091450;
            var_v1_2 = 7;
            if (var_a1_2 != 0) {
                do {
                    temp_v0_3 = *var_a0_2;
                    var_a0_2 += 1;
                    var_v1_2 -= 1;
                    *var_a1_2 = temp_v0_3;
                    var_a1_2 += 1;
                } while (var_v1_2 != -1);
            }
block_26:
            return var_a2;
        }
        var_v0 = 0;
        if (arg0 != 0) {
            /* Duplicate return node #28. Try simplifying control flow for better match */
            return var_v0;
        }
        goto loop_1;
    }
    return var_v0;
}
