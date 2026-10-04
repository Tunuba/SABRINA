#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003B53C(s32 arg0, s32 arg2_reg) {
    s16 arg2 = (s16) arg2_reg;
    void *temp_v1;

    temp_v1 = arg0 + 0x74;
    M2C_FIELD(temp_v1, s16 *, 0x1C) = arg2;
    M2C_FIELD(temp_v1, s16 *, 0x18) = 0x14;
    M2C_FIELD(arg0, s32 *, 0x50) = func_8002244C(arg0);
}
