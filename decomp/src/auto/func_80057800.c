#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_80057800(void *arg0) {
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    u16 *temp_s2;
    void *temp_s0;

    temp_s2 = M2C_FIELD(arg0, u16 **, 0x64);
    temp_s0 = arg0 + 0x74;
    func_80048900();
    temp_v0 = p_sabrina->x - M2C_FIELD(temp_s0, s32 *, 0x28);
    sp2C = temp_v0;
    temp_v0_2 = p_sabrina->z - M2C_FIELD(temp_s0, s32 *, 0x30);
    sp34 = temp_v0_2;
    temp_v0_3 = temp_v0 >> 8;
    temp_v0_4 = ((s32) (temp_v0_3 * temp_v0_3) >> 8) << 8;
    sp30 = temp_v0_4;
    temp_v0_5 = temp_v0_2 >> 8;
    sp30 = temp_v0_4 + (((s32) (temp_v0_5 * temp_v0_5) >> 8) << 8);
    if (sp30 < M2C_FIELD(temp_s0, s32 *, 0x34)) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    }
    if (func_800607AC((s32) arg0, (s32) (temp_s0 + 0x1C), (s32) temp_s0, /* extra? */ (s32) *temp_s2) == 8) {
        if (M2C_FIELD(temp_s0, s8 *, 4) != 0) {
            M2C_FIELD(temp_s0, s8 *, 0x21) = (s8) -M2C_FIELD(temp_s0, s8 *, 0x21);
            M2C_FIELD(arg0, s32 *, 0x74) = (s32) M2C_FIELD(temp_s0, s32 *, 0xC);
            return;
        }
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) M2C_FIELD(temp_s0, s32 *, 0xC);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(temp_s0, s32 *, 0x10);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(temp_s0, s32 *, 0x14);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_s0, s32 *, 0x18);
    }
}
