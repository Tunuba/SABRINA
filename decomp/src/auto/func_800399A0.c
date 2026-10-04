#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800399A0(s32 arg0, s32 arg1) {
    void *temp_v1;

    temp_v1 = arg1 + 0x74;
    M2C_FIELD(temp_v1, s32 *, 0x14) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(temp_v1, s32 *, 0x1C) = (s32) M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(temp_v1, s32 *, 0x20) = (s32) M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(temp_v1, s32 *, 0x24) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(temp_v1, s32 *, 0x28) = (s32) M2C_FIELD(arg0, s32 *, 0x10);
    M2C_FIELD(temp_v1, s32 *, 0x2C) = (s32) M2C_FIELD(arg0, s32 *, 0x14);
}
