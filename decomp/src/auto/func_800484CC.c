#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800484CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;

    sp24 = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD(arg1, s32 *, 0);
    sp28 = M2C_FIELD(arg0, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4);
    sp2C = M2C_FIELD(arg0, s32 *, 8) - M2C_FIELD(arg1, s32 *, 8);
    func_8001C45C((s32) &sp24);
    temp_v1 = arg2 >> 8;
    temp_v0 = M2C_FIELD(arg1, s32 *, 0) + (((s32) ((sp24 >> 8) * temp_v1) >> 8) << 8);
    sp24 = temp_v0;
    temp_v0_2 = M2C_FIELD(arg1, s32 *, 8) + (((s32) ((sp2C >> 8) * temp_v1) >> 8) << 8);
    sp2C = temp_v0_2;
    temp_v0_3 = M2C_FIELD(arg1, s32 *, 4) + (((s32) ((sp28 >> 8) * temp_v1) >> 8) << 8);
    sp28 = temp_v0_3;
    M2C_FIELD(arg3, s32 *, 0) = (s32) (func_80021CE4(0x1000) - 0x800);
    M2C_FIELD(arg3, s32 *, 8) = (s32) (func_80021CE4(0x1000) - 0x800);
    M2C_FIELD(arg3, s32 *, 4) = (s32) (func_80021CE4(0x1000) - 0x800);
    func_8001C45C(arg3);
    M2C_FIELD(arg3, s32 *, 0) = (s32) (temp_v0 + (((s32) (((s32) M2C_FIELD(arg3, s32 *, 0) >> 8) * temp_v1) >> 8) << 8));
    M2C_FIELD(arg3, s32 *, 8) = (s32) (temp_v0_3 + (((s32) (((s32) M2C_FIELD(arg3, s32 *, 8) >> 8) * temp_v1) >> 8) << 8));
    M2C_FIELD(arg3, s32 *, 4) = (s32) (temp_v0_2 + (((s32) (((s32) M2C_FIELD(arg3, s32 *, 4) >> 8) * temp_v1) >> 8) << 8));
}
