#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80053250(void *arg0, s32 arg1) {
    void *temp_v1;

    temp_v1 = arg0 + 0x74;
    M2C_FIELD(arg0, s32 *, 0x74) = arg1;
    M2C_FIELD(temp_v1, s32 *, 8) = 0;
    M2C_FIELD(temp_v1, s32 *, 4) = 0x32;
    if (M2C_FIELD(arg0, s32 *, 0x74) != 0) {
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
    }
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = -0x28;
    TocarSonido(0x22, 0, 0x2A, 0x7F);
}
