#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CB7C;


void func_8005C8E0(s32 arg0) {
    s32 var_a1;
    s32 var_a2;
    void *temp_v0;

    var_a1 = 0;
    var_a2 = 0;
loop_4:
    if (var_a1 < 5) {
        temp_v0 = M2C_FIELD((var_a2 + (arg0 + 0x74)), void **, 0x3C);
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_v0, s8 *, 0x20) = 0x80;
        }
        var_a1 += 1;
        var_a2 += 4;
        goto loop_4;
    }
    D_8007CB7C = 0;
    thunk_FUN_8004866c(arg0);
}
