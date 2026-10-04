#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80091424;
extern s32 D_80091428;
extern s32 D_8009142C;

void func_8002D520(s32 arg0, s32 arg1, s32 arg2) {
    D_80091424 = arg0;
    D_80091428 = arg1;
    D_8009142C = arg2;
}
