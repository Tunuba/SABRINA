#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8001164C(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v0;
    s32 var_v1;

    var_v1 = 0xE1000000;
    if (arg1 != 0) {
        var_v1 = 0xE1000200;
    }
    var_v0 = arg2 & 0x9FF;
    if (arg0 != 0) {
        var_v0 |= 0x400;
    }
    return var_v1 | var_v0;
}
