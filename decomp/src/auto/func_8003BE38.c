#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003BE38(void *arg0) {
    s16 temp_s2;
    s16 temp_v0;
    s16 var_s0;
    s32 temp_s3;
    s32 temp_s5;
    void *temp_s4;
    void *temp_v1;

    temp_s4 = arg0 + 0x74;
    temp_s5 = (s32) -M2C_FIELD(arg0, s32 *, 0x3C) >> 1;
    temp_v0 = M2C_FIELD(temp_s4, s16 *, 0xC);
    if (temp_v0 & 8) {
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(temp_s4, s32 *, 0x14);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(temp_s4, s32 *, 0x18);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_s4, s32 *, 0x1C);
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) M2C_FIELD(temp_s4, s16 *, 0x20);
        M2C_FIELD(arg0, s16 *, 0x30) = 0;
        if (temp_v0 & 0x100) {
            temp_v1 = M2C_FIELD(arg0, void **, 0x60);
            M2C_FIELD(temp_v1, u8 *, 0x64) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x64) | 1);
            M2C_FIELD(arg0, s32 *, 0x54) = 1;
            M2C_FIELD(arg0, s32 *, 0x58) = 1;
            M2C_FIELD(arg0, s32 *, 0x5C) = 1;
        }
        M2C_FIELD(arg0, s16 *, 0x70) = 1;
        return;
    }
    var_s0 = 0;
loop_6:
    if (var_s0 < 0xA) {
        temp_s2 = func_80021CE4(0x190) - 0xC8;
        temp_s3 = temp_s5 - func_80021CE4(0xCCC);
        CrearParticula((s32) M2C_FIELD(temp_s4, s8 *, 0x12), (s32) arg0, (s32) temp_s2, 0, /* extra? */ 0, /* extra? */ 0x28F, /* extra? */ 0, /* extra? */ temp_s3, /* extra? */ func_80021CE4(0xCCC), /* extra? */ 0, /* extra? */ 0x51E, /* extra? */ 0, /* extra? */ 0x32, /* extra? */ 0x10, /* extra? */ 0);
        var_s0 += 1;
        goto loop_6;
    }
    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
}
