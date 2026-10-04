#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80064980[];
extern u8 D_800649A0[];

u8 D_800649A0[4];                                   /* unable to generate initializer: cannot parse D_80064980 as integer */

void func_800169A0(s32 arg0) {
    M2C_FIELD(*D_800649A0, M2C_UNK (**)(M2C_UNK, s32), 0x14)(4, arg0);
}
