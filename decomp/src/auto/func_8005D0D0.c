#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800D5818;

s32 func_8005D0D0(void) {
    s32 var_v0;

    var_v0 = 2;
    if (D_800D5818 != 0) {
        var_v0 = 3;
    }
    return var_v0 & 0xFFFF;
}
