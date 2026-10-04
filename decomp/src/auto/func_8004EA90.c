#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8004EA90(void *arg1) {
    s32 var_v0;

    var_v0 = 0;
    if (arg1 != NULL) {
        var_v0 = M2C_FIELD(arg1, s32 *, -4);
    }
    return var_v0;
}
