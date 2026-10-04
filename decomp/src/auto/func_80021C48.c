#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006C468[];
extern u16 D_8007CAF0;
extern s16 D_8007CAF2;
extern s32 D_8007CAF4;


void func_80021C48(s32 arg0) {
    s16 var_s0;
    s32 var_s1;

    D_8007CAF0 = arg0 - 1;
    D_8007CAF2 = 0;
    D_8007CAF4 = Reservar(arg0 * 2, (s32) "StratTools.c");
    var_s0 = (s16) D_8007CAF0;
    var_s1 = var_s0 * 2;
loop_2:
    if (var_s0 >= 0) {
        *(D_8007CAF4 + var_s1) = (func_80014F10() & 0x7FFF) * 2;
        var_s0 -= 1;
        var_s1 -= 2;
        goto loop_2;
    }
}
