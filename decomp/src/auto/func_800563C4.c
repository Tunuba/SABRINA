#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;


void func_800563C4(void *arg0) {
    s32 var_v0;
    void *temp_s0;

    temp_s0 = arg0 + 0x74;
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (((s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x2C)) >> 8) & 0xFFF);
    M2C_FIELD(temp_s0, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    switch (nivel_actual) {
    case 1:
    case 2:
    case 3:
        var_v0 = CrearParticula(0x19, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
block_6:
        M2C_FIELD(temp_s0, s32 *, 0xC) = var_v0;
        break;
    case 4:
    case 5:
    case 6:
        var_v0 = CrearParticula(0x1C, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
        goto block_6;
    case 7:
    case 8:
    case 9:
        var_v0 = CrearParticula(0x1B, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
        goto block_6;
    case 10:
    case 11:
    case 12:
        var_v0 = CrearParticula(0x1A, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
        goto block_6;
    }
}
