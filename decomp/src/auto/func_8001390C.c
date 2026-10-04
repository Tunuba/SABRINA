#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80060D2C[];
extern u8 D_80063688[];
extern u8 D_800636C8[];
extern s32 * D_80063754;
extern s32 * D_80063760;
extern s32 D_80063780;
extern s32 D_80063784;
extern s32 func_80013D24();

u8 D_800636C8[4];                                   /* unable to generate initializer: cannot parse D_80063688 as integer */

s32 func_8001390C(s32 arg0, M2C_UNK arg1) {
    s32 var_v0;
    s32 var_v0_2;

    func_800112C0((s32) D_80060D2C, arg0);
    D_80063780 = func_8001626C(-1) + 0xF0;
    D_80063784 = 0;
    var_v0_2 = *D_80063760;
loop_3:
    if (!(var_v0_2 & 0x01000000) && (*D_80063754 & 0x04000000)) {
        func_80016970(2, (s32) func_80013D24);
        M2C_FIELD(*D_800636C8, M2C_UNK (**)(s32, M2C_UNK), 0x20)(arg0, arg1);
        var_v0 = 0;
    } else {
        var_v0 = -1;
        if (func_80012900() == 0) {
            var_v0_2 = *D_80063760;
            goto loop_3;
        }
    }
    return var_v0;
}
