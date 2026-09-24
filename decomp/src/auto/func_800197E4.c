#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007961C[];


void func_800197E4(void) {
    s32 var_a0;

    var_a0 = 0;
loop_2:
    if (var_a0 != 0x41) {
        D_8007961C[var_a0] = 0x7E;
        var_a0 = (var_a0 + 1) & 0xFFFF;
        goto loop_2;
    }
}
