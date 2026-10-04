#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8005D164(s32 arg0) {
    s16 temp_a2;
    s16 temp_v0;
    s32 var_v0;

    temp_v0 = *arg0 - 8;
    *arg0 = temp_v0;
    if (temp_v0 < 0) {
        *arg0 = 0;
    }
    temp_a2 = *arg0;
    SsSetSerialVol(0, (s32) temp_a2, (s32) temp_a2);
    var_v0 = 0;
    if (*arg0 == 0) {
        var_v0 = 2;
    }
    return var_v0;
}
