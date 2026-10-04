#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80060BE0[];
extern u8 D_80063688[];
extern u8 D_800636C8[];
extern u8 D_8006379A;

u8 D_800636C8[4];                                   /* unable to generate initializer: cannot parse D_80063688 as integer */

void func_80012CDC(s32 arg0) {
    M2C_UNK var_a0;

    if ((u8) D_8006379A >= 2U) {
        D_80063794("SetDispMask(%d)...\n", arg0);
    }
    if (arg0 == 0) {
        func_80012AE4((s32) (&D_8006379A + 0x6A), -1, 0x14);
    }
    var_a0 = 0x03000001;
    if (arg0 != 0) {
        var_a0 = 0x03000000;
    }
    M2C_FIELD(*D_800636C8, M2C_UNK (**)(M2C_UNK), 0x10)(var_a0);
}
