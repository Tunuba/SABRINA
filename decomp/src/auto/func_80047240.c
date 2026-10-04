#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA1C;
extern s16 D_8007CA1E;
extern s16 D_8007CA20;
extern s8 D_8007CA38;


void func_80047240(void) {
    D_8007CA1C = 6;
    D_8007CA38 = 1;
    D_8007CA1E = 1;
    D_8007CA20 = 0xDF;
}
