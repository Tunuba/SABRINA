#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80053B30(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0);
    temp_v0 = M2C_FIELD(arg0, s32 *, 0xC);
    if (temp_v0 < temp_v1) {
        M2C_FIELD(arg0, s32 *, 0xC) = temp_v1;
        M2C_FIELD(arg0, s32 *, 0) = temp_v0;
    }
    temp_v1_2 = M2C_FIELD(arg0, s32 *, 4);
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_v0_2 < temp_v1_2) {
        M2C_FIELD(arg0, s32 *, 0x10) = temp_v1_2;
        M2C_FIELD(arg0, s32 *, 4) = temp_v0_2;
    }
    temp_v1_3 = M2C_FIELD(arg0, s32 *, 8);
    temp_v0_3 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_v0_3 < temp_v1_3) {
        M2C_FIELD(arg0, s32 *, 0x14) = temp_v1_3;
        M2C_FIELD(arg0, s32 *, 8) = temp_v0_3;
    }
}
