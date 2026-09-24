#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80063750;
extern s32 * D_80063754;


s32 func_80012054(s32 *arg0, s32 arg1) {
    s32 *var_a0;
    s32 temp_v1;
    s32 var_a2;

    var_a0 = arg0;
    var_a2 = arg1 - 1;
    *D_80063754 = 0x04000000;
    if (arg1 != 0) {
        do {
            temp_v1 = *var_a0;
            var_a0 += 4;
            var_a2 -= 1;
            *D_80063750 = temp_v1;
        } while (var_a2 != -1);
    }
    return 0;
}
