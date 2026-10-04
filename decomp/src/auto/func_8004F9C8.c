#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 jugando;
extern s16 D_8007CA20;
extern s8 D_8007CA38;
extern s32 D_8007CA58;
extern s8 D_8007CC18;
extern u8 D_8007CC3C;
extern s16 D_8007CC4C;


void func_8004F9C8(void) {
    D_8007CC4C = 0;
    D_8007CA58 = 0;
    D_8007CA20 = 0;
    if (D_8007CC3C == 1) {
        jugando = 0;
        D_8007CC18 = 1;
        D_8007CA38 = 0;
    }
}
