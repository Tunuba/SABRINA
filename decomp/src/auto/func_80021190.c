#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80021190(void) {
    M2C_UNK sp24;
    s8 sp34;

    SetDefDispEnv((s32) &sp24, 0x1FF, 0, 0x200, /* extra? */ 0x1E0);
    func_8001321C((s32) &sp24);
    sp34 = 1;
}
