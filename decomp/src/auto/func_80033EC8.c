#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80033EC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;

    M2C_FIELD(arg4, s32 *, 0) = arg2;
    M2C_FIELD(arg4, s32 *, 8) = (s32) -arg0;
    M2C_FIELD(arg4, s32 *, 4) = 0;
    temp_v0 = func_8001C33C(arg3, (s32) arg4);
    if (temp_v0 < 0) {
        M2C_FIELD(arg4, s32 *, 0) = (s32) -arg2;
        temp_v0_2 = -temp_v0;
        M2C_FIELD(arg4, s32 *, 8) = arg0;
        M2C_FIELD(arg4, s32 *, 0) = (s32) ((arg0 >> 6) + ((s32) (M2C_FIELD(arg4, s32 *, 0) * temp_v0_2) >> 8));
        var_v0 = (arg2 >> 6) + ((s32) (M2C_FIELD(arg4, s32 *, 8) * temp_v0_2) >> 8);
    } else {
        M2C_FIELD(arg4, s32 *, 0) = (s32) ((arg0 >> 6) + ((s32) (M2C_FIELD(arg4, s32 *, 0) * temp_v0) >> 8));
        var_v0 = (arg2 >> 6) + ((s32) (M2C_FIELD(arg4, s32 *, 8) * temp_v0) >> 8);
    }
    M2C_FIELD(arg4, s32 *, 8) = var_v0;
}
