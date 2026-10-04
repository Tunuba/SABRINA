#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];

void func_800573C0(s32 arg0, s32 arg1, s32 arg2) {
    s16 temp_a0_2;
    s16 temp_a0_3;
    s16 temp_a0_5;
    s16 temp_t4;
    s32 temp_t4_2;
    s32 temp_t4_3;
    s32 temp_t4_4;
    s32 temp_t4_5;
    s32 temp_t4_6;
    s32 temp_t4_7;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    s32 var_t4;
    s32 var_t4_2;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a0_4;

    var_v1 = M2C_FIELD(arg0, s32 *, 0);
    var_t0 = M2C_FIELD(arg0, s32 *, 4);
    var_t1 = M2C_FIELD(arg0, s32 *, 8);
    temp_t4 = M2C_FIELD(arg0, s16 *, 0x10);
    var_t2 = var_v1;
    var_a3 = var_t0;
    var_v0 = var_t1;
    if (temp_t4 != 0) {
        var_t4 = temp_t4 * 0x18;
loop_16:
        temp_a0 = &D_800D588C[var_t4];
        if (arg0 == temp_a0) {

        } else {
            temp_t4_2 = M2C_FIELD(temp_a0, s32 *, 0);
            if (temp_t4_2 < var_t2) {
                var_t2 = temp_t4_2;
            }
            temp_t4_3 = M2C_FIELD(temp_a0, s32 *, 4);
            if (temp_t4_3 < var_a3) {
                var_a3 = temp_t4_3;
            }
            temp_t4_4 = M2C_FIELD(temp_a0, s32 *, 8);
            if (temp_t4_4 < var_v0) {
                var_v0 = temp_t4_4;
            }
            if (var_v1 < temp_t4_2) {
                var_v1 = temp_t4_2;
            }
            if (var_t0 < temp_t4_3) {
                var_t0 = temp_t4_3;
            }
            if (var_t1 < temp_t4_4) {
                var_t1 = temp_t4_4;
            }
            temp_a0_2 = M2C_FIELD(temp_a0, s16 *, 0x10);
            if (temp_a0_2 != 0) {
                var_t4 = temp_a0_2 * 0x18;
                goto loop_16;
            }
        }
    } else {
        temp_a0_3 = M2C_FIELD(arg0, s16 *, 0xE);
        if (temp_a0_3 != 0) {
            var_t4_2 = temp_a0_3 * 0x18;
loop_34:
            temp_a0_4 = &D_800D588C[var_t4_2];
            if (arg0 != temp_a0_4) {
                temp_t4_5 = M2C_FIELD(temp_a0_4, s32 *, 0);
                if (temp_t4_5 < var_t2) {
                    var_t2 = temp_t4_5;
                }
                temp_t4_6 = M2C_FIELD(temp_a0_4, s32 *, 4);
                if (temp_t4_6 < var_a3) {
                    var_a3 = temp_t4_6;
                }
                temp_t4_7 = M2C_FIELD(temp_a0_4, s32 *, 8);
                if (temp_t4_7 < var_v0) {
                    var_v0 = temp_t4_7;
                }
                if (var_v1 < temp_t4_5) {
                    var_v1 = temp_t4_5;
                }
                if (var_t0 < temp_t4_6) {
                    var_t0 = temp_t4_6;
                }
                if (var_t1 < temp_t4_7) {
                    var_t1 = temp_t4_7;
                }
                temp_a0_5 = M2C_FIELD(temp_a0_4, s16 *, 0xE);
                if (temp_a0_5 != 0) {
                    var_t4_2 = temp_a0_5 * 0x18;
                    goto loop_34;
                }
            }
        }
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) ((s32) (var_v1 - var_t2) >> 1);
    M2C_FIELD(arg1, s32 *, 4) = 0;
    M2C_FIELD(arg1, s32 *, 8) = (s32) ((s32) (var_t1 - var_v0) >> 1);
    temp_v1 = (s32) M2C_FIELD(arg1, s32 *, 0) >> 8;
    *arg2 = (s32) (((s32) (temp_v1 * temp_v1) >> 8) << 8);
    temp_v1_2 = (s32) M2C_FIELD(arg1, s32 *, 8) >> 8;
    *arg2 = (s32) (*arg2 + (((s32) (temp_v1_2 * temp_v1_2) >> 8) << 8));
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + var_t2);
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + var_v0);
}
