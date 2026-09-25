#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003C8F8(void *arg0, s32 arg1_reg, s32 arg2) {
    s8 arg1 = (s8) arg1_reg;
    s32 temp_v1;
    void *temp_a1;
    void *temp_v0;

    temp_v0 = arg0 + 0x74;
    M2C_FIELD(temp_v0, s16 *, 0x24) = 0x32;
    M2C_FIELD(temp_v0, s16 *, 0x20) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x26) = 0;
    if (arg2 == 0) {
        if (arg1 != 0) {
            M2C_FIELD(arg0, s8 *, 0x119) = arg1;
        } else {
            M2C_FIELD(arg0, s8 *, 0x119) = 1;
        }
        temp_v1 = M2C_FIELD(temp_v0, s32 *, 4);
        if (temp_v1 > 0) {
            M2C_FIELD(temp_v0, s32 *, 4) = (s32) -temp_v1;
        }
        if (M2C_FIELD(arg0, s32 *, 0x74) <= 0) {
            M2C_FIELD(arg0, s32 *, 0x74) = 0x4000;
        }
        if (M2C_FIELD(temp_v0, s16 *, 0xC) & 0x100) {
            temp_a1 = M2C_FIELD(arg0, void **, 0x60);
            M2C_FIELD(temp_a1, u8 *, 0x64) = (u8) (M2C_FIELD(temp_a1, u8 *, 0x64) | 1);
            M2C_FIELD(arg0, s32 *, 0x54) = 1;
            M2C_FIELD(arg0, s32 *, 0x58) = 1;
            M2C_FIELD(arg0, s32 *, 0x5C) = 1;
            M2C_FIELD(arg0, s16 *, 0x112) = 0;
        }
        M2C_FIELD(temp_v0, s32 *, 0x14) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
        M2C_FIELD(temp_v0, s32 *, 0x18) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
        M2C_FIELD(temp_v0, s32 *, 0x1C) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
        M2C_FIELD(temp_v0, s16 *, 0x20) = (s16) M2C_FIELD(arg0, s16 *, 0x32);
        M2C_FIELD(arg0, s16 *, 0x70) = 1;
    }
}
