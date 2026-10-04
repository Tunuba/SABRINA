#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80026E04(void *arg0, s32 arg1_reg) {
    s8 arg1 = (s8) arg1_reg;
    M2C_FIELD(arg0, s8 *, 0x37) = 0x47;
    M2C_FIELD(arg0, void **, 0x2C) = (void *) (arg0 + 0x24);
    M2C_FIELD(arg0, s8 *, 0x24) = arg1;
    M2C_FIELD(arg0, s8 *, 0x36) = 1;
}
