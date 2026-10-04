#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80037EE0(void *arg0, s32 arg1_reg, s32 arg2) {
    s8 arg1 = (s8) arg1_reg;
    void *temp_v1;

    temp_v1 = arg0 + 0x74;
    M2C_FIELD(temp_v1, s8 *, 4) = 6;
    M2C_FIELD(temp_v1, s8 *, 5) = 1;
    M2C_FIELD(temp_v1, s32 *, 8) = 0x32;
    M2C_FIELD(arg0, s8 *, 0x119) = arg1;
    M2C_FIELD(temp_v1, s32 *, 0xC) = arg2;
    if (M2C_FIELD(arg0, s32 *, 0x74) >= 0) {
        M2C_FIELD(arg0, s32 *, 0x74) = 0x4000;
    }
}
