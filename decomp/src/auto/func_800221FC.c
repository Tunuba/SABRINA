#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_800221FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = (s32) (arg3 - arg0) >> 8;
    temp_a0 = (s32) (arg4 - arg1) >> 8;
    temp_a1 = (s32) (arg5 - arg2) >> 8;
    return (((s32) (temp_a1 * temp_a1) >> 8) + (((s32) (temp_v1 * temp_v1) >> 8) + ((s32) (temp_a0 * temp_a0) >> 8))) << 8;
}
