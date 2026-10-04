#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074CD8[];


s32 func_8003E060(void) {
    s32 temp_v0;

    temp_v0 = func_8002CF28(3, 0, 0);
    if (temp_v0 != -1) {
        return D_80074CD8[temp_v0];
    }
    return -1;
}
