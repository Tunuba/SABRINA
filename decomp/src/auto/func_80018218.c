#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80084CE0[];
extern u8 D_800653F8[];


void func_80018218(void) {
    s16 var_v1;
    s32 var_a0;
    s32 var_s0;
    u8 *temp_v0;

    var_s0 = Reservar(0x190C8, (s32) "BasicTools.c");
    memset(var_s0, 0, 0x190C8);
    var_v1 = 0;
    var_a0 = 0;
loop_2:
    if (var_v1 != 0x3B6) {
        temp_v0 = &D_80084CE0[var_a0];
        *temp_v0 = var_s0;
        var_s0 += 0x6C;
        M2C_FIELD(*temp_v0, s16 *, 0x62) = var_v1;
        var_v1 += 1;
        var_a0 += 4;
        goto loop_2;
    }
}
