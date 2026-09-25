#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_8006CF6C;

static M2C_UNK (*D_8006CFAC)() = NULL;

s32 func_800259A8(void) {
    s32 var_v0;

    var_v0 = 0;
    if (M2C_FIELD(D_8006CF6C, s32 *, 4) & 1) {
        var_v0 = 0;
        if (M2C_FIELD(D_8006CF6C, s32 *, 0) & 1) {
            if (D_8006CFAC != NULL) {
                D_8006CFAC();
            }
            var_v0 = 1;
        }
    }
    return var_v0;
}
