#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA0C;
extern s32 D_8007CA10;


void func_80018C8C(void) {
    Liberar(D_8007CA10);
    D_8007CA10 = 0;
    D_8007CA0C = 0;
}
