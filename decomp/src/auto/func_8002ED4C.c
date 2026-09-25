#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8002ED4C(s32 arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x1C);
    M2C_FIELD(temp_a0, s16 *, 0x4C) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x4C) + M2C_FIELD(temp_a0, s16 *, 0x4E));
    if (M2C_FIELD(temp_a0, s16 *, 0x4C) & ~0xFFF) {
        M2C_FIELD(temp_a0, u8 *, 0x52) = (u8) M2C_FIELD(temp_a0, u8 *, 0x50);
        M2C_FIELD(temp_a0, u8 *, 0x53) = (u8) M2C_FIELD(temp_a0, u8 *, 0x51);
        M2C_FIELD(temp_a0, u8 *, 0x50) = (u8) (M2C_FIELD(temp_a0, u8 *, 0x50) + (((s16) M2C_FIELD(temp_a0, s16 *, 0x4C) >> 0xC) & 0xFF));
        M2C_FIELD(temp_a0, s16 *, 0x4C) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x4C) & 0xFFF);
    }
}
