#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024DE4();

void func_80038F08(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 (**)(), 0) = func_80024DE4;
    M2C_FIELD(arg1, s32 *, 0x54) = (s32) (M2C_FIELD(arg1, s32 *, 0x54) + 0x1000);
    if (M2C_FIELD(arg1, s32 *, 0x54) >= 0x1000) {
        M2C_FIELD(arg1, s32 *, 0x54) = 0x1000;
        func_800399E8(arg0, (s32) arg1);
        M2C_FIELD(arg1, s16 *, 0x112) = (s16) (M2C_FIELD(arg1, s16 *, 0x112) & 0x7FFF);
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        M2C_FIELD(arg1, s32 *, 0x11C) = 0;
    }
    M2C_FIELD(arg1, s32 *, 0x58) = (s32) M2C_FIELD(arg1, s32 *, 0x54);
    M2C_FIELD(arg1, s32 *, 0x5C) = (s32) M2C_FIELD(arg1, s32 *, 0x54);
}
