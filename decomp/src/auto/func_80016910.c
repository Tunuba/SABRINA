#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80064980[];
extern u8 D_800649A0[];

u8 D_800649A0[4];                                   /* unable to generate initializer: cannot parse D_80064980 as integer */

void func_80016910(void) {
    M2C_FIELD(*D_800649A0, M2C_UNK (**)(), 0xC)();
}
