#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80038EB4(s32 arg0, s32 arg1) {
    func_800399E8(arg0, arg1);
    M2C_FIELD(arg1, s16 *, 0x112) = (s16) (M2C_FIELD(arg1, s16 *, 0x112) & 0x7FFF);
    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
    M2C_FIELD(arg1, s32 *, 0x11C) = 0;
}
