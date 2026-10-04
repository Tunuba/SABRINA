#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003C528(s32 arg0) {
    s16 temp_v0_2;
    s16 var_v1;
    s32 temp_v0;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    if (M2C_FIELD(temp_s1, s32 *, 0x28) == 0) {
        M2C_FIELD(temp_s1, s32 *, 0x28) = CrearParticula((s32) M2C_FIELD(temp_s1, s8 *, 0x12), arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ (s32) M2C_FIELD(temp_s1, s16 *, 0x24), /* extra? */ 0x1000, /* extra? */ (s32) M2C_FIELD(temp_s1, s16 *, 0x20));
        temp_v0 = M2C_FIELD(temp_s1, s32 *, 0x28);
        if (temp_v0 != 0) {
            M2C_FIELD(temp_v0, s32 *, 0x3C) = 0;
        }
    }
    temp_v0_2 = M2C_FIELD(temp_s1, s16 *, 0x22);
    if (temp_v0_2 > 0) {
        M2C_FIELD(temp_s1, s16 *, 0x22) = (s16) (temp_v0_2 - 1);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x28), s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x28), s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x28), s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
        var_v1 = 0xA;
    } else {
        var_v1 = 1;
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
    }
    M2C_FIELD((void *) M2C_FIELD(temp_s1, s32 *, 0x28), s16 *, 0x40) = var_v1;
}
