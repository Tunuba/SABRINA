#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800649C0[];


void func_80016A98(s32 arg0, s32 arg1) {
    s32 *temp_a0;

    temp_a0 = &D_800649C0[arg0];
    if (arg1 != *temp_a0) {
        *temp_a0 = arg1;
    }
}
