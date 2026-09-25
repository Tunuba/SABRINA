#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80090A98[];
extern s32 D_8006CFD0;


u8 *func_80028354(s32 arg0) {
    s32 var_v0;
    u8 *var_a1;

    var_a1 = D_80090A98;
    if (arg0 & 0xF0) {
        var_a1 = D_80090A98 + 0xF0;
    }
    if (D_8006CFD0 != 0) {
        var_v0 = arg0 & 3;
        if ((M2C_FIELD(var_a1, u8 *, 0xE8) != 8) || (var_v0 = arg0 & 3, ((arg0 & 0xF) != 0))) {
            if (var_v0 != 0) {
                var_v0 = arg0 & 3;
                goto block_7;
            }
        } else {
block_7:
            var_a1 = M2C_FIELD(var_a1, s32 *, 0xC) + (var_v0 * 0xF0);
        }
    }
    return var_a1;
}
