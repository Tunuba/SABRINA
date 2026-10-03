#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800C8558;
extern s16 D_800C855A;
extern s16 D_800C855C;
extern s8 D_800C855E;
extern s8 D_800C8582;
extern s8 D_800C8583;
extern s8 D_800C8584;
extern s8 D_800C8585;
extern u8 D_800C86B5[];
extern u8 D_800C86C6[];
extern s8 D_800C98C2;
extern s16 gemas;

s32 func_8004AF50(void) {
    s16 temp_v1;
    s16 temp_v1_2;
    s16 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s8 var_v0;
    s8 var_v0_2;
    s8 var_v0_3;

    temp_v1 = (s16) (gemas + D_800C8558) + D_800C855A;
    temp_v1_2 = temp_v1 + D_800C855C;
    var_v0_2 = 0;
    if (temp_v1_2 != 0) {
        var_v0_2 = (s8) (s16) (((temp_v1 + D_800C855C) / 100) + ((u32) temp_v1_2 >> 0x1F));
    }
    var_a0 = 0;
    var_a1 = 0;
    var_a2 = 0;
loop_4:
    if (var_a1 < 0xE) {
        var_a1 += 1;
        var_a0 += (s8) D_800C86B5[var_a2];
        var_a2 += 0x141;
        goto loop_4;
    }
    var_v0_3 = var_v0_2 + (s8) var_a0;
    if (D_800C8582 == 2) {
        var_v0_3 += 4;
    }
    if (D_800C8583 == 2) {
        var_v0_3 += 4;
    }
    if (D_800C8584 == 2) {
        var_v0_3 += 4;
    }
    if (D_800C8585 == 2) {
        var_v0_3 += 4;
    }
    var_a1_2 = 0;
    var_a0_2 = 0;
loop_19:
    if (var_a1_2 < 0xF) {
        if ((var_a1_2 != 0xD) && (var_a1_2 != 0) && ((s8) D_800C86C6[var_a0_2] != 0)) {
            var_v0_3 += 1;
        }
        var_a1_2 += 1;
        var_a0_2 += 0x141;
        goto loop_19;
    }
    var_v0 = var_v0_3 + (s8) (D_800C855E * 2);
    if (D_800C98C2 != 0) {
        var_v0 += 4;
    }
    return (s32) var_v0;
}
