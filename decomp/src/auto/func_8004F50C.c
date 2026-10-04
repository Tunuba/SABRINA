#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA20;
extern s32 D_8007CC44;
extern s16 D_8007CC4E;
extern u16 D_8007CC56;
extern s16 D_8007CC58;
extern s16 D_8007CC5A;


void func_8004F50C(s32 arg0) {
    M2C_UNK sp1C;

    D_8007CA20 = 0xF2;
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC4E = 0;
    if (D_8007CC56 == 2) {
        func_80051764(arg0);
        func_80051298(0, 0, (s32) &sp1C);
        D_8007CC44 = 2;
        D_8007CA20 = 0;
    }
}
