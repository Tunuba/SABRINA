#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_8006CF6C;
extern void * D_8006CF70;


s32 func_800266B4(void) {
    s32 var_v0;

    *D_8006CF6C = -0x81;
    if (M2C_FIELD(D_8006CF70, u16 *, 4) & 0x80) {
loop_1:
        var_v0 = 0;
        if (func_800290AC() == 0) {
            if (!(M2C_FIELD(D_8006CF70, u16 *, 4) & 0x80)) {
                goto block_3;
            }
            goto loop_1;
        }
    } else {
block_3:
        var_v0 = 1;
        M2C_FIELD(D_8006CF70, u16 *, 0xA) = (u16) (M2C_FIELD(D_8006CF70, u16 *, 0xA) | 0x10);
    }
    return var_v0;
}
