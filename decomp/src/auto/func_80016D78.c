#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80016D78(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_v0;

    var_a0 = arg0;
    var_v0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            *var_a0 = 0;
            var_v0 -= 1;
            var_a0 += 4;
        } while (var_v0 != -1);
    }
}
