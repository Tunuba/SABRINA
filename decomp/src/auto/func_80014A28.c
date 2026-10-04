#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_80063848;


s32 func_80014A28(void) {
    s32 var_v0;

    var_v0 = 0;
    if (M2C_FIELD(D_80063848, s32 *, 4) & 1) {
        var_v0 = 1;
        if (!(M2C_FIELD(D_80063848, s32 *, 0) & 1)) {
            var_v0 = 0;
        }
    }
    return var_v0;
}
