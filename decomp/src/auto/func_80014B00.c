#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80014B00(s32 arg0) {
    s32 var_v0;

    var_v0 = arg0;
    if (arg0 < 0) {
        var_v0 = -var_v0;
    }
    return var_v0;
}
