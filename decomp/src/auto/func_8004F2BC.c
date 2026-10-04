#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA20;
extern s16 D_8007CC4E;
extern s16 D_8007CC50;
extern s16 D_8007CC58;
extern s16 D_8007CC5A;


void func_8004F2BC(void) {
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC50 = 0;
    D_8007CC4E = 0;
    D_8007CA20 = 0xE3;
}
