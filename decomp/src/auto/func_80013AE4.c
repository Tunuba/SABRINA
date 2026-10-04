#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80060C5C[];
extern u8 D_80063688[];
extern u8 D_800636C8[];
extern u8 D_800636EC[];
extern s32 * D_80063754;
extern s32 * D_80063760;
extern s32 D_80063780;
extern s32 D_80063784;
extern s32 func_80013D24();

u8 D_800636C8[4];                                   /* unable to generate initializer: cannot parse D_80063688 as integer */

s32 func_80013AE4(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 var_v0;
    s32 var_v0_2;

    func_800112C0((s32) D_80060C5C, arg0);
    D_80063780 = func_8001626C(-1) + 0xF0;
    D_80063784 = 0;
    var_v0_2 = *D_80063760;
loop_3:
    if (!(var_v0_2 & 0x01000000) && (*D_80063754 & 0x04000000)) {
        func_80016970(2, (s32) func_80013D24);
        var_v0 = -1;
        if (M2C_FIELD(arg0, s16 *, 4) != 0) {
            if (M2C_FIELD(arg0, s16 *, 6) == 0) {
                return -1;
            }
            temp_a1 = M2C_FIELD(arg0, s32 *, 0);
            M2C_FIELD(D_800636EC, s32 *, 4) = (s32) ((arg2 << 0x10) | (arg1 & 0xFFFF));
            M2C_FIELD(D_800636EC, s32 *, 0) = temp_a1;
            M2C_FIELD(D_800636EC, s32 *, 8) = (s32) M2C_FIELD(arg0, s16 *, 4);
            M2C_FIELD(*D_800636C8, M2C_UNK (**)(u8 *, s32), 0x18)(D_800636EC - 8, temp_a1);
            var_v0 = 0;
            /* Duplicate return node #9. Try simplifying control flow for better match */
            return var_v0;
        }
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = -1;
    if (func_80012900() == 0) {
        var_v0_2 = *D_80063760;
        goto loop_3;
    }
    return var_v0;
}
