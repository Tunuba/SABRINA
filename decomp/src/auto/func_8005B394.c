#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005B394(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    M2C_FIELD(arg0, s32 *, 0x38) = (s32) -(M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg2, s32 *, 0));
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) -(M2C_FIELD(arg1, s32 *, 8) - M2C_FIELD(arg2, s32 *, 8));
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    func_8001C45C(arg0 + 0x38);
    temp_v0 = arg3 >> 8;
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x38) >> 4) * temp_v0) >> 8) << 8);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x40) >> 4) * temp_v0) >> 8) << 8);
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    M2C_FIELD(arg0, s16 *, 0x112) = 0x803;
    M2C_FIELD(arg0, s16 *, 0x114) = 1;
    M2C_FIELD(arg0, s8 *, 0x119) = 1;
    M2C_FIELD(arg0, s32 *, 0x74) = 0x5A;
}
