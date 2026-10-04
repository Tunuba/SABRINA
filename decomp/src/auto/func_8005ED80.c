#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007C872;


void func_8005ED80(s32 arg0) {
    D_8007C872 = 0;
    thunk_FUN_8004866c(arg0);
}
