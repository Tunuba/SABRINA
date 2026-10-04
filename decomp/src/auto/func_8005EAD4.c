#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C8582;
extern s8 D_800C8583;
extern s8 D_800C8584;
extern s8 D_800C8585;
extern s8 nivel_actual;
extern u16 D_8007CBD4;


void func_8005EAD4(void *arg0) {
    s32 var_v1;
    u16 var_v0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s3;

    temp_s3 = M2C_FIELD(arg0, void **, 0x64);
    M2C_FIELD(arg0, s8 *, 0x119) = 1;
    M2C_FIELD(arg0, s8 *, 0x118) = 5;
    M2C_FIELD(arg0, s16 *, 0x70) = 8;
    temp_s1 = arg0 + 0x74;
    func_80022FD8(M2C_FIELD(arg0, s8 *, 0x118) & 0xFF, 5);
    if (func_8002ECFC((s32) arg0) != 0) {
        temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s2, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
        M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 2);
        M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
        M2C_FIELD(temp_s2, u8 *, 0x53) = (u8) M2C_FIELD(temp_s2, u8 *, 0x51);
        M2C_FIELD(temp_s2, u8 *, 0x52) = (u8) M2C_FIELD(temp_s2, u8 *, 0x50);
        M2C_FIELD(temp_s2, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
    }
    M2C_FIELD(arg0, s16 *, 0x70) = 8;
    if ((nivel_actual == 6) || (nivel_actual == 0xC) || (nivel_actual == 9) || (nivel_actual == 3)) {
        var_v1 = 5;
        M2C_FIELD(arg0, s32 *, 0x54) = 5;
        M2C_FIELD(arg0, s32 *, 0x58) = 5;
    } else {
        var_v1 = 0x1800;
        M2C_FIELD(arg0, s32 *, 0x54) = 0x1800;
        M2C_FIELD(arg0, s32 *, 0x58) = 0x1800;
    }
    M2C_FIELD(arg0, s32 *, 0x5C) = var_v1;
    func_8001E588((s32) arg0);
    switch (nivel_actual) {                         /* irregular */
    case 3:
        M2C_FIELD(temp_s1, s32 *, 0xC) = 0x8000;
        M2C_FIELD(temp_s1, s32 *, 0x10) = 0;
        M2C_FIELD(temp_s1, s32 *, 0x14) = 0x4CCC;
        M2C_FIELD(temp_s1, s8 *, 0x27) = 0x16;
        if (D_800C8582 != 0) {
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
            var_v0 = D_8007CBD4 | 0x40;
block_20:
            D_8007CBD4 = var_v0;
        }
        break;
    case 6:
        M2C_FIELD(temp_s1, s32 *, 0xC) = 0x8000;
        M2C_FIELD(temp_s1, s32 *, 0x10) = 0;
        M2C_FIELD(temp_s1, s32 *, 0x14) = 0x4CCC;
        M2C_FIELD(temp_s1, s8 *, 0x27) = 0x1E;
        if (D_800C8583 != 0) {
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
            var_v0 = D_8007CBD4 | 0x40;
            goto block_20;
        }
        break;
    case 9:
        M2C_FIELD(temp_s1, s32 *, 0xC) = 0;
        M2C_FIELD(temp_s1, s32 *, 0x10) = 0;
        M2C_FIELD(temp_s1, s32 *, 0x14) = 0x9999;
        M2C_FIELD(temp_s1, s8 *, 0x27) = 0x17;
        if (D_800C8584 != 0) {
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
            var_v0 = D_8007CBD4 | 0x40;
            goto block_20;
        }
        break;
    case 12:
        M2C_FIELD(temp_s1, s32 *, 0xC) = 0;
        M2C_FIELD(temp_s1, s32 *, 0x10) = 0;
        M2C_FIELD(temp_s1, s32 *, 0x14) = 0x4CCC;
        M2C_FIELD(temp_s1, s8 *, 0x27) = 0x27;
        if (D_800C8585 != 0) {
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
            var_v0 = D_8007CBD4 | 0x40;
            goto block_20;
        }
        break;
    }
}
