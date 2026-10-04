#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_800756EA[];
extern u16 D_8007C7B0[];
extern s32 D_8007CA18;
extern s16 D_8007CA1C;
extern s16 D_8007CA1E;
extern s8 D_8007CA38;
extern s32 D_8007CB34;
extern u16 D_8007CC00;


void func_80019464(s32 arg0) {
    D_8007CC00 = (u16) arg0;
    D_8007CA18 = 0;
    switch (arg0) {                                 /* irregular */
    case 0:
        D_8007CA18 = 1;
        break;
    case 1:
        D_8007CA18 = 4;
        break;
    case 2:
        D_8007CA18 = 7;
        break;
    case 3:
        D_8007CA18 = 0xA;
        break;
    default:
        Afirmar(0);
        break;
    }
    *D_800756EA = D_8007C7B0[D_8007CC00];
    D_8007CA38 = 1;
    D_8007CA1C = 5;
    D_8007CA1E = 0;
    D_8007CB34 = 1;
}
