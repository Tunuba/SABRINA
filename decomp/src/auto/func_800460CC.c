#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];
extern s8 nivel_actual;


void func_800460CC(void *arg0) {
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
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0xFFFF2667;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0xD999;
        M2C_FIELD(temp_s0, s8 *, 0x27) = 0x10;
        M2C_FIELD(temp_s0, s8 *, 0x28) = 0x10;
        M2C_FIELD(arg0, s8 *, 0x118) = 1;
        break;
    case 4:
    case 5:
    case 6:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0xFFFE726F;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0x9439;
        M2C_FIELD(temp_s0, s8 *, 0x27) = 0x1E;
        M2C_FIELD(temp_s0, s8 *, 0x28) = 0x22;
        M2C_FIELD(arg0, s8 *, 0x118) = 1;
        break;
    case 7:
    case 8:
    case 9:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
        M2C_FIELD(temp_s0, s8 *, 0x27) = 0xA;
        M2C_FIELD(temp_s0, s8 *, 0x28) = 0xA;
        M2C_FIELD(arg0, s8 *, 0x118) = 2;
        break;
    case 10:
    case 11:
    case 12:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0xFFFEA000;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0x953F;
        M2C_FIELD(temp_s0, s8 *, 0x27) = 0xE;
        M2C_FIELD(temp_s0, s8 *, 0x28) = 0xE;
        M2C_FIELD(arg0, s8 *, 0x118) = 1;
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
        } else if ((nivel_actual == 9) || (nivel_actual == 8) || (nivel_actual == 7)) {
            M2C_FIELD(arg0, s16 *, 0x112) = (s16) (M2C_FIELD(arg0, s16 *, 0x112) | 0x100);
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
    if ((nivel_actual == 9) || (nivel_actual == 8) || (nivel_actual == 7)) {
        M2C_FIELD(arg0, s16 *, 0x112) = (s16) (M2C_FIELD(arg0, s16 *, 0x112) | 0x100);
    }
}
