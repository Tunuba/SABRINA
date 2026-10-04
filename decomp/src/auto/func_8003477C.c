#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];
extern u8 D_800D5890[];
extern u8 D_800D5894[];
extern s32 D_8007CBA8;


void func_8003477C(s32 arg0) {
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    void *temp_s0;
    void *temp_s2;

    temp_s0 = arg0 + 0x74;
    M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x14) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x15) = 0;
    D_8007CBA8 = 0;
    if (func_8002ECFC(arg0) != 0) {
        temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s2, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
        M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) *M2C_FIELD(arg0, u16 **, 0x64);
        M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
        M2C_FIELD(temp_s2, u8 *, 0x53) = (u8) M2C_FIELD(temp_s2, u8 *, 0x51);
        M2C_FIELD(temp_s2, u8 *, 0x52) = (u8) M2C_FIELD(temp_s2, u8 *, 0x50);
        M2C_FIELD(temp_s2, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
    }
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x74);
    if (temp_v0 != 0) {
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) (D_800D588C + (temp_v0 * 0x18));
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 0);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 8);
        temp_v0_2 = M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s16 *, 0xE) * 0x18;
        temp_a0 = *(D_800D588C + temp_v0_2);
        temp_a1 = *(D_800D5890 + temp_v0_2);
        temp_a2 = *(D_800D5894 + temp_v0_2);
        M2C_FIELD(arg0, s32 *, 0x54) = 5;
        M2C_FIELD(arg0, s32 *, 0x58) = 5;
        M2C_FIELD(arg0, s32 *, 0x5C) = 5;
        M2C_FIELD(temp_s0, s32 *, 0x18) = (s32) ((s32) (temp_a0 - M2C_FIELD(arg0, s32 *, 0x24)) >> 4);
        M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) ((s32) (temp_a1 - M2C_FIELD(arg0, s32 *, 0x28)) >> 4);
        M2C_FIELD(temp_s0, s32 *, 0x20) = (s32) ((s32) (temp_a2 - M2C_FIELD(arg0, s32 *, 0x2C)) >> 4);
        M2C_FIELD(temp_s0, s32 *, 0x24) = (s32) (temp_a0 - M2C_FIELD(arg0, s32 *, 0x24));
        M2C_FIELD(temp_s0, s32 *, 0x28) = (s32) (temp_a1 - M2C_FIELD(arg0, s32 *, 0x28));
        M2C_FIELD(temp_s0, s32 *, 0x2C) = (s32) (temp_a2 - M2C_FIELD(arg0, s32 *, 0x2C));
        func_8001C45C((s32) (temp_s0 + 0x24));
        M2C_FIELD(temp_s0, s16 *, 0xE) = 0x10;
    } else {
        sp24 = M2C_FIELD(arg0, s32 *, 0x24);
        sp28 = (M2C_FIELD(arg0, s32 *, 0x28) - 0x6667) - 0x7FFF;
        sp2C = M2C_FIELD(arg0, s32 *, 0x2C);
        temp_v0_3 = func_800223E8((s32) &sp24);
        sp28 = temp_v0_3;
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) ((temp_v0_3 - 0x3334) - 0x7FFF);
        M2C_FIELD(temp_s0, s32 *, 0x18) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x1C) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x20) = 0;
        M2C_FIELD(temp_s0, s16 *, 0xE) = 1;
        M2C_FIELD(temp_s0, s32 *, 0x24) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x28) = 0x1000;
        M2C_FIELD(temp_s0, s32 *, 0x2C) = 0;
        func_8002205C((s32) (temp_s0 + 0x24), 0, (s32) M2C_FIELD(arg0, s16 *, 0x32));
    }
    func_8001E588(arg0);
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
}
