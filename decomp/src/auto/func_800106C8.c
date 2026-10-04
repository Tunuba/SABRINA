#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_800106C8(void) {
    M2C_UNK (*temp_v0)();
    M2C_UNK (*var_s0)();

    var_s0 = D_800609B0;
loop_2:
    temp_v0 = *var_s0;
    if (temp_v0 != NULL) {
        temp_v0();
        var_s0 += 4;
        goto loop_2;
    }
    BuclePrincipal();
}
