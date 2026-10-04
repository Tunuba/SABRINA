#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80029948(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v0;

    if (arg0 == 2) {
        func_8002B270(arg0, arg1, arg2);
        return 1;
    }
    var_v0 = 0;
    if (func_8002B2BC() == 0) {
        var_v0 = 1;
        if (arg0 == 1) {
            var_v0 = 0;
            if (func_8002B180() == 0) {
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
