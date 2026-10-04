#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800539D0(void *arg0) {
    void *temp_a1;

    temp_a1 = arg0 + 0x74;
    M2C_FIELD(temp_a1, s16 *, 6) = 0x280;
    M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) - M2C_FIELD(temp_a1, s16 *, 4));
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) - M2C_FIELD(temp_a1, s16 *, 4));
    M2C_FIELD(arg0, s32 *, 0x5C) = (s32) (M2C_FIELD(arg0, s32 *, 0x5C) - M2C_FIELD(temp_a1, s16 *, 4));
    M2C_FIELD(arg0, s32 *, 0xF8) = (s32) (M2C_FIELD(arg0, s32 *, 0xF8) - 0x6666);
    if (M2C_FIELD(arg0, s32 *, 0x54) < 3) {
        M2C_FIELD(arg0, s32 *, 0x54) = 5;
        M2C_FIELD(arg0, s32 *, 0x58) = 5;
        M2C_FIELD(arg0, s32 *, 0x5C) = 5;
        M2C_FIELD(arg0, s32 *, 0xF8) = 0;
        M2C_FIELD(arg0, s16 *, 0x114) = 0;
        M2C_FIELD(arg0, s16 *, 0x112) = 0;
    }
}
