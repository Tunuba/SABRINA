#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80038154(void *arg0) {
    s32 temp_v0;
    void *temp_a0;

    temp_a0 = arg0 + 0x74;
    temp_v0 = M2C_FIELD(temp_a0, s32 *, 8);
    if (temp_v0 > 0) {
        M2C_FIELD(temp_a0, s32 *, 8) = (s32) (temp_v0 - 1);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
        CrearParticula((s32) M2C_FIELD(temp_a0, s8 *, 4), (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0, /* extra? */ 0);
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
}
