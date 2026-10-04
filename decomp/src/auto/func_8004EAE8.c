#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D1604;
extern s32 D_800D1608;
extern s32 D_800D160C;

void func_8004EAE8(s32 arg0, s32 arg1, s32 arg2) {
    D_800D1604 = arg0;
    D_800D1608 = arg1;
    D_800D160C = arg2;
}
