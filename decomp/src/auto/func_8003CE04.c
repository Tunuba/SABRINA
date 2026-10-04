#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003CE04(void *arg0) {
    s16 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + 0x74;
    temp_v0 = M2C_FIELD(temp_s0, s16 *, 0x22);
    if (temp_v0 > 0) {
        M2C_FIELD(temp_s0, s16 *, 0x22) = (s16) (temp_v0 - 1);
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (M2C_FIELD(arg0, s32 *, 0x3C) + 0x51E);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
        M2C_FIELD(CrearParticula((s32) M2C_FIELD(temp_s0, s8 *, 0x12), (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ (s32) M2C_FIELD(temp_s0, s16 *, 0x24), /* extra? */ 0, /* extra? */ (s32) M2C_FIELD(temp_s0, s16 *, 0x20)), s32 *, 0x3C) = (s32) M2C_FIELD(temp_s0, s16 *, 0x26);
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
}
