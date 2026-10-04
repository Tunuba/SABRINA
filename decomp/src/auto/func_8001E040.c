#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_8007CA70;


s32 func_8001E040(void) {
    s32 var_v0;

    var_v0 = 0;
    if (M2C_FIELD(D_8007CA70, u16 *, 0x20) & 0x840) {
        var_v0 = 1;
    }
    return var_v0;
}
