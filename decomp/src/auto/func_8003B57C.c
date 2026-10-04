#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003B57C(void *arg0) {
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v1;
    s16 temp_v1_4;
    s32 *temp_v1_3;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_a0;
    void *temp_s0;

    temp_s0 = arg0 + 0x74;
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + rsin(M2C_FIELD(temp_s0, s16 *, 0x1C) << 6));
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + rsin(M2C_FIELD(temp_s0, s16 *, 0x1C) << 5));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + rsin(M2C_FIELD(temp_s0, s16 *, 0x1C) * 0x10));
    temp_v1 = M2C_FIELD(temp_s0, s16 *, 0x1C);
    M2C_FIELD(temp_s0, s16 *, 0x1C) = (s16) (temp_v1 - 1);
    if (temp_v1 <= 0) {
        var_a0 = 0x12C;
        if (M2C_FIELD(arg0, s32 *, 0x54) < 0x200) {
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
            return;
        }
        goto block_4;
    }
    var_a0 = 0x1000;
block_4:
    temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x54);
    M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v1_2 + ((s32) (var_a0 - temp_v1_2) >> 2));
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
    M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
    if (M2C_FIELD(temp_s0, s16 *, 0x14) < 5) {
        sp24 = M2C_FIELD(arg0, s32 *, 0x24);
        sp28 = M2C_FIELD(arg0, s32 *, 0x28);
        sp2C = M2C_FIELD(arg0, s32 *, 0x2C);
        temp_v0 = func_8002506C((s32) &sp24, 0x3E8, (s32) arg0);
        if (temp_v0 != 0) {
            sp24 = (s32) (sp24 - M2C_FIELD(temp_v0, s32 *, 0x24)) >> 8;
            sp28 = (s32) (sp28 - M2C_FIELD(temp_v0, s32 *, 0x28)) >> 8;
            sp2C = (s32) (sp2C - M2C_FIELD(temp_v0, s32 *, 0x2C)) >> 8;
            if (func_8001C33C((s32) &sp24, (s32) &sp24) < 0x1900) {
                M2C_FIELD(arg0, M2C_UNK (**)(void *, s32), 8)(arg0, temp_v0);
            }
        }
    }
    temp_v0_2 = M2C_FIELD(temp_s0, s16 *, 0x14);
    if (temp_v0_2 != 0) {
        temp_v0_3 = M2C_FIELD(temp_s0, s16 *, 0x18);
        if (temp_v0_3 > 0) {
            temp_v1_3 = temp_s0 + (M2C_FIELD(temp_s0, s16 *, 0x16) * 4);
            temp_s2 = *temp_v1_3;
            if (temp_s2 != 0) {
                if (temp_v0_3 == 0x14) {
                    func_8003B894((s32) arg0, temp_s2, 0x20000, 0xF);
                    func_8003B894((s32) arg0, temp_s2, 0x10000, 0x10);
                }
            } else {
                *temp_v1_3 = *(temp_s0 + ((temp_v0_2 - 1) * 4));
                *(temp_s0 + ((M2C_FIELD(temp_s0, s16 *, 0x14) - 1) * 4)) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x14) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x14) - 1);
                M2C_FIELD(temp_s0, s16 *, 0x18) = 0;
            }
            if (M2C_FIELD(temp_s0, s16 *, 0x18) == 1) {
                M2C_FIELD(arg0, s16 *, 0x112) = 0x1800;
                M2C_FIELD(arg0, s8 *, 0x119) = 1;
            } else {
                M2C_FIELD(arg0, s16 *, 0x112) = 8;
                M2C_FIELD(arg0, s8 *, 0x119) = 0;
            }
            M2C_FIELD(temp_s0, s16 *, 0x18) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x18) - 1);
            return;
        }
        temp_v1_4 = M2C_FIELD(temp_s0, s16 *, 0x1A);
        M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16) (temp_v1_4 - 1);
        if (temp_v1_4 < 0) {
            M2C_FIELD(temp_s0, s16 *, 0x1A) = 5;
            M2C_FIELD(temp_s0, s16 *, 0x18) = 0x14;
            M2C_FIELD(temp_s0, s16 *, 0x16) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x16) + 1);
            if (M2C_FIELD(temp_s0, s16 *, 0x16) >= M2C_FIELD(temp_s0, s16 *, 0x14)) {
                M2C_FIELD(temp_s0, s16 *, 0x16) = 0;
            }
        }
    }
}
