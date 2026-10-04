#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80012AE4(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;
    s32 var_v0;

    var_a0 = arg0;
    var_v0 = arg2 - 1;
    if (arg2 != 0) {
        do {
            *var_a0 = (s8) arg1;
            var_v0 -= 1;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}
