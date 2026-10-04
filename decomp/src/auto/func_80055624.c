#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80055624(s32 arg0) {
    void *temp_v0;

    temp_v0 = arg0 + 0x74;
    M2C_FIELD(temp_v0, s32 *, 0x14) = 0;
    M2C_FIELD(temp_v0, s32 *, 0x18) = 0;
}
