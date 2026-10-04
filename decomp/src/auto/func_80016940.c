#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80064980[];
extern u8 D_800649A0[];

u8 D_800649A0[4];                                   /* unable to generate initializer: cannot parse D_80064980 as integer */

s32 func_80016940(void) {
    return M2C_FIELD(*D_800649A0, s32 (**)(), 8)();
}
