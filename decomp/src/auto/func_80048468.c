#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80048468(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) + (((s32) -(M2C_FIELD(arg1, s32 *, 0x24) - M2C_FIELD(arg0, s32 *, 0x24)) >> 8) << 5));
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) M2C_FIELD(arg0, s32 *, 0x3C);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + (((s32) -(M2C_FIELD(arg1, s32 *, 0x2C) - M2C_FIELD(arg0, s32 *, 0x2C)) >> 8) << 5));
}
