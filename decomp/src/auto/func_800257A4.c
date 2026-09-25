#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8008AF88[];
extern s32 D_8007CB44;


void func_800257A4(void) {
    s32 var_v1;

    D_8007CB44 = 0;
    var_v1 = 0;
loop_4:
    if (var_v1 < 0x50) {
        if ((s8) D_8008AF88[var_v1] != 0) {
            D_8007CB44 += 1;
        }
        var_v1 += 1;
        goto loop_4;
    }
}
