#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800140DC(s32 arg0, s32 arg1) {
    u8 var_v0;

    if (arg1 != 0) {
        var_v0 = M2C_FIELD(arg0, u8 *, 7) | 2;
    } else {
        var_v0 = M2C_FIELD(arg0, u8 *, 7) & 0xFD;
    }
    M2C_FIELD(arg0, u8 *, 7) = var_v0;
}
