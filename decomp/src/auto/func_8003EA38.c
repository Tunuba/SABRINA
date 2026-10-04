#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80074E94;


void func_8003EA38(s32 arg0) {
    s32 var_a0;
    s32 var_v1;

    *D_80074E94 &= 0xFFF8FFFF;
    if (arg0 != 0) {
        var_v1 = *D_80074E94;
        var_a0 = 0x30000;
    } else {
        var_v1 = *D_80074E94;
        var_a0 = 0x50000;
    }
    *D_80074E94 = var_v1 | var_a0;
}
