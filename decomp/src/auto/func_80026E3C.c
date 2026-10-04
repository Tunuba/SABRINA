#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80026E3C(void *arg0, s32 arg1, s32 arg2_reg) {
    s8 arg2 = (s8) arg2_reg;
    M2C_FIELD(arg0, s32 *, 0x28) = arg1;
    M2C_FIELD(arg0, s8 *, 0x34) = arg2;
}
