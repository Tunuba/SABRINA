#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_8003BB28();

void func_8003BBA8(void *arg0) {
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x54);
    if (temp_a1 >= 0x401) {
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_a1 + (((s32) (0x400 - temp_a1) >> 1) - 4));
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        return;
    }
    M2C_FIELD(arg0, s32 (**)(s32), 0) = func_8003BB28;
}
