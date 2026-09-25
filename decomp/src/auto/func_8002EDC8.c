#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800B4C5C[];
extern u8 D_800C4E2C[];

void func_8002EDC8(s32 arg0) {
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_s4;
    s32 var_s0;
    s32 var_s1;
    s8 *temp_v0_3;
    s8 *var_s2;
    u8 *var_s5;
    u8 *var_s6;
    u8 temp_a0_2;
    u8 temp_v0_2;
    void *temp_a0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s4 = M2C_FIELD(temp_v0, s16 *, 0x4C);
    temp_v1 = D_800B4C5C + ((M2C_FIELD(temp_v0, u8 *, 0x52) + *(D_800C4E2C + (M2C_FIELD(temp_v0, u8 *, 0x53) * 4))) * 0xC);
    var_s2 = temp_v0 + 0xA;
    temp_a0 = D_800B4C5C + ((M2C_FIELD(temp_v0, u8 *, 0x50) + *(D_800C4E2C + (M2C_FIELD(temp_v0, u8 *, 0x51) * 4))) * 0xC);
    temp_a2 = M2C_FIELD(temp_v1, s16 *, 4);
    M2C_FIELD(temp_v0, s16 *, 0) = (s16) (temp_a2 + ((s32) (temp_s4 * (M2C_FIELD(temp_a0, s16 *, 4) - temp_a2)) >> 0xC));
    temp_a2_2 = M2C_FIELD(temp_v1, s16 *, 6);
    M2C_FIELD(temp_v0, s16 *, 2) = (s16) (temp_a2_2 + ((s32) (temp_s4 * (M2C_FIELD(temp_a0, s16 *, 6) - temp_a2_2)) >> 0xC));
    temp_a2_3 = M2C_FIELD(temp_v1, s16 *, 8);
    M2C_FIELD(temp_v0, s16 *, 4) = (s16) (temp_a2_3 + ((s32) (temp_s4 * (M2C_FIELD(temp_a0, s16 *, 8) - temp_a2_3)) >> 0xC));
    M2C_FIELD(temp_v0, u16 *, 0x54) = (u16) M2C_FIELD(temp_a0, u16 *, 0xA);
    var_s6 = M2C_FIELD(temp_v1, u8 **, 0);
    var_s5 = M2C_FIELD(temp_a0, u8 **, 0);
    var_s1 = M2C_FIELD(temp_v0, u8 *, 8) * 3;
loop_6:
    if (var_s1 > 0) {
        temp_a0_2 = *var_s5;
        var_s5 += 1;
        temp_v0_2 = *var_s6;
        var_s0 = temp_a0_2 - temp_v0_2;
        var_s6 += 1;
        if (func_80014AEC(var_s0) >= 0x80) {
            if (var_s0 > 0) {
                var_s0 = -(0x100 - var_s0);
            } else {
                var_s0 += 0x100;
            }
        }
        var_s1 -= 1;
        temp_v0_3 = var_s2;
        var_s2 = temp_v0_3 + 1;
        *temp_v0_3 = temp_v0_2 + (((s32) (var_s0 * temp_s4) >> 0xC) & 0xFF);
        goto loop_6;
    }
}
