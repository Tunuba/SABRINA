#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8001C180(s32 arg0) {
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;

    temp_v1 = (s32) M2C_FIELD(arg0, s32 *, 0) >> 8;
    temp_v1_2 = (s32) M2C_FIELD(arg0, s32 *, 4) >> 8;
    temp_v1_3 = (s32) M2C_FIELD(arg0, s32 *, 8) >> 8;
    return ((s32) (temp_v1 * temp_v1) >> 8) + ((s32) (temp_v1_2 * temp_v1_2) >> 8) + ((s32) (temp_v1_3 * temp_v1_3) >> 8);
}
