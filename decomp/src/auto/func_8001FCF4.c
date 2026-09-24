#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8001FCF4(s32 arg0, s32 arg1) {
    void *temp_a1;

    M2C_FIELD(arg0, s16 *, 0xC) = (s16) M2C_FIELD(arg1, s16 *, 0x10);
    M2C_FIELD(arg0, s16 *, 0x18) = (s16) M2C_FIELD(arg1, s16 *, 0x12);
    temp_a1 = M2C_FIELD(arg1, void **, 0xC);
    M2C_FIELD(arg0, s16 *, 0x24) = (s16) M2C_FIELD(arg1, s16 *, 0x14);
    M2C_FIELD(arg0, u16 *, 0x1A) = (u16) M2C_FIELD(temp_a1, u16 *, 0xC);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(temp_a1, u16 *, 0xE);
}
