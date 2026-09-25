#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006D304;


s32 func_80029A90(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_8006D304;
    D_8006D304 = arg0;
    return temp_v0;
}
