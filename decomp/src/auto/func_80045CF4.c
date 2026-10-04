#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CBF4;


void func_80045CF4(void *arg0) {
    s16 temp_v0;
    s32 temp_s2;
    u16 temp_v0_2;
    void *temp_s1;
    void *temp_s3;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s3 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s2 = M2C_FIELD(arg0, s32 *, 0x64);
    temp_s1 = arg0 + 0x74;
    switch (temp_v0) {
    case 0:
        M2C_FIELD(temp_s1, s16 *, 0x40) = 0xC;
        M2C_FIELD(arg0, s16 *, 0x70) = 1;
        return;
    case 1:
        func_80048908((s32) arg0, (s32) (temp_s1 + 0x40), (s32) (temp_s1 + 0x28), (s32) M2C_FIELD(temp_s1, s8 *, 0x20));
        return;
    case 2:
        func_80049218((s32) arg0, (s32) temp_s1, temp_s2);
        return;
    case 3:
    case 4:
        if (func_800487B0((s32) arg0, (s32) p_sabrina, 0x96) < 0x200) {
            if (M2C_FIELD(arg0, s16 *, 0x70) != 4) {
                temp_v0_2 = M2C_FIELD(temp_s2, u16 *, 8);
                if (M2C_FIELD(temp_s3, u8 *, 0x51) != temp_v0_2) {
                    M2C_FIELD(temp_s3, u8 *, 0x51) = (u8) temp_v0_2;
                    M2C_FIELD(temp_s3, s8 *, 0x50) = 0;
                    M2C_FIELD(temp_s3, s16 *, 0x4E) = 0x800;
                    M2C_FIELD(arg0, s16 *, 0x70) = 4;
                }
            }
            func_80048804((s32) arg0, (s32) M2C_FIELD(temp_s1, s8 *, 0x20), (s32) temp_s3, (s32) (s8) M2C_FIELD(temp_s2, u16 *, 0));
            return;
        }
        return;
    case 7:
        func_800498F4((s32) arg0, (s32) temp_s1, temp_s2, D_8007CBF4);
        return;
    case 8:
        func_800487B0((s32) arg0, (s32) p_sabrina, 0x96);
        if (func_8002EFD0((s32) arg0) != 0) {
            if (M2C_FIELD(temp_s1, s8 *, 0x20) & 4) {
                M2C_FIELD(arg0, s16 *, 0x70) = 0xB;
                return;
            }
            M2C_FIELD(arg0, s16 *, 0x70) = 4;
            return;
        }
        break;
    case 10:
        func_80048228((s32) arg0);
        return;
    case 11:
        func_800489C4((s32) arg0);
        func_80049388((s32) arg0, (s32) temp_s1, temp_s2, D_8007CBF4);
        return;
    case 12:
        func_8004951C((s32) arg0, (s32) temp_s1, temp_s2);
        return;
    case 6:
        func_800496E4((s32) arg0, (s32) temp_s1, temp_s2);
        return;
    default:
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        break;
    }
}
