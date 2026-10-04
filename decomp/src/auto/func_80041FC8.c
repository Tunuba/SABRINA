#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C6EF8[];

void func_80041FC8(s32 arg0, s32 arg1) {
    s32 temp_v1;
    s8 var_a3;
    u8 *temp_t0;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_a2_3;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1_2;
    void *var_t0;

    temp_t0 = &D_800C6EF8[(s32) (arg0 << 0x10) >> 0xE];
    temp_v1 = (s16) arg1 * 0xB0;
    temp_s0 = *temp_t0 + temp_v1;
    M2C_FIELD(temp_s0, s32 *, 0x98) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x98) & ~1);
    temp_a2 = temp_v1 + *temp_t0;
    M2C_FIELD(temp_a2, s32 *, 0x98) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x98) & ~2);
    temp_a2_2 = temp_v1 + *temp_t0;
    M2C_FIELD(temp_a2_2, s32 *, 0x98) = (s32) (M2C_FIELD(temp_a2_2, s32 *, 0x98) & ~8);
    temp_a2_3 = temp_v1 + *temp_t0;
    M2C_FIELD(temp_a2_3, s32 *, 0x98) = (s32) (M2C_FIELD(temp_a2_3, s32 *, 0x98) & ~0x400);
    temp_v1_2 = temp_v1 + *temp_t0;
    M2C_FIELD(temp_v1_2, s32 *, 0x98) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x98) | 4);
    _SsVmSeqKeyOff((s32) (s16) (arg0 | (arg1 << 8)));
    func_80042B68();
    var_a3 = 0;
    var_t0 = temp_s0;
    M2C_FIELD(temp_s0, s8 *, 0x14) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x88) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x1C) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x18) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x19) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x1E) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x1A) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x1B) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x1F) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x17) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x21) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x1C) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x1D) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x15) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x16) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x90) = (s32) M2C_FIELD(temp_s0, s32 *, 0x84);
    M2C_FIELD(temp_s0, s32 *, 0x94) = (s32) M2C_FIELD(temp_s0, s32 *, 0x8C);
    M2C_FIELD(temp_s0, u16 *, 0x54) = (u16) M2C_FIELD(temp_s0, u16 *, 0x56);
    M2C_FIELD(temp_s0, s32 *, 0) = (s32) M2C_FIELD(temp_s0, s32 *, 4);
    M2C_FIELD(temp_s0, s32 *, 8) = (s32) M2C_FIELD(temp_s0, s32 *, 4);
    do {
        temp_v0 = temp_s0 + var_a3;
        M2C_FIELD(temp_v0, s8 *, 0x37) = var_a3;
        M2C_FIELD(temp_v0, s8 *, 0x27) = 0x40;
        M2C_FIELD(var_t0, s16 *, 0x60) = 0x7F;
        var_a3 += 1;
        var_t0 += 2;
    } while (var_a3 < 0x10);
    M2C_FIELD(temp_s0, s16 *, 0x5C) = 0x7F;
    M2C_FIELD(temp_s0, s16 *, 0x5E) = 0x7F;
}
