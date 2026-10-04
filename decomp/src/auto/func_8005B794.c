#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005B794(void *arg0) {
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0;
    s32 var_s1;

    if (M2C_FIELD(arg0, s32 *, 0x74) < 0) {
        var_s1 = 0;
loop_5:
        if (var_s1 < 0xD) {
            temp_s3 = func_80021CE4(0x3333) - 0x1999;
            temp_s2 = func_80021CE4(0x3333) - 0x1999;
            temp_v0 = CrearParticula(3, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ temp_s3, /* extra? */ temp_s2, /* extra? */ (func_80021CE4(0x3333) - 0x1999), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0, /* extra? */ 0);
            if (temp_v0 != 0) {
                M2C_FIELD(temp_v0, s32 *, 0x3C) = 0x112;
            }
            var_s1 += 1;
            goto loop_5;
        }
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
    }
    M2C_FIELD(arg0, s32 *, 0x74) = (s32) (M2C_FIELD(arg0, s32 *, 0x74) - 1);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) (M2C_FIELD(arg0, s16 *, 0x30) + 0x100);
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) (M2C_FIELD(arg0, s16 *, 0x30) & 0xFFF);
}
