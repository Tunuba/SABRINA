#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80048228(void *arg0) {
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v1;

    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) - 0x9C4);
    temp_s2 = func_80021CE4(0x1000);
    temp_s3 = func_80021CE4(0x1000);
    temp_s1 = (s32) (rsin(temp_s2) * 0xC000) >> 0xC;
    temp_v1 = (s32) (rcos(temp_s2) * 0xC000) >> 0xC;
    CrearParticula(0x11, (s32) arg0, (s32) (s16) temp_s3, 0, /* extra? */ (temp_s1 - 0x5999), /* extra? */ temp_v1, /* extra? */ 0, /* extra? */ ((s32) -temp_s1 >> 5), /* extra? */ ((s32) -temp_v1 >> 5), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xA, /* extra? */ 0x202, /* extra? */ 0);
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x54);
    if (temp_v0 <= 0) {
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        M2C_FIELD(arg0, s32 *, 0x54) = 5;
        M2C_FIELD(arg0, s32 *, 0x58) = 5;
        M2C_FIELD(arg0, s32 *, 0x5C) = 5;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v0 - 0x36);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) - 0x36);
    M2C_FIELD(arg0, s32 *, 0x5C) = (s32) (M2C_FIELD(arg0, s32 *, 0x5C) - 0x36);
}
