#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005E290(s32 arg0_reg, s32 arg1_reg, s32 arg2_reg, void *arg3) {
    s16 arg0 = (s16) arg0_reg;
    s16 arg1 = (s16) arg1_reg;
    s16 arg2 = (s16) arg2_reg;
    M2C_FIELD(arg3, s16 *, 0xA) = arg0;
    M2C_FIELD(arg3, s16 *, 0xC) = arg1;
    M2C_FIELD(arg3, s16 *, 0xE) = arg2;
}
