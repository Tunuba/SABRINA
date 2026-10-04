#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D5680;
extern s32 D_800D5684;
extern s32 D_800D5688;

s32 func_80053A98(s32 arg0) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v0;

    temp_a1 = (s32) (M2C_FIELD(arg0, s32 *, 0) - D_800D5680) >> 8;
    temp_a2 = (s32) (M2C_FIELD(arg0, s32 *, 4) - D_800D5684) >> 8;
    temp_a0 = (s32) (M2C_FIELD(arg0, s32 *, 8) - D_800D5688) >> 8;
    var_v0 = 0;
    if (((((s32) (temp_a1 * temp_a1) >> 8) << 8) + (((s32) (temp_a2 * temp_a2) >> 8) << 8) + (((s32) (temp_a0 * temp_a0) >> 8) << 8)) < 0x190000) {
        var_v0 = 1;
    }
    return var_v0;
}
