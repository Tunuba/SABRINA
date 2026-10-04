#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800654C4[];


void func_8001951C(s32 arg0, s32 arg1) {
    s32 temp_a1_11;
    s32 temp_a1_12;
    s32 temp_a1_13;
    s32 temp_a1_14;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_5;
    s32 temp_a1_7;
    s32 temp_a1_9;
    s32 var_a0;
    s32 var_v0;
    u8 temp_a1;
    u8 temp_a1_10;
    u8 temp_a1_4;
    u8 temp_a1_6;
    u8 temp_a1_8;
    u8 temp_a2;

    var_a0 = arg0;
    var_v0 = arg1;
loop_30:
    temp_a1 = M2C_FIELD(var_v0, u8 *, 0);
    if ((temp_a1 != 0) && ((u32) var_v0 < (u32) (arg1 + 0x40))) {
        if (temp_a1 < 0x80U) {
            temp_a2 = M2C_FIELD(var_v0, u8 *, 0);
            var_v0 += 1;
            temp_a1_2 = var_a0;
            var_a0 = temp_a1_2 + 1;
            *temp_a1_2 = temp_a2;
        } else {
            if ((temp_a1 == 0x80) || (temp_a1 == 0xA0)) {
                temp_a1_3 = var_a0;
                var_a0 = temp_a1_3 + 1;
                *temp_a1_3 = 0x23;
                goto block_29;
            }
            if ((temp_a1 >= 0x81U) && (temp_a1 < 0xFDU)) {
                if ((temp_a1 == 0x81) && (temp_a1_4 = M2C_FIELD(var_v0, u8 *, 1), ((temp_a1_4 < 0x40U) == 0)) && (temp_a1_4 < 0x98U)) {
                    var_v0 += 2;
                    temp_a1_5 = var_a0;
                    var_a0 = temp_a1_5 + 1;
                    *temp_a1_5 = (u8) M2C_FIELD(&D_800654C4[temp_a1_4], u8 *, -0x40);
                } else if ((temp_a1 == 0x82) && (temp_a1_6 = M2C_FIELD(var_v0, u8 *, 1), ((temp_a1_6 < 0x4FU) == 0)) && (temp_a1_6 < 0x59U)) {
                    temp_a1_7 = var_a0;
                    var_a0 = temp_a1_7 + 1;
                    *temp_a1_7 = (s8) (temp_a1_6 - 0x1F);
                    var_v0 += 2;
                } else if ((temp_a1 == 0x82) && (temp_a1_8 = M2C_FIELD(var_v0, u8 *, 1), ((temp_a1_8 < 0x60U) == 0)) && (temp_a1_8 < 0x7BU)) {
                    temp_a1_9 = var_a0;
                    var_a0 = temp_a1_9 + 1;
                    *temp_a1_9 = (s8) (temp_a1_8 - 0x1F);
                    var_v0 += 2;
                } else if ((temp_a1 == 0x82) && (temp_a1_10 = M2C_FIELD(var_v0, u8 *, 1), ((temp_a1_10 < 0x81U) == 0)) && (temp_a1_10 < 0x9CU)) {
                    temp_a1_11 = var_a0;
                    var_a0 = temp_a1_11 + 1;
                    *temp_a1_11 = (s8) (temp_a1_10 - 0x20);
                    var_v0 += 2;
                } else {
                    if ((temp_a1 >= 0xA1U) && (temp_a1 < 0xE0U)) {
                        temp_a1_12 = var_a0;
                        var_a0 = temp_a1_12 + 1;
                        *temp_a1_12 = 0x2A;
                        goto block_29;
                    }
                    temp_a1_13 = var_a0;
                    var_a0 = temp_a1_13 + 1;
                    *temp_a1_13 = 0x2A;
                    var_v0 += 2;
                }
            } else {
                temp_a1_14 = var_a0;
                var_a0 = temp_a1_14 + 1;
                *temp_a1_14 = 0x23;
block_29:
                var_v0 += 1;
            }
        }
        goto loop_30;
    }
    *var_a0 = 0;
}
