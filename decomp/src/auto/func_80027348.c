#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80027348(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0x37) = 0x43;
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (arg0 + 0x24);
    M2C_FIELD(arg0, s8 *, 0x24) = (s8) arg1;
    M2C_FIELD(arg0, s8 *, 0x36) = 1;
}
