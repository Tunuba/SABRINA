#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8009387C[];
extern s32 D_80093A0C;
extern u8 D_800616E4[];
extern s32 D_8006D30C;
extern s32 D_8006D41C[];
extern s32 D_8006D5AC;
extern s32 D_8006D5B0;
extern s32 D_8006D5B4;
extern s32 D_8006D5B8;


s32 func_8002CF28(s32 arg0, s32 arg1, s32 arg2) {
    s8 sp10;
    u8 sp18;
    s32 *var_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    if (arg0 == 3) {
        var_v0 = -1;
        if (D_8006D5AC != -1) {
            func_80029AB8(1, 0, 0);
            if (func_80029A50(1, (s32) &sp18) != 0) {
                if (!(sp18 & 0xC0)) {
                    D_8006D5B0 = 1;
                }
                if ((D_8006D5B0 == 0) || (sp18 & 0x10)) {
                    func_80029BF4(1, 0);
                } else {
                    goto block_22;
                }
            }
            goto block_23;
        }
        /* Duplicate return node #24. Try simplifying control flow for better match */
        return var_v0;
    }
    if (arg0 == 0) {
        func_8002CEB4();
        goto block_23;
    }
    temp_v0 = CdGetToc((s32) D_8009387C);
    D_80093A0C = temp_v0;
    if (temp_v0 == 0) {
        if (D_8006D30C >= 2) {
            printf((s32) "No TOC found: please use CD-DA disc...\n");
        }
        D_8006D5AC = -1;
        return -1;
    }
    D_8006D5B4 = arg0 != 1;
    var_v1 = 0;
    var_a0 = D_8006D41C;
    var_a1 = arg1;
loop_15:
    temp_v0_2 = *var_a1;
    if (temp_v0_2 != 0) {
        *var_a0 = temp_v0_2;
        var_a0 += 4;
        var_v1 += 1;
        var_a1 += 4;
        if (var_v1 < 0x63) {
            goto loop_15;
        }
    }
    D_8006D41C[var_v1] = 0;
    D_8006D5AC = arg2;
    if (arg2 >= 0) {
        if (var_v1 >= arg2) {
            var_v1 = arg2;
        }
    } else {
        var_v1 = 0;
    }
    D_8006D5AC = var_v1;
    sp10 = 5;
    D_8006D5B8 = D_8006D41C[var_v1];
    func_80029AB8(0xE, (s32) &sp10, 0);
block_22:
    func_8002CD3C();
block_23:
    var_v0 = D_8006D5AC;
    return var_v0;
}
