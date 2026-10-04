#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800399E8(s32 arg0, s32 arg1) {
    void *temp_v1;

    temp_v1 = arg0 + 0x74;
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(temp_v1, s32 *, 0x14);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(temp_v1, s32 *, 0x1C);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(temp_v1, s32 *, 0x20);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(temp_v1, s32 *, 0x24);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) M2C_FIELD(temp_v1, s32 *, 0x28);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) M2C_FIELD(temp_v1, s32 *, 0x2C);
}
