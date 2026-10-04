#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CC84;


s32 func_8005D8A0(s32 arg0) {
    s32 temp_v0;
    s32 var_a0;

    var_a0 = arg0;
    temp_v0 = D_8007CC84;
    if (var_a0 & 3) {
        var_a0 = (var_a0 + 4) & ~3;
    }
    D_8007CC84 += var_a0;
    return temp_v0;
}
