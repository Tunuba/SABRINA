#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CC70;


void func_80055F00(s32 arg0) {
    func_800249CC(arg0, -1);
    D_8007CC70 = 0;
    thunk_FUN_8004866c(arg0);
}
