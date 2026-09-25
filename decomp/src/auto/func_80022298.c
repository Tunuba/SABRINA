#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80022298(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + ((s32) (arg2 * rsin(arg1)) >> 0xC));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + ((s32) (arg2 * rcos(arg1)) >> 0xC));
}
