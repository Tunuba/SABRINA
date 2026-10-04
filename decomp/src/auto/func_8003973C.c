#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80074BCF[];


void func_8003973C(void *arg0, s32 arg1_reg, s32 arg2) {
    s8 arg1 = (s8) arg1_reg;
    void *temp_a0;

    temp_a0 = arg0 + 0x74;
    if (M2C_FIELD(arg0, s8 *, 0x74) == 0) {
        M2C_FIELD(arg0, s8 *, 0x74) = arg1;
    }
    M2C_FIELD(temp_a0, s32 *, 4) = arg2;
    M2C_FIELD(temp_a0, s32 *, 8) = (s32) M2C_FIELD(temp_a0, s32 *, 4);
    M2C_FIELD(temp_a0, s8 *, 1) = (s8) *(D_80074BCF + (M2C_FIELD(arg0, s8 *, 0x74) * 0x10));
}
