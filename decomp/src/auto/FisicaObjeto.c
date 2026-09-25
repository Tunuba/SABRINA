#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6594;
extern s32 D_800C65D4;
extern u8 D_800C98C4[];
extern s8 nivel_actual;
extern void * D_8007CB8C;
extern s32 D_8007CC1C;


void FisicaObjeto(s32 arg0, s32 arg1) {
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp7C;
    s32 sp80;
    s32 sp84;
    s32 sp8C;
    s32 sp90;
    s32 sp94;
    s32 sp98;
    s32 sp9C;
    s32 spA0;
    s32 spA4;
    s32 spAC;
    s32 spB0;
    s32 spBC;
    s16 temp_v0_6;
    s32 *var_t7;
    s32 *var_t7_2;
    s32 *var_t7_3;
    s32 *var_t7_4;
    s32 *var_t7_5;
    s32 *var_t7_6;
    s32 *var_t7_7;
    s32 *var_t7_8;
    s32 *var_t7_9;
    s32 *var_t8;
    s32 *var_t8_2;
    s32 *var_t8_3;
    s32 *var_t8_4;
    s32 *var_t8_5;
    s32 *var_t8_6;
    s32 *var_t8_7;
    s32 *var_t8_8;
    s32 *var_t8_9;
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s5;
    s32 var_t9;
    s32 var_t9_2;
    s32 var_t9_3;
    s32 var_t9_4;
    s32 var_t9_5;
    s32 var_t9_6;
    s32 var_t9_7;
    s32 var_t9_8;
    s32 var_t9_9;
    s32 var_v0;
    s8 temp_v0;
    u16 *temp_s6;
    u16 *temp_s7;
    void *temp_s1_2;
    void *temp_s2_2;
    void *temp_s4;

    temp_s4 = arg0 + 0x74;
    temp_v0 = M2C_FIELD(temp_s4, s8 *, 0x26);
    if (temp_v0 > 0) {
        M2C_FIELD(temp_s4, s8 *, 0x26) = (s8) (temp_v0 - 1);
    }
    sp98 = 0;
    sp9C = -0x100;
    spA0 = 0;
    sp8C = M2C_FIELD(arg0, s32 *, 0x24);
    sp90 = 0;
    sp94 = M2C_FIELD(arg0, s32 *, 0x2C);
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x24);
    temp_s2 = M2C_FIELD(arg0, s32 *, 0x28);
    temp_s3 = M2C_FIELD(arg0, s32 *, 0x2C);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (temp_v1 + M2C_FIELD(arg0, s32 *, 0x38));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
    sp8C = M2C_FIELD(arg0, s32 *, 0x38);
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x40);
    sp94 = temp_v0_2;
    temp_v0_3 = ((s32) (sp8C * sp8C) >> 0x10) + ((s32) (temp_v0_2 * temp_v0_2) >> 0x10);
    if ((arg1 == 1) && (temp_v0_3 != 0)) {
        if (temp_v0_3 < 0x1000) {
            func_8001C45C((s32) &sp8C);
        }
        sp8C *= 4;
        sp94 *= 4;
        func_8001C404((s32) &spA4, (s32) &sp98, (s32) &sp8C);
        temp_v0_4 = spA4 * 4;
        spA4 = temp_v0_4;
        temp_v0_5 = spAC * 4;
        spAC = temp_v0_5;
        sp40 = temp_v1 - sp8C;
        sp48 = temp_s3 - sp94;
        sp44 = temp_s2 + 0xFFFE999A;
        sp50 = temp_s2;
        sp4C = temp_v0_4 + (M2C_FIELD(arg0, s32 *, 0x24) + (sp8C * 2));
        sp54 = temp_v0_5 + (M2C_FIELD(arg0, s32 *, 0x2C) + (sp94 * 2));
        var_s1 = 0;
        func_8003B38C((s32) &sp40, (s32) &sp40, (s32) &sp4C);
        var_t8 = &sp40;
        var_t7 = &D_800C6594;
        var_t9 = 0x13;
        do {
            var_t9 -= 1;
            *var_t7 = *var_t8;
            var_t8 += 4;
            var_t7 += 4;
        } while (var_t9 > 0);
        if (func_8003AE84() != 0) {
            var_t8_2 = &D_800C6594;
            var_t7_2 = &sp40;
            var_t9_2 = 0x13;
            do {
                var_t9_2 -= 1;
                *var_t7_2 = *var_t8_2;
                var_t8_2 += 4;
                var_t7_2 += 4;
            } while (var_t9_2 > 0);
            if (sp80 >= 0xFFFF3801) {
                var_s1 = 1;
            }
        } else {
            var_t8_3 = &D_800C6594;
            var_t7_3 = &sp40;
            var_t9_3 = 0x13;
            do {
                var_t9_3 -= 1;
                *var_t7_3 = *var_t8_3;
                var_t8_3 += 4;
                var_t7_3 += 4;
            } while (var_t9_3 > 0);
        }
        if (var_s1 == 0) {
            sp4C = (M2C_FIELD(arg0, s32 *, 0x24) + (sp8C * 2)) - spA4;
            sp54 = (M2C_FIELD(arg0, s32 *, 0x2C) + (sp94 * 2)) - spAC;
            func_8003B38C((s32) &sp40, (s32) &sp40, (s32) &sp4C);
            var_t8_4 = &sp40;
            var_t7_4 = &D_800C6594;
            var_t9_4 = 0x13;
            do {
                var_t9_4 -= 1;
                *var_t7_4 = *var_t8_4;
                var_t8_4 += 4;
                var_t7_4 += 4;
            } while (var_t9_4 > 0);
            if (func_8003AE84() != 0) {
                var_t8_5 = &D_800C6594;
                var_t7_5 = &sp40;
                var_t9_5 = 0x13;
                do {
                    var_t9_5 -= 1;
                    *var_t7_5 = *var_t8_5;
                    var_t8_5 += 4;
                    var_t7_5 += 4;
                } while (var_t9_5 > 0);
                if (D_800C65D4 >= 0xFFFF3801) {
                    var_s1 = 1;
                }
            } else {
                var_t8_6 = &D_800C6594;
                var_t7_6 = &sp40;
                var_t9_6 = 0x13;
                do {
                    var_t9_6 -= 1;
                    *var_t7_6 = *var_t8_6;
                    var_t8_6 += 4;
                    var_t7_6 += 4;
                } while (var_t9_6 > 0);
            }
        }
        if ((var_s1 == 1) && (sp80 >= 0xFFFF3801)) {
            M2C_FIELD(temp_s4, s16 *, 0x18) = (s16) (M2C_FIELD(temp_s4, s16 *, 0x18) | 8);
            M2C_FIELD(temp_s4, s8 *, 0x26) = 5;
            func_8001C45C((s32) &sp7C);
            sp7C = sp7C >> 4;
            sp80 = sp80 >> 4;
            sp84 = sp84 >> 4;
            M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) - M2C_FIELD(arg0, s32 *, 0x38));
            M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) - M2C_FIELD(arg0, s32 *, 0x40));
            sp8C = (s32) M2C_FIELD(arg0, s32 *, 0x38) >> 8;
            sp90 = 0;
            sp94 = (s32) M2C_FIELD(arg0, s32 *, 0x40) >> 8;
            func_80033EC8(sp7C, sp80, sp84, (s32) &sp8C, /* extra? */ &spB0);
            M2C_FIELD(arg0, s32 *, 0x38) = (s32) (spB0 << 8);
            M2C_FIELD(arg0, s32 *, 0x40) = (s32) (spB8 << 8);
            sp40 = M2C_FIELD(arg0, s32 *, 0x24);
            sp44 = sp74;
            sp48 = M2C_FIELD(arg0, s32 *, 0x2C);
            sp4C = sp70 + (spB0 << 0xA);
            sp54 = sp78 + (spB8 << 0xA);
            sp50 = sp74;
            func_8003B38C((s32) &sp40, (s32) &sp40, (s32) &sp4C);
            var_t8_7 = &sp40;
            var_t7_7 = &D_800C6594;
            var_t9_7 = 0x13;
            do {
                var_t9_7 -= 1;
                *var_t7_7 = *var_t8_7;
                var_t8_7 += 4;
                var_t7_7 += 4;
            } while (var_t9_7 > 0);
            if (func_8003AE84() != 0) {
                var_t8_8 = &D_800C6594;
                var_t7_8 = &sp40;
                var_t9_8 = 0x13;
                do {
                    var_t9_8 -= 1;
                    *var_t7_8 = *var_t8_8;
                    var_t8_8 += 4;
                    var_t7_8 += 4;
                } while (var_t9_8 > 0);
                M2C_FIELD(arg0, s32 *, 0x38) = 0;
                M2C_FIELD(arg0, s32 *, 0x40) = 0;
            } else {
                var_t8_9 = &D_800C6594;
                var_t7_9 = &sp40;
                var_t9_9 = 0x13;
                do {
                    var_t9_9 -= 1;
                    *var_t7_9 = *var_t8_9;
                    var_t8_9 += 4;
                    var_t7_9 += 4;
                } while (var_t9_9 > 0);
            }
        }
    }
    if (M2C_FIELD(temp_s4, s32 *, 4) < func_8001C004(0, 0, 0, M2C_FIELD(arg0, s32 *, 0x38), /* extra? */ 0, /* extra? */ M2C_FIELD(arg0, s32 *, 0x40))) {
        temp_s1 = M2C_FIELD(arg0, s32 *, 0x3C);
        func_8001C45C(arg0 + 0x38);
        M2C_FIELD(arg0, s32 *, 0x38) = func_8001C304(M2C_FIELD(arg0, s32 *, 0x38) * 0x10, M2C_FIELD(temp_s4, s32 *, 4));
        M2C_FIELD(arg0, s32 *, 0x40) = func_8001C304(M2C_FIELD(arg0, s32 *, 0x40) * 0x10, M2C_FIELD(temp_s4, s32 *, 4));
        M2C_FIELD(arg0, s32 *, 0x3C) = temp_s1;
    }
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
    sp40 = M2C_FIELD(arg0, s32 *, 0x24);
    sp44 = M2C_FIELD(arg0, s32 *, 0x28) + 0xFFFE999A;
    sp48 = M2C_FIELD(arg0, s32 *, 0x2C);
    if (M2C_FIELD(temp_s4, s16 *, 0x18) & 0x10) {
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x38);
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) (temp_v1_2 - (temp_v1_2 >> 2));
        temp_v1_3 = M2C_FIELD(arg0, s32 *, 0x40);
        var_v0 = temp_v1_3 - (temp_v1_3 >> 2);
    } else {
        temp_v1_4 = M2C_FIELD(arg0, s32 *, 0x38);
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) (temp_v1_4 - (temp_v1_4 >> 3));
        temp_v1_5 = M2C_FIELD(arg0, s32 *, 0x40);
        var_v0 = temp_v1_5 - (temp_v1_5 >> 3);
    }
    M2C_FIELD(arg0, s32 *, 0x40) = var_v0;
    if (func_8003AF48((s32) &sp40) != 0) {
        M2C_FIELD(temp_s4, s32 *, 0x28) = sp7C;
        M2C_FIELD(temp_s4, s32 *, 0x2C) = sp80;
        M2C_FIELD(temp_s4, s32 *, 0x30) = sp84;
        M2C_FIELD(arg0, s32 *, 0x50) = sp74;
        if (sp74 >= (M2C_FIELD(arg0, s32 *, 0x28) - 0x51E)) {
            M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (M2C_FIELD(arg0, s32 *, 0x3C) + 0x51E);
        } else {
            var_a0 = sp80;
            sp7C = sp7C >> 4;
            sp80 = sp80 >> 4;
            sp84 = sp84 >> 4;
            if (var_a0 >= 0xFFFF3801) {
                if (var_a0 >= -0x7FFF) {
                    M2C_FIELD(temp_s4, s16 *, 0x18) = (s16) (M2C_FIELD(temp_s4, s16 *, 0x18) | 8);
                    M2C_FIELD(temp_s4, s8 *, 0x26) = 0x1E;
                }
                if (var_a0 < 0) {
                    var_a0 = -var_a0;
                }
                temp_a0 = var_a0 >> 6;
                M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) + ((s32) ((s32) (sp7C * temp_a0) >> 8) >> 2));
                M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + ((s32) ((s32) (sp84 * temp_a0) >> 8) >> 2));
                M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
                M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
            } else {
                temp_v0_6 = M2C_FIELD(temp_s4, s16 *, 0x18);
                if (temp_v0_6 == 0) {
                    M2C_FIELD(temp_s4, s16 *, 0x18) = (s16) (temp_v0_6 | 0x10);
                    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
                }
            }
            M2C_FIELD(arg0, s32 *, 0x50) = sp74;
            M2C_FIELD(arg0, s32 *, 0x28) = sp74;
            M2C_FIELD(temp_s4, u16 *, 0xC) = sp88;
        }
    } else if (nivel_actual == 0xD) {
        temp_s2_2 = M2C_FIELD(arg0, void **, 0x1C);
        temp_s1_2 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
        temp_s6 = M2C_FIELD(D_8007CB8C, u16 **, 0x64);
        temp_s7 = M2C_FIELD(arg0, u16 **, 0x64);
        var_s3 = 0;
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (M2C_FIELD(arg0, s32 *, 0x3C) + 0x51E);
        var_s5 = 0;
loop_59:
        if (var_s3 < D_8007CC1C) {
            if (func_8004DB6C((s32) &spBC, M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0x28), M2C_FIELD(arg0, s32 *, 0x2C), /* extra? */ D_800C98C4[var_s5]) == 1) {
                temp_v0_7 = M2C_FIELD(arg0, s32 *, 0x28);
                if ((temp_v0_7 >= spBC) && ((temp_v0_7 - spBC) < 0x8000)) {
                    M2C_FIELD(arg0, s32 *, 0x50) = spBC;
                    M2C_FIELD(arg0, s32 *, 0x28) = spBC;
                    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
                    M2C_FIELD(temp_s4, s16 *, 0x18) = (s16) (M2C_FIELD(temp_s4, s16 *, 0x18) | 0x10);
                }
            }
            var_s3 += 1;
            var_s5 += 4;
            goto loop_59;
        }
        if (M2C_FIELD(arg0, s32 *, 0x28) >= 0xA0001) {
            M2C_FIELD(temp_s2_2, s8 *, 0x51) = (s8) *temp_s7;
            M2C_FIELD(temp_s2_2, s8 *, 0x50) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 0x4E) = 0x800;
            M2C_FIELD(temp_s1_2, s8 *, 0x51) = (s8) *temp_s6;
            M2C_FIELD(temp_s1_2, s8 *, 0x50) = 0;
            M2C_FIELD(temp_s1_2, s16 *, 0x4E) = 0x800;
            M2C_FIELD(temp_s4, s8 *, 0x1A) = -1;
            M2C_FIELD(temp_s4, s8 *, 0x1B) = -1;
            M2C_FIELD(arg0, s16 *, 0x70) = 2;
        }
    }
    DanoPorSuelo(arg0, M2C_ERROR(/* Read from unset register $a1 */), M2C_ERROR(/* Read from unset register $a2 */), M2C_ERROR(/* Read from unset register $a3 */));
}
