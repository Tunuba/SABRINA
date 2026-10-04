#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007CB50;


void func_800547EC(void *arg0) {
    void *temp_s0;
    void *temp_v1;

    temp_v1 = arg0 + 0x74;
    M2C_FIELD(temp_v1, s8 *, 5) = 0xA;
    M2C_FIELD(arg0, s8 *, 0x118) = 5;
    M2C_FIELD(temp_v1, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    if (func_8002ECFC((s32) arg0) != 0) {
        temp_s0 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s0, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x4E) = 0;
        M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) D_8007CB50;
        M2C_FIELD(temp_s0, u8 *, 0x50) = 0U;
        M2C_FIELD(temp_s0, u8 *, 0x53) = (u8) M2C_FIELD(temp_s0, u8 *, 0x51);
        M2C_FIELD(temp_s0, u8 *, 0x52) = (u8) M2C_FIELD(temp_s0, u8 *, 0x50);
        M2C_FIELD(temp_s0, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
    }
}
