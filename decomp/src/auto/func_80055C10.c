#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80055C10(void *arg0) {
    u16 *temp_s2;
    void *temp_s0;

    temp_s2 = M2C_FIELD(arg0, u16 **, 0x64);
    if (func_8002ECFC((s32) arg0) != 0) {
        temp_s0 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s0, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
        M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) *temp_s2;
        M2C_FIELD(temp_s0, u8 *, 0x50) = 0U;
        M2C_FIELD(temp_s0, u8 *, 0x53) = (u8) M2C_FIELD(temp_s0, u8 *, 0x51);
        M2C_FIELD(temp_s0, u8 *, 0x52) = (u8) M2C_FIELD(temp_s0, u8 *, 0x50);
        M2C_FIELD(temp_s0, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
    }
}
