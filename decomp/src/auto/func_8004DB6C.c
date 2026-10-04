#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8004DB6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    s32 var_v0;

    arg1 = (s32) (arg1 - M2C_FIELD(arg4, s32 *, 0x24)) >> 8;
    arg2 = 0;
    arg3 = (s32) (arg3 - M2C_FIELD(arg4, s32 *, 0x2C)) >> 8;
    var_v0 = 0;
    if (func_8001C33C((s32) &arg1, (s32) &arg1) < M2C_FIELD(arg4, s32 *, 0x7C)) {
        *arg0 = (s32) ((M2C_FIELD(arg4, s32 *, 0x28) - 0x199A) - 0x7FFF);
        var_v0 = 1;
    }
    return var_v0;
}
