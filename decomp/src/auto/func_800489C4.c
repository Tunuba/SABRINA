#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];


void func_800489C4(s32 arg0) {
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 var_v1;
    u8 *temp_v1_2;
    void *temp_v1;

    func_800487B0(arg0, (s32) p_sabrina, 0x96);
    sp34 = (s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8;
    sp38 = (s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8;
    sp3C = (s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8;
    temp_v1 = M2C_FIELD(arg0, void **, 0x74);
    sp1C = (s32) M2C_FIELD(temp_v1, s32 *, 0) >> 8;
    sp20 = (s32) M2C_FIELD(temp_v1, s32 *, 4) >> 8;
    sp24 = (s32) M2C_FIELD(temp_v1, s32 *, 8) >> 8;
    temp_v0 = M2C_FIELD(temp_v1, s16 *, 0xE);
    if (temp_v0 != 0) {
        var_v1 = temp_v0 * 0x18;
    } else {
        var_v1 = M2C_FIELD(temp_v1, s16 *, 0x10) * 0x18;
    }
    temp_v1_2 = &D_800D588C[var_v1];
    temp_v0_2 = (s32) M2C_FIELD(temp_v1_2, s32 *, 0) >> 8;
    sp28 = temp_v0_2;
    temp_v0_3 = (s32) M2C_FIELD(temp_v1_2, s32 *, 4) >> 8;
    sp2C = temp_v0_3;
    temp_v0_4 = (s32) M2C_FIELD(temp_v1_2, s32 *, 8) >> 8;
    sp30 = temp_v0_4;
    sp1C -= sp34;
    temp_v0_5 = sp20 - sp38;
    sp20 = temp_v0_5;
    sp24 -= sp3C;
    sp28 = temp_v0_2 - sp34;
    sp2C = temp_v0_3 - sp38;
    sp30 = temp_v0_4 - sp3C;
    sp34 = (s32) (p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24)) >> 8;
    sp38 = (s32) (p_sabrina->y - M2C_FIELD(arg0, s32 *, 0x28)) >> 8;
    sp3C = (s32) (p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C)) >> 8;
    if ((temp_v0_5 + (sp1C + sp24)) != 0) {
        if (func_8001C1D4((s32) &sp34, (s32) &sp1C) < 0) {
            sp1C = sp28;
            sp20 = sp2C;
            goto block_8;
        }
    } else if (func_8001C1D4((s32) &sp34, (s32) &sp28) > 0) {
        sp1C = sp28;
        sp20 = sp2C;
block_8:
        sp24 = sp30;
    }
    temp_v0_6 = sp1C * 8;
    sp1C = temp_v0_6;
    temp_v0_7 = sp20 * 8;
    sp20 = temp_v0_7;
    temp_v0_8 = sp24 * 8;
    sp24 = temp_v0_8;
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + temp_v0_6);
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + temp_v0_7);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + temp_v0_8);
    sp28 = (s32) (p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24)) >> 8;
    sp2C = (s32) (p_sabrina->y - M2C_FIELD(arg0, s32 *, 0x28)) >> 8;
    sp30 = (s32) (p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C)) >> 8;
    if (func_8001C1D4((s32) &sp1C, (s32) &sp28) < 0) {
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) - sp1C);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) - sp20);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) - sp24);
    }
}
