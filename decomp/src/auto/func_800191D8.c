#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_8006553C[];


void func_800191D8(s8 *arg0, void *arg1) {
    s32 var_a2;
    s32 var_v1;

    var_v1 = 0;
    var_a2 = 0x45;
loop_2:
    if (var_a2 != 0x7F) {
        var_a2 = *(arg0 + var_v1) & 0xFFFF;
        var_v1 = (var_v1 + 1) & 0xFFFF;
        goto loop_2;
    }
    if (var_v1 == 1) {
        var_v1 = 2;
        *arg0 = *D_8006553C;
    }
    M2C_FIELD(arg1, s16 *, 0x16) = (s16) (var_v1 - 1);
    M2C_FIELD(arg1, s16 *, 0x18) = 0;
}
