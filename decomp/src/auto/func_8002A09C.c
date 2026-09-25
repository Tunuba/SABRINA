#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80091448;
extern u8 D_80091450;
extern u8 D_80091458;
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
extern u8 D_800613AC[];
extern u8 D_800613B8[];
extern u8 D_800613D4[];
extern u8 D_800613E8[];
extern s32 D_8006D0B0[];
extern s32 D_8006D1B0[];
extern u8 * D_8006D2B0;
extern u8 * D_8006D2B4;
extern s8 * D_8006D2B8;
extern u8 * D_8006D2BC;
extern u8 D_8006D2C8[];
extern s32 D_8006D30C;
extern s32 D_8006D310;
extern s32 D_8006D314;
extern s32 D_8006D318;
extern u8 D_8006D321;
extern u8 D_8006D328[];

u8 D_8006D328[0x80];                                /* unable to generate initializer: cannot parse D_80061338 as integer */

s32 func_8002A09C(void) {
    u8 sp10;
    u8 sp18;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_7;
    s32 var_a0_9;
    s32 var_s0;
    s32 var_s1;
    s32 var_v1;
    s32 var_v1_10;
    s32 var_v1_8;
    u8 *temp_v1;
    u8 *var_a0_6;
    u8 *var_a0_8;
    u8 *var_a1;
    u8 *var_a1_2;
    u8 *var_a1_3;
    u8 *var_a1_4;
    u8 *var_a1_5;
    u8 *var_a1_6;
    u8 *var_a1_7;
    u8 *var_a1_8;
    u8 *var_a1_9;
    u8 *var_v0;
    u8 *var_v1_11;
    u8 *var_v1_2;
    u8 *var_v1_3;
    u8 *var_v1_4;
    u8 *var_v1_5;
    u8 *var_v1_7;
    u8 *var_v1_9;
    u8 temp_v0;
    u8 temp_v0_10;
    u8 temp_v0_11;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 temp_v0_5;
    u8 temp_v0_6;
    u8 temp_v0_7;
    u8 temp_v0_8;
    u8 temp_v0_9;
    u8 var_v0_2;
    u8 var_v1_6;

    *D_8006D2B0 = 1;
    temp_v0 = *D_8006D2BC & 7;
    sp10 = temp_v0;
    var_s1 = 0;
    if (temp_v0 != 0) {
loop_3:
        var_s0 = 0;
        if (sp10 != (*D_8006D2BC & 7)) {
            sp10 = *D_8006D2BC & 7;
            goto loop_3;
        }
loop_5:
        temp_v1 = &(&sp18)[var_s0];
        if (*D_8006D2B0 & 0x20) {
            var_s0 += 1;
            *temp_v1 = *D_8006D2B4;
            if (var_s0 < 8) {
                goto loop_5;
            }
        }
        var_v1 = var_s0;
        if (var_s0 < 8) {
            var_v0 = &(&sp18)[var_v1];
            do {
                *var_v0 = 0;
                var_v1 += 1;
                var_v0 = &(&sp18)[var_v1];
            } while (var_v1 < 8);
        }
        *D_8006D2B0 = 1;
        *D_8006D2BC = 7;
        *D_8006D2B8 = 7;
        if ((sp10 != 3) || (D_8006D1B0[D_8006D321] != 0)) {
            if (!(D_8006D310 & 0x10) && (sp18 & 0x10)) {
                D_8006D318 += 1;
            }
            temp_v0_2 = sp18 & 0xFF;
            var_s1 = temp_v0_2 & 0x1D;
            D_8006D310 = temp_v0_2;
            D_8006D314 = (s32) sp19;
        }
        if ((sp10 == 5) && (D_8006D30C > 0)) {
            printf((s32) "DiskError: ");
            if (D_8006D30C > 0) {
                printf((s32) "com=%s,code=(%02x:%02x)\n", *(D_8006D328 + (D_8006D321 * 4)), D_8006D310, D_8006D314);
            }
        }
        switch (sp10) {
        case 3:
            if (var_s1 != 0) {
                M2C_FIELD(D_8006D2C8, u8 *, 0) = 5;
                var_v1_2 = &D_80091448;
                var_a1 = &sp18;
                if (&D_80091448 != NULL) {
                    var_a0 = 7;
                    do {
                        temp_v0_3 = *var_a1;
                        var_a1 += 1;
                        var_a0 -= 1;
                        *var_v1_2 = temp_v0_3;
                        var_v1_2 += 1;
                    } while (var_a0 != -1);
                    return 2;
                }
                goto block_41;
            }
            if (D_8006D0B0[D_8006D321] != 0) {
                M2C_FIELD(D_8006D2C8, u8 *, 0) = 3;
                var_v1_3 = &D_80091448;
                var_a1_2 = &sp18;
                if (&D_80091448 != NULL) {
                    var_a0_2 = 7;
                    do {
                        temp_v0_4 = *var_a1_2;
                        var_a1_2 += 1;
                        var_a0_2 -= 1;
                        *var_v1_3 = temp_v0_4;
                        var_v1_3 += 1;
                    } while (var_a0_2 != -1);
                }
                return 1;
            }
            M2C_FIELD(D_8006D2C8, u8 *, 0) = 2;
            var_v1_4 = &D_80091448;
            var_a1_3 = &sp18;
            if (&D_80091448 != NULL) {
                var_a0_3 = 7;
                do {
                    temp_v0_5 = *var_a1_3;
                    var_a1_3 += 1;
                    var_a0_3 -= 1;
                    *var_v1_4 = temp_v0_5;
                    var_v1_4 += 1;
                } while (var_a0_3 != -1);
                return 2;
            }
block_41:
            return 2;
        case 2:
            var_v0_2 = 2;
            if (var_s1 != 0) {
                var_v0_2 = 5;
            }
            M2C_FIELD(D_8006D2C8, u8 *, 0) = var_v0_2;
            var_v1_5 = &D_80091448;
            var_a1_4 = &sp18;
            if (&D_80091448 != NULL) {
                var_a0_4 = 7;
                do {
                    temp_v0_6 = *var_a1_4;
                    var_a1_4 += 1;
                    var_a0_4 -= 1;
                    *var_v1_5 = temp_v0_6;
                    var_v1_5 += 1;
                } while (var_a0_4 != -1);
            }
            goto block_41;
        case 1:
            if ((var_s1 != 0) && (var_s0 == 1)) {
                var_s1 = 0;
            }
            var_v1_6 = 1;
            if (var_s1 != 0) {
                var_v1_6 = 5;
            }
            M2C_FIELD(D_8006D2C8, u8 *, 1) = var_v1_6;
            var_v1_7 = &D_80091450;
            var_a1_5 = &sp18;
            if (&D_80091450 != NULL) {
                var_a0_5 = 7;
                do {
                    temp_v0_7 = *var_a1_5;
                    var_a1_5 += 1;
                    var_a0_5 -= 1;
                    *var_v1_7 = temp_v0_7;
                    var_v1_7 += 1;
                } while (var_a0_5 != -1);
            }
            *D_8006D2B0 = 0;
            *D_8006D2BC = 0;
            return 4;
        case 4:
            var_a0_6 = &D_80091458;
            M2C_FIELD(D_8006D2C8, u8 *, 2) = 4U;
            var_a1_6 = &sp18;
            M2C_FIELD(D_8006D2C8, u8 *, 1) = (u8) M2C_FIELD(D_8006D2C8, u8 *, 2);
            var_v1_8 = 7;
            if (&D_80091458 != NULL) {
                do {
                    temp_v0_8 = *var_a1_6;
                    var_a1_6 += 1;
                    var_v1_8 -= 1;
                    *var_a0_6 = temp_v0_8;
                    var_a0_6 += 1;
                } while (var_v1_8 != -1);
            }
            var_v1_9 = &D_80091450;
            var_a1_7 = &sp18;
            if (&D_80091450 != NULL) {
                var_a0_7 = 7;
                do {
                    temp_v0_9 = *var_a1_7;
                    var_a1_7 += 1;
                    var_a0_7 -= 1;
                    *var_v1_9 = temp_v0_9;
                    var_v1_9 += 1;
                } while (var_a0_7 != -1);
            }
            return 4;
        case 5:
            var_a0_8 = &D_80091448;
            M2C_FIELD(D_8006D2C8, u8 *, 1) = 5U;
            var_a1_8 = &sp18;
            M2C_FIELD(D_8006D2C8, u8 *, 0) = M2C_FIELD(D_8006D2C8, u8 *, 1);
            var_v1_10 = 7;
            if (&D_80091448 != NULL) {
                do {
                    temp_v0_10 = *var_a1_8;
                    var_a1_8 += 1;
                    var_v1_10 -= 1;
                    *var_a0_8 = temp_v0_10;
                    var_a0_8 += 1;
                } while (var_v1_10 != -1);
            }
            var_v1_11 = &D_80091450;
            var_a1_9 = &sp18;
            if (&D_80091450 != NULL) {
                var_a0_9 = 7;
                do {
                    temp_v0_11 = *var_a1_9;
                    var_a1_9 += 1;
                    var_a0_9 -= 1;
                    *var_v1_11 = temp_v0_11;
                    var_v1_11 += 1;
                } while (var_a0_9 != -1);
            }
            return 6;
        default:
            puts((s32) "CDROM: unknown intr");
            printf((s32) "(%d)\n", sp10);
            goto block_66;
        }
    } else {
block_66:
        return 0;
    }
}
