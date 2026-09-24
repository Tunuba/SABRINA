#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_8007CA40;


void func_8001B494(void) {
    void *temp_a0;
    void *var_s0;

    var_s0 = D_8007CA40;
loop_2:
    if (var_s0 != NULL) {
        temp_a0 = var_s0;
        var_s0 = M2C_FIELD(var_s0, void **, 4);
        Liberar((s32) temp_a0);
        goto loop_2;
    }
    D_8007CA40 = NULL;
}
