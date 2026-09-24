#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8006379C;
extern s16 D_8006379E;


s32 func_8001166C(s32 arg0, s32 arg1) {
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    if ((s16) arg0 >= 0) {
        var_v0 = (u16) D_8006379C - 1;
        if ((D_8006379C - 1) >= (s16) arg0) {
            var_v0 = arg0;
        }
    }
    if ((s16) arg1 >= 0) {
        var_v1 = arg1 & 0x3FF;
        if ((D_8006379E - 1) < (s16) arg1) {
            var_a1 = (u16) D_8006379E - 1;
            goto block_7;
        }
    } else {
        var_a1 = 0;
block_7:
        var_v1 = var_a1 & 0x3FF;
    }
    return (var_v1 << 0xA) | ((var_v0 & 0x3FF) | 0xE3000000);
}
