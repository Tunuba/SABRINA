#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_8004951C(void *arg0, void *arg1, void *arg2) {
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_s2_2;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v0_4;
    u16 temp_v0_2;
    void *temp_s2;

    temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
    func_800487B0((s32) arg0, (s32) p_sabrina, 0x96);
    sp2C = M2C_FIELD(arg0, s32 *, 0x24) - p_sabrina->x;
    sp30 = 0;
    sp34 = M2C_FIELD(arg0, s32 *, 0x2C) - p_sabrina->z;
    temp_v0 = func_8001C180((s32) &sp2C);
    if (temp_v0 < 0x80) {
        M2C_FIELD(arg0, s16 *, 0x70) = 7;
        M2C_FIELD(arg1, s8 *, 0x24) = 0xC;
        M2C_FIELD(arg1, s16 *, 0x42) = 0;
        return;
    }
    if (temp_v0 < ((s32) M2C_FIELD(arg1, s32 *, 8) >> 8)) {
        temp_v0_2 = M2C_FIELD(arg2, u16 *, 2);
        if (M2C_FIELD(temp_s2, u8 *, 0x51) != temp_v0_2) {
            M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) temp_v0_2;
            M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
        }
        func_8001C45C((s32) &sp2C);
        temp_v0_3 = ((s32) ((sp2C >> 4) * ((s32) M2C_FIELD(arg1, s32 *, 0x1C) >> 8)) >> 8) << 8;
        sp2C = temp_v0_3;
        temp_v0_4 = ((s32) ((sp34 >> 4) * ((s32) M2C_FIELD(arg1, s32 *, 0x1C) >> 8)) >> 8) << 8;
        sp34 = temp_v0_4;
        temp_s3 = M2C_FIELD(arg0, s32 *, 0x24) - temp_v0_3;
        temp_s2_2 = M2C_FIELD(arg0, s32 *, 0x2C) - temp_v0_4;
        sp2C = M2C_FIELD(arg1, s32 *, 0x34) - temp_s3;
        sp34 = M2C_FIELD(arg1, s32 *, 0x3C) - temp_s2_2;
        if (func_8001C180((s32) &sp2C) < ((s32) M2C_FIELD(arg1, s32 *, 8) >> 8)) {
            M2C_FIELD(arg0, s32 *, 0x24) = temp_s3;
            M2C_FIELD(arg0, s32 *, 0x2C) = temp_s2_2;
            return;
        }
        M2C_FIELD(arg0, s16 *, 0x70) = 6;
        goto block_9;
    }
    M2C_FIELD(arg0, s16 *, 0x70) = 6;
block_9:
    M2C_FIELD(arg1, s8 *, 0x24) = 0xC;
}
