#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80037DE0(void *arg0) {
    s16 temp_s1;
    s16 var_s0;
    s32 temp_s3;
    s32 temp_s5;

    temp_s5 = (s32) -M2C_FIELD(arg0, s32 *, 0x3C) >> 1;
    var_s0 = 0;
loop_2:
    if (var_s0 < 0x14) {
        temp_s1 = func_80021CE4(0x190) - 0xC8;
        temp_s3 = temp_s5 - func_80021CE4(0xCCC);
        CrearParticula((s32) M2C_FIELD((arg0 + 0x74), s8 *, 4), (s32) arg0, (s32) temp_s1, 0, /* extra? */ 0, /* extra? */ 0x28F, /* extra? */ 0, /* extra? */ temp_s3, /* extra? */ func_80021CE4(0xCCC), /* extra? */ 0, /* extra? */ 0x51E, /* extra? */ 0, /* extra? */ 0x32, /* extra? */ 0x10, /* extra? */ 0);
        var_s0 += 1;
        goto loop_2;
    }
    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
}
