#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA20;
extern s8 D_8007CC3C;
extern s16 D_8007CC4E;
extern s16 D_8007CC58;
extern s16 D_8007CC5A;


void func_8004F968(s32 arg0, s32 arg1, s32 arg2) {
    s16 var_v0;

    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC4E = 0;
    D_8007CC3C = 1;
    if (arg2 != 0) {
        var_v0 = 0x103;
    } else {
        var_v0 = 0xFF;
    }
    D_8007CA20 = var_v0;
}
