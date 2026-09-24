#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80063851[];


s32 func_80014B4C(s32 arg0) {
    s32 var_v1;

    var_v1 = arg0;
    if (D_80063851[var_v1 & 0xFF] & 2) {
        var_v1 = arg0 - 0x20;
    }
    return (s32) (s8) var_v1;
}
