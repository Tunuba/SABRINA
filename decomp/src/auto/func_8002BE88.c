#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80091484[];
extern u8 D_800614A4[];
extern u8 D_800614C0[];
extern u8 D_800614D8[];
extern u8 D_800614F4[];
extern u8 D_80061514[];
extern u8 D_80061520[];
extern s32 D_8006D30C;
extern s32 D_8006D318;
extern s32 D_8006D3CC;


s32 func_8002BE88(s32 arg0, s32 arg1) {
    s8 sp10;
    s32 var_a0;
    s32 var_a1;
    s32 var_s0_2;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_v0_2;
    s8 *var_s1;
    s8 var_v0;
    u8 *var_a0_2;
    u8 *var_s0;
    u8 *var_s3;
    u8 var_v1;

    if (D_8006D3CC != D_8006D318) {
        if (func_8002B810() != 0) {
            D_8006D3CC = D_8006D318;
            goto block_3;
        }
        /* Duplicate return node #38. Try simplifying control flow for better match */
        return 0;
    }
block_3:
    if (*arg1 != 0x5C) {
        return 0;
    }
    sp10 = 0;
    var_a0 = 1;
    var_s0_2 = arg1;
    var_s2 = 0;
loop_7:
    var_v0 = *var_s0_2;
    var_v1 = (u8) *var_s0_2;
    var_s1 = &sp10;
    if (var_v0 != 0x5C) {
loop_9:
        var_v0_2 = var_s2 < 8;
        if (var_v1 != 0) {
            var_s0_2 += 1;
            *var_s1 = (s8) var_v1;
            var_v1 = (u8) *var_s0_2;
            var_s1 += 1;
            if (*var_s0_2 == 0x5C) {
                var_v0 = *var_s0_2;
                goto block_12;
            }
            goto loop_9;
        }
    } else {
block_12:
        var_v0_2 = var_s2 < 8;
        if (var_v0 != 0) {
            var_s0_2 += 1;
            *var_s1 = 0;
            var_a0 = func_8002BAD4(var_a0, (s32) &sp10);
            if (var_a0 != -1) {
                var_s2 += 1;
                if (var_s2 >= 8) {
                    goto block_15;
                }
                goto loop_7;
            }
            sp10 = 0;
block_15:
            var_v0_2 = var_s2 < 8;
        }
    }
    if (var_v0_2 == 0) {
        if (D_8006D30C > 0) {
            printf((s32) "%s: path level (%d) error\n", arg1, var_s2);
            return 0;
        }
        goto block_37;
    }
    if (sp10 == 0) {
        var_a1 = arg1;
        if (D_8006D30C > 0) {
            var_a0_2 = "%s: dir was not found\n";
            goto block_36;
        }
        goto block_37;
    }
    *var_s1 = 0;
    if (func_8002BB78(var_a0) == 0) {
        if (D_8006D30C > 0) {
            printf((s32) "CdSearchFile: disc error\n");
            return 0;
        }
        /* Duplicate return node #38. Try simplifying control flow for better match */
        return 0;
    }
    var_s2_2 = 0;
    if (D_8006D30C >= 2) {
        printf((s32) "CdSearchFile: searching %s...\n", &sp10);
        var_s2_2 = 0;
    }
    var_s0 = D_80091484 - 8;
    var_s3 = D_80091484;
    var_s1_2 = 0;
loop_28:
    if ((s8) D_80091484[var_s1_2] != 0) {
        if (func_8002B7F0((s32) var_s3, (s32) &sp10) != 0) {
            if (D_8006D30C >= 2) {
                printf((s32) "%s:  found\n", &sp10);
            }
            M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(var_s0, s32 *, 0);
            M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(var_s0, s32 *, 4);
            M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(var_s0, s32 *, 8);
            M2C_FIELD(arg0, s32 *, 0xC) = (s32) M2C_FIELD(var_s0, s32 *, 0xC);
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) M2C_FIELD(var_s0, s32 *, 0x10);
            M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(var_s0, s32 *, 0x14);
            return (s32) var_s0;
        }
        var_s0 += 0x18;
        var_s3 += 0x18;
        var_s2_2 += 1;
        var_s1_2 += 0x18;
        if (var_s2_2 >= 0x40) {
            goto block_34;
        }
        goto loop_28;
    }
block_34:
    var_a1 = (s32) &sp10;
    if (D_8006D30C > 0) {
        var_a0_2 = "%s: not found\n";
block_36:
        printf((s32) var_a0_2, var_a1);
    }
block_37:
    return 0;
}
