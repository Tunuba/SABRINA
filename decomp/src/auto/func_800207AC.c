#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_800207AC(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg1, s32 *, 0x54) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
    M2C_FIELD(arg1, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) + (M2C_FIELD(arg2, s16 *, 0) * 0x1C));
    M2C_FIELD(arg1, s16 *, 0x5C) = (s16) M2C_FIELD(arg0, s16 *, 0x5C);
    M2C_FIELD(arg1, s16 *, 0x5E) = (s16) M2C_FIELD(arg2, s16 *, 2);
    M2C_FIELD(arg1, u8 *, 0x64) = (u8) M2C_FIELD(arg0, u8 *, 0x64);
    M2C_FIELD(arg1, u8 *, 0x64) = (u8) (M2C_FIELD(arg1, u8 *, 0x64) & 0xF7);
    return M2C_FIELD(arg2, s16 *, 2) & 0xFFFF;
}
