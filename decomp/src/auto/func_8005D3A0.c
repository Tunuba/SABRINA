#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800D5818;

s32 func_8005D3A0(s32 arg0) {
    s32 temp_v0;
    s32 var_t9;
    s32 var_v0;

    var_v0 = arg0 & 0xFFFF;
    if (D_800D5818 != 0) {
        temp_v0 = arg0 * 3;
        var_t9 = temp_v0 >> 1;
        if (temp_v0 < 0) {
            var_t9 = (s32) (temp_v0 + 1) >> 1;
        }
        var_v0 = var_t9 & 0xFFFF;
    }
    return var_v0;
}
