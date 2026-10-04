#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80053400(void *arg0) {
    s32 temp_a1;
    s32 temp_v0_2;
    void *temp_v0;
    void *temp_v0_3;

    temp_v0 = M2C_FIELD(arg0, void **, 0x74);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(temp_v0, s32 *, 0x24);
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(temp_v0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_v0, s32 *, 0x2C);
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x74), s32 *, 0x50);
    temp_v0_2 = 0x1000 - ((s32) (M2C_FIELD(arg0, s32 *, 0x28) - M2C_FIELD(M2C_FIELD(arg0, void **, 0x74), s32 *, 0x28)) >> 5);
    M2C_FIELD(arg0, s32 *, 0x54) = temp_v0_2;
    M2C_FIELD(arg0, s32 *, 0x5C) = temp_v0_2;
    temp_v0_3 = M2C_FIELD(arg0, void **, 0x74);
    temp_a1 = M2C_FIELD(temp_v0_3, s32 *, 0x54);
    if (temp_a1 < 0x3E8) {
        M2C_FIELD(arg0, s32 *, 0x54) = temp_a1;
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(temp_v0_3, s32 *, 0x58);
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(temp_v0_3, s32 *, 0x5C);
    }
}
