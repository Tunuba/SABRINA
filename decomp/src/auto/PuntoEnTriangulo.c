#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 PuntoEnTriangulo(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp4;
    s32 sp8;
    s32 spC;
    s16 temp_a3_2;
    s16 temp_t2;
    s16 temp_t2_3;
    s16 temp_t2_5;
    s16 temp_t4;
    s16 temp_t6;
    s16 temp_t6_2;
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t2_2;
    s32 temp_t2_4;
    s32 temp_t2_6;
    s32 temp_t3;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_v1_2;
    s32 var_v0;
    s8 temp_v1;

    temp_v1 = M2C_FIELD(arg2, s8 *, 0x1B);
    temp_a3 = temp_v1 & 3;
    temp_t1 = (temp_v1 >> 2) & 3;
    temp_t0 = *(arg1 + (temp_a3 * 4));
    temp_v1_2 = *(arg1 + (temp_t1 * 4));
    temp_t1_2 = temp_t1 * 2;
    sp4 = M2C_FIELD(arg2, s32 *, 0);
    var_v0 = 0;
    sp8 = M2C_FIELD(arg2, s32 *, 4);
    spC = M2C_FIELD(arg2, s32 *, 8);
    temp_t2 = *(spC + temp_t1_2);
    temp_t4 = *(sp4 + temp_t1_2);
    temp_t2_2 = (temp_t4 >= temp_v1_2) & 0xFF;
    if (((temp_t2 >= temp_v1_2) & 0xFF) != temp_t2_2) {
        temp_t5 = temp_a3 * 2;
        temp_t6 = *(sp4 + temp_t5);
        if (temp_t2_2 == (((s32) ((temp_t4 - temp_v1_2) * (*(spC + temp_t5) - temp_t6)) >> 8) >= ((s32) ((temp_t6 - temp_t0) * (temp_t2 - temp_t4)) >> 8))) {
            var_v0 = 1;
        }
    }
    temp_t2_3 = *(sp8 + temp_t1_2);
    temp_t2_4 = (temp_t2_3 >= temp_v1_2) & 0xFF;
    if ((temp_t2_2 & 0xFF) != temp_t2_4) {
        temp_t5_2 = temp_a3 * 2;
        temp_t6_2 = *(sp8 + temp_t5_2);
        if (temp_t2_4 == (((s32) ((temp_t2_3 - temp_v1_2) * (*(sp4 + temp_t5_2) - temp_t6_2)) >> 8) >= ((s32) ((temp_t6_2 - temp_t0) * (*(sp4 + temp_t1_2) - temp_t2_3)) >> 8))) {
            var_v0 = var_v0 == 0;
        }
    }
    temp_t2_5 = *(spC + temp_t1_2);
    temp_t2_6 = (temp_t2_5 >= temp_v1_2) & 0xFF;
    if ((temp_t2_4 & 0xFF) != temp_t2_6) {
        temp_t3 = temp_a3 * 2;
        temp_a3_2 = *(spC + temp_t3);
        if (temp_t2_6 == (((s32) ((temp_t2_5 - temp_v1_2) * (*(sp8 + temp_t3) - temp_a3_2)) >> 8) >= ((s32) ((temp_a3_2 - temp_t0) * (*(sp8 + temp_t1_2) - temp_t2_5)) >> 8))) {
            var_v0 = var_v0 == 0;
        }
    }
    return var_v0;
}
