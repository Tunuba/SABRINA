#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 partida;


void func_8004AB24(void *arg0) {
    s32 temp_s1;
    s32 temp_s2;
    s32 var_s1;

    M2C_FIELD(arg0, s32 *, 0x38) = (s32) ((s32) (p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24)) >> 3);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) ((s32) (p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C)) >> 3);
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) ((s32) (((p_sabrina->y - 0x4001) - 0x7FFF) - M2C_FIELD(arg0, s32 *, 0x28)) >> 3);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x38) >> 8) * 0x2CC) >> 8) << 8);
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x3C) >> 8) * 0x2CC) >> 8) << 8);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x40) >> 8) * 0x2CC) >> 8) << 8);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
    temp_s2 = ((func_80014F10() & 0x3F) - 0x20) << 8;
    temp_s1 = ((func_80014F10() & 0x3F) - 0x20) << 8;
    CrearParticula(0, (s32) arg0, 0, temp_s2, /* extra? */ temp_s1, /* extra? */ (((func_80014F10() & 0x3F) - 0x20) << 8), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 7, /* extra? */ 2, /* extra? */ 0);
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x2D);
    if (func_8002225C((s32) arg0, p_sabrina->x, (p_sabrina->y - 0x4001) - 0x7FFF, p_sabrina->z) < 0x6666) {
        var_s1 = 0;
        partida += 1;
loop_3:
        if (var_s1 < 0x14) {
            CrearParticula(0, (s32) arg0, (s32) func_80021CE4(0x1000), 0, /* extra? */ 0, /* extra? */ 0x4000, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x4CCC, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0);
            var_s1 += 1;
            goto loop_3;
        }
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
    }
}
