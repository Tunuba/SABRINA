#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CC98;
extern s32 D_8007CC9C;
extern s32 D_8007CCA0;
extern s32 D_8007CCA4;


void func_8005D844(void) {
    s32 sp18;
    s16 sp1C;
    s16 sp1E;
    s16 sp28;
    s16 sp2A;
    s32 sp30;

    sp18 = 0x2C3;
    sp1C = 0x3FFF;
    sp1E = 0x3FFF;
    sp28 = 0x3FFF;
    sp2A = 0x3FFF;
    D_8007CC9C = 0;
    D_8007CC98 = 0;
    D_8007CCA4 = 0;
    D_8007CCA0 = 0;
    sp30 = 1;
    SpuSetCommonAttr((s32) &sp18);
}
