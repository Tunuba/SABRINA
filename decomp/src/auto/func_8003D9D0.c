#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C65E0[];
extern s32 D_8007CBDC;
extern s16 D_8007CBE4;


void func_8003D9D0(void) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0x14;
    var_s1 = 0x28;
loop_2:
    if (var_s0 != 0) {
        D_800C65E0[var_s1] = 0;
        thunk_FUN_80042924(var_s0);
        var_s0 = (var_s0 - 1) & 0xFF;
        var_s1 -= 2;
        goto loop_2;
    }
    SsVabClose((s32) D_8007CBE4);
    Liberar(D_8007CBDC);
}
