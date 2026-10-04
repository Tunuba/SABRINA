#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086324[];
extern s32 D_8007CA24;


void func_80052FC0(s32 arg0) {
    s32 var_a2;
    s32 var_a3;
    u8 *temp_v1;
    void *temp_v0;

    temp_v0 = M2C_FIELD((arg0 + 0x74), void **, 0x18);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0xA4) = 0;
    }
    var_a2 = 0;
    var_a3 = 0;
loop_6:
    if (var_a2 < D_8007CA24) {
        temp_v1 = &D_80086324[var_a3];
        if (*temp_v1 == arg0) {
            *temp_v1 = 0;
            D_8007CA24 -= 1;
        }
        var_a2 += 1;
        var_a3 += 4;
        goto loop_6;
    }
    thunk_FUN_8004866c(arg0);
}
