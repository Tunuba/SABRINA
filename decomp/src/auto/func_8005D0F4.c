#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800D5818;
extern u16 D_800D5822;

s32 func_8005D0F4(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_t9;
    s32 var_t9_2;
    s32 var_v0;

    if (D_800D5818 != 0) {
        temp_v0 = D_800D5822 - 1;
        var_t9 = temp_v0 >> 4;
        if (temp_v0 < 0) {
            var_t9 = (s32) (temp_v0 + 0xF) >> 4;
        }
        var_v0 = (var_t9 + 1) * 0x180;
    } else {
        temp_v0_2 = D_800D5822 - 1;
        var_t9_2 = temp_v0_2 >> 4;
        if (temp_v0_2 < 0) {
            var_t9_2 = (s32) (temp_v0_2 + 0xF) >> 4;
        }
        var_v0 = (var_t9_2 + 1) << 8;
    }
    return var_v0 >> 1;
}
