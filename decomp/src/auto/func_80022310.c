#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80022310(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4_reg) {
    u16 arg4 = (u16) arg4_reg;
    s16 temp_v0;
    s32 temp_s1;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x1C);
    if ((M2C_FIELD(temp_v1, u8 *, 0x53) != arg4) && (M2C_FIELD(temp_v1, u8 *, 0x51) != arg4)) {
        M2C_FIELD(temp_v1, u8 *, 0x51) = (u8) arg4;
        M2C_FIELD(temp_v1, s8 *, 0x50) = 0;
        M2C_FIELD(temp_v1, s16 *, 0x4E) = 0;
    }
    temp_v0 = M2C_FIELD(temp_v1, s16 *, 0x4E);
    if (temp_v0 < arg3) {
        M2C_FIELD(temp_v1, s16 *, 0x4E) = (s16) (temp_v0 + 0x80);
    }
    temp_s1 = (s32) (arg2 * M2C_FIELD(temp_v1, s16 *, 0x4E)) >> 0xC;
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) + ((s32) (temp_s1 * rsin(arg1)) >> 0xC));
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + ((s32) (temp_s1 * rcos(arg1)) >> 0xC));
}
