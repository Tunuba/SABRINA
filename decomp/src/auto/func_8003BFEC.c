#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6594;
extern s32 D_800C6598;
extern s32 D_800C659C;
extern s32 D_800C65A0;
extern s32 D_800C65A4;
extern s32 D_800C65A8;

void func_8003BFEC(void *arg0) {
    s16 temp_v0;
    u8 var_v0;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    temp_v0 = M2C_FIELD(temp_s1, s16 *, 0x22);
    if (temp_v0 > 0) {
        M2C_FIELD(temp_s1, s16 *, 0x22) = (s16) (temp_v0 - 1);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
        M2C_FIELD(CrearParticula((s32) M2C_FIELD(temp_s1, s8 *, 0x12), (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ (s32) M2C_FIELD(temp_s1, s16 *, 0x24), /* extra? */ 0x1000, /* extra? */ (s32) M2C_FIELD(temp_s1, s16 *, 0x20)), s32 *, 0x3C) = (s32) M2C_FIELD(temp_s1, s16 *, 0x26);
        if (M2C_FIELD(temp_s1, s16 *, 0x22) & 1) {
            D_800C6594 = M2C_FIELD(arg0, s32 *, 0x24);
            D_800C6598 = M2C_FIELD(arg0, s32 *, 0x28);
            D_800C659C = M2C_FIELD(arg0, s32 *, 0x2C);
            D_800C65A0 = M2C_FIELD(arg0, s32 *, 0x24) + (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x38) >> 8) * 0x21E) >> 8) << 8);
            D_800C65A4 = M2C_FIELD(arg0, s32 *, 0x28) + (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x3C) >> 8) * 0x21E) >> 8) << 8);
            D_800C65A8 = M2C_FIELD(arg0, s32 *, 0x2C) + (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x40) >> 8) * 0x21E) >> 8) << 8);
            func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
            if (func_8003AE84() != 0) {
                var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
                goto block_5;
            }
        }
    } else {
        var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
block_5:
        M2C_FIELD(arg0, u8 *, 0x20) = var_v0;
    }
}
