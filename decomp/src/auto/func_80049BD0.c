#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_80049BD0(void *arg0, void *arg1, void *arg2) {
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v1;
    u16 temp_v0_2;
    u16 temp_v0_4;
    void *temp_s2;

    temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
    if ((M2C_FIELD(arg0, s32 *, 0x24) != M2C_FIELD(arg1, s32 *, 0x38)) && (M2C_FIELD(arg0, s32 *, 0x2C) != M2C_FIELD(arg1, s32 *, 0x40))) {
        temp_v1 = p_sabrina->y;
        temp_v0 = p_sabrina->z;
        sp34 = p_sabrina->x;
        sp38 = temp_v1;
        sp3C = temp_v0;
        p_sabrina->x = M2C_FIELD(arg1, s32 *, 0x38);
        p_sabrina->z = M2C_FIELD(arg1, s32 *, 0x40);
        func_800487B0((s32) arg0, (s32) p_sabrina, 0x96);
        p_sabrina->x = sp34;
        p_sabrina->y = temp_v1;
        p_sabrina->z = temp_v0;
        temp_v0_2 = M2C_FIELD(arg2, u16 *, 2);
        if (M2C_FIELD(temp_s2, u8 *, 0x51) != temp_v0_2) {
            M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) temp_v0_2;
            M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
        }
        sp28 = M2C_FIELD(arg0, s32 *, 0x24) - M2C_FIELD(arg1, s32 *, 0x38);
        sp30 = M2C_FIELD(arg0, s32 *, 0x2C) - M2C_FIELD(arg1, s32 *, 0x40);
        sp2C = 0;
        if (func_8001C180((s32) &sp28) < 0x4C) {
            M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
            M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
            return;
        }
        func_8001C45C((s32) &sp28);
        temp_v0_3 = ((s32) ((sp28 >> 4) * ((s32) M2C_FIELD(arg1, s32 *, 0x20) >> 8)) >> 8) << 8;
        sp28 = temp_v0_3;
        sp30 = ((s32) ((sp30 >> 4) * ((s32) M2C_FIELD(arg1, s32 *, 0x20) >> 8)) >> 8) << 8;
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) - temp_v0_3);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) - sp30);
        return;
    }
    temp_v0_4 = M2C_FIELD(arg2, u16 *, 0);
    if (M2C_FIELD(temp_s2, u8 *, 0x53) != temp_v0_4) {
        if (M2C_FIELD(temp_s2, u8 *, 0x51) != temp_v0_4) {
            M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) temp_v0_4;
            M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
            goto block_11;
        }
    } else {
block_11:
        M2C_FIELD(arg0, s16 *, 0x70) = 0xC;
    }
}
