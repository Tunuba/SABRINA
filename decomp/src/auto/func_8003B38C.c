#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003B38C(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) M2C_FIELD(arg2, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) M2C_FIELD(arg2, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(arg2, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 0)) >> 8);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 0x10) - M2C_FIELD(arg0, s32 *, 4)) >> 8);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 0x14) - M2C_FIELD(arg0, s32 *, 8)) >> 8);
    func_8001C45C(arg0 + 0x18);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x18) >> 4);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x1C) >> 4);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x20) >> 4);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(arg0, s32 *, 0x20);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (0x10000 / (s32) M2C_FIELD(arg0, s32 *, 0x18));
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (0x10000 / (s32) M2C_FIELD(arg0, s32 *, 0x1C));
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (0x10000 / (s32) M2C_FIELD(arg0, s32 *, 0x20));
    M2C_FIELD(arg0, s16 *, 0x48) = 1;
}
