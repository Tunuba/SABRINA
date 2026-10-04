#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D5304;

s32 func_80051284(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_800D5304;
    D_800D5304 = arg0;
    return temp_v0;
}
