#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003BB28(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0xFA);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + ((s32) (rsin((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x3333) >> 0xC));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + ((s32) (rcos((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x3333) >> 0xC));
}
