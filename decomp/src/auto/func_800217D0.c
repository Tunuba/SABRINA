#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CAA0;
extern s32 D_8007CAA4;
extern s32 D_8007CAA8;
extern s32 D_8007CAAC;
extern s32 D_8007CAB0;
extern s32 D_8007CAB4;
extern s32 D_8007CAB8;
extern s32 D_8007CABC;
extern s32 D_8007CAC0;
extern s32 D_8007CAC4;
extern s32 D_8007CAC8;
extern s32 D_8007CACC;
extern s32 D_8007CAD0;
extern s32 D_8007CAD4;
extern s32 D_8007CAD8;
extern s32 D_8007CADC;
extern u16 D_8007CAE0;


void func_800217D0(void) {
    if (D_8007CAE0 != 0) {
        D_8007CAE0 = 0;
        D_8007CAC0 = D_8007CAA0;
        D_8007CAC4 = D_8007CAA4;
        D_8007CAC8 = D_8007CAA8;
        D_8007CACC = D_8007CAAC;
        D_8007CAD0 = D_8007CAB0;
        D_8007CAD4 = D_8007CAB4;
        D_8007CAD8 = D_8007CAB8;
        D_8007CADC = D_8007CABC;
        return;
    }
    D_8007CAC0 = D_8007CAA0 + 0x13880;
    D_8007CAC4 = D_8007CAA4 + 0xC8;
    D_8007CAC8 = D_8007CAA8 + 0x1F40;
    D_8007CACC = D_8007CAAC + 0x1388;
    D_8007CAD0 = D_8007CAB0 + 0x7D0;
    D_8007CAD4 = D_8007CAB4 + 0xC80;
    D_8007CAD8 = D_8007CAB8 + 0x3E8;
    D_8007CADC = D_8007CABC + 0xC;
    D_8007CAE0 = 1;
}
