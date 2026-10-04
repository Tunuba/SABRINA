#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];

void func_8003D278(s32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    u16 *temp_s3;
    void *temp_s0;
    void *temp_s2;

    temp_s0 = arg0 + 0x74;
    temp_s3 = M2C_FIELD(arg0, u16 **, 0x64);
    M2C_FIELD(temp_s0, s16 *, 0x42) = -1;
    if ((s16) M2C_FIELD(arg0, s32 *, 0x74) > 0) {
        M2C_FIELD(temp_s0, s32 *, 0x2C) = 0x4CCC;
        M2C_FIELD((temp_s0 + 0x2C), s8 *, 5) = 0;
        M2C_FIELD(temp_s0, s8 *, 0x20) = (s8) (M2C_FIELD(temp_s0, s8 *, 0x20) | 1);
        M2C_FIELD(arg0, s16 *, 0x70) = 2;
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) (D_800D588C + ((s16) M2C_FIELD(arg0, s32 *, 0x74) * 0x18));
        func_80048164(arg0, M2C_FIELD(arg0, s32 *, 0x74));
        if (M2C_FIELD(arg0, s16 *, 0x70) == 0xB) {
            M2C_FIELD(temp_s0, s8 *, 0x20) = 4;
        }
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 0);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 8);
    } else {
        M2C_FIELD(temp_s0, s8 *, 0x20) = (s8) (M2C_FIELD(temp_s0, s8 *, 0x20) & ~1);
        M2C_FIELD(arg0, s16 *, 0x70) = 0xC;
    }
    if (func_8002ECFC(arg0) != 0) {
        temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s2, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
        M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) *temp_s3;
        M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
        M2C_FIELD(temp_s2, u8 *, 0x53) = (u8) M2C_FIELD(temp_s2, u8 *, 0x51);
        M2C_FIELD(temp_s2, u8 *, 0x52) = (u8) M2C_FIELD(temp_s2, u8 *, 0x50);
        M2C_FIELD(temp_s2, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
    }
    M2C_FIELD(temp_s0, s16 *, 0x42) = 0;
    func_800483F8(arg0);
    M2C_FIELD(temp_s0, s32 *, 0x34) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(temp_s0, s32 *, 0x38) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(temp_s0, s32 *, 0x3C) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
    temp_v0 = (s32) M2C_FIELD(temp_s0, s32 *, 8) >> 8;
    M2C_FIELD(temp_s0, s32 *, 8) = (s32) (((s32) (temp_v0 * temp_v0) >> 8) << 8);
    temp_v0_2 = (s32) M2C_FIELD(temp_s0, s32 *, 4) >> 8;
    M2C_FIELD(temp_s0, s32 *, 4) = (s32) (((s32) (temp_v0_2 * temp_v0_2) >> 8) << 8);
}
