#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CBA8;


void func_80034770(s32 arg0) {
    D_8007CBA8 = 0;
    thunk_FUN_8004866c(arg0);
}
