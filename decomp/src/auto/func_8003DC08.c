#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003DC08(void) {
    s16 var_s0;

    var_s0 = 0;
loop_2:
    if (var_s0 < 0x14) {
        func_80042924((s32) var_s0);
        var_s0 += 1;
        goto loop_2;
    }
}
