#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];
extern s8 nivel_actual;


void func_8002E21C(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    u16 *temp_s3;
    void *temp_s0;
    void *temp_s2;

    temp_s0 = arg0 + 0x74;
    temp_s3 = M2C_FIELD(arg0, u16 **, 0x64);
    M2C_FIELD(temp_s0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s8 *, 0x118) = 2;
    switch (nivel_actual) {
    case 1:
    case 2:
    case 3:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0x2C08;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0xFFFF28F6;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0x160C4;
        M2C_FIELD(temp_s0, s8 *, 0x27) = 0xE;
        M2C_FIELD(temp_s0, s8 *, 0x28) = 0xE;
        M2C_FIELD(arg0, s8 *, 0x118) = 1;
        break;
    case 4:
    case 5:
    case 6:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0x43D7;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0xFFFE8F5D;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0x75C2;
        M2C_FIELD(temp_s0, s8 *, 0x27) = 9;
        M2C_FIELD(temp_s0, s8 *, 0x28) = 9;
        M2C_FIELD(arg0, s8 *, 0x118) = 1;
        break;
    case 7:
    case 8:
    case 9:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0xFFFF2419;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0xC418;
        M2C_FIELD(temp_s0, s8 *, 0x27) = 0xF;
        M2C_FIELD(temp_s0, s8 *, 0x28) = 0xF;
        M2C_FIELD(arg0, s8 *, 0x118) = 1;
        break;
    case 10:
    case 11:
    case 12:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0x4106;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0xFFFE845B;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0xC7EF;
        M2C_FIELD(temp_s0, s8 *, 0x27) = 0xD;
        M2C_FIELD(temp_s0, s8 *, 0x28) = 0xD;
        M2C_FIELD(arg0, s8 *, 0x118) = 2;
        break;
    }
    M2C_FIELD(arg0, s8 *, 0x119) = 1;
    M2C_FIELD(temp_s0, s16 *, 0x44) = 0;
    if ((s16) M2C_FIELD(arg0, s32 *, 0x74) > 0) {
        M2C_FIELD(temp_s0, s32 *, 0x30) = 0x1999;
        M2C_FIELD((temp_s0 + 0x30), s8 *, 5) = 0;
        M2C_FIELD(arg0, s16 *, 0x70) = 2;
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) (D_800D588C + ((s16) M2C_FIELD(arg0, s32 *, 0x74) * 0x18));
        M2C_FIELD(temp_s0, s8 *, 0x24) = (s8) (M2C_FIELD(temp_s0, s8 *, 0x24) | 1);
        func_80048164((s32) arg0, M2C_FIELD(arg0, s32 *, 0x74));
        if (M2C_FIELD(arg0, s16 *, 0x70) == 0xB) {
            M2C_FIELD(temp_s0, s8 *, 0x24) = 4;
        }
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 0);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 8);
    } else {
        M2C_FIELD(temp_s0, s8 *, 0x24) = (s8) (M2C_FIELD(temp_s0, s8 *, 0x24) & ~1);
        M2C_FIELD(arg0, s16 *, 0x70) = 0xC;
    }
    if (func_8002ECFC((s32) arg0) != 0) {
        temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s2, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
        M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) *temp_s3;
        M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
        M2C_FIELD(temp_s2, u8 *, 0x53) = (u8) M2C_FIELD(temp_s2, u8 *, 0x51);
        M2C_FIELD(temp_s2, u8 *, 0x52) = (u8) M2C_FIELD(temp_s2, u8 *, 0x50);
        M2C_FIELD(temp_s2, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
    }
    M2C_FIELD(temp_s0, s32 *, 0x38) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(temp_s0, s32 *, 0x3C) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(temp_s0, s32 *, 0x40) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
    temp_v0 = (s32) M2C_FIELD(temp_s0, s32 *, 8) >> 8;
    M2C_FIELD(temp_s0, s32 *, 8) = (s32) (((s32) (temp_v0 * temp_v0) >> 8) << 8);
    temp_v0_2 = (s32) M2C_FIELD(temp_s0, s32 *, 4) >> 8;
    M2C_FIELD(temp_s0, s32 *, 4) = (s32) (((s32) (temp_v0_2 * temp_v0_2) >> 8) << 8);
}
