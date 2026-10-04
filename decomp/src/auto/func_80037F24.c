#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6594;
extern s32 D_800C6598;
extern s32 D_800C659C;
extern s32 D_800C65A0;
extern s32 D_800C65A4;
extern s32 D_800C65A8;

void func_80037F24(void *arg0) {
    s32 temp_a1;
    u8 var_v0;
    void *temp_v0;

    temp_v0 = arg0 + 0x74;
    if (M2C_FIELD(temp_v0, s8 *, 5) == 0) {
        temp_a1 = M2C_FIELD(arg0, s32 *, 0x54);
        if (temp_a1 < 0x1000) {
            M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_a1 + ((s32) (0x1000 - temp_a1) >> 2));
            if (M2C_FIELD(arg0, s32 *, 0x54) >= 0x1000) {
                M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
            }
            M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
            M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        }
    }
    M2C_FIELD(temp_v0, s32 *, 8) = (s32) (M2C_FIELD(temp_v0, s32 *, 8) - 1);
    if (M2C_FIELD(temp_v0, s32 *, 8) <= 0) {
        var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
        goto block_10;
    }
    M2C_FIELD(arg0, s16 *, 0x34) = (s16) (M2C_FIELD(arg0, s16 *, 0x34) + 0xF6);
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) (M2C_FIELD(arg0, s16 *, 0x30) + 0xEA);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
    if (M2C_FIELD(temp_v0, s32 *, 8) & 1) {
        D_800C6594 = M2C_FIELD(arg0, s32 *, 0x24);
        D_800C6598 = M2C_FIELD(arg0, s32 *, 0x28);
        D_800C659C = M2C_FIELD(arg0, s32 *, 0x2C);
        D_800C65A0 = M2C_FIELD(arg0, s32 *, 0x24) + (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x38) >> 8) * 0x21E) >> 8) << 8);
        D_800C65A4 = M2C_FIELD(arg0, s32 *, 0x28) + (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x3C) >> 8) * 0x21E) >> 8) << 8);
        D_800C65A8 = M2C_FIELD(arg0, s32 *, 0x2C) + (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x40) >> 8) * 0x21E) >> 8) << 8);
        func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
        if (func_8003AE84() != 0) {
            var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
block_10:
            M2C_FIELD(arg0, u8 *, 0x20) = var_v0;
        }
    }
}
