#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006CF74;


s32 func_80025DD4(void) {
    s32 temp_v0;

    temp_v0 = D_8006CF74;
    D_8006CF74 = 0;
    return temp_v0;
}
