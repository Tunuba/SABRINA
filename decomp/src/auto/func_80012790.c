#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80063754;
extern s32 * D_80063760;
extern s32 D_80063818;
extern s32 D_8006381C[];


s32 func_80012790(s32 arg0) {
    s32 temp_s0;
    s32 var_v0;

    if (arg0 == 0) {
        func_800128CC();
loop_3:
        if (D_80063818 != *D_8006381C) {
            func_800123E0();
            var_v0 = -1;
            if (func_80012900() == 0) {
                goto loop_3;
            }
            /* Duplicate return node #15. Try simplifying control flow for better match */
            return var_v0;
        }
loop_6:
        if (!(*D_80063760 & 0x01000000) && (*D_80063754 & 0x04000000)) {
            return 0;
        }
        var_v0 = -1;
        if (func_80012900() == 0) {
            goto loop_6;
        }
        /* Duplicate return node #15. Try simplifying control flow for better match */
        return var_v0;
    }
    temp_s0 = (D_80063818 - *D_8006381C) & 0x3F;
    if (temp_s0 != 0) {
        func_800123E0();
    }
    if ((*D_80063760 & 0x01000000) || (var_v0 = temp_s0, ((*D_80063754 & 0x04000000) == 0))) {
        var_v0 = temp_s0;
        if (temp_s0 == 0) {
            var_v0 = 1;
        }
    }
    return var_v0;
}
