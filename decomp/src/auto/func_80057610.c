#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];
extern s8 nivel_actual;


void func_80057610(void *arg0) {
    s32 temp_s0;
    u16 *temp_s3;
    void *temp_s1;

    temp_s0 = arg0 + 0x74;
    M2C_FIELD(arg0, s32 *, 0x74) = (s32) (D_800D588C + ((s16) M2C_FIELD(arg0, s32 *, 0x74) * 0x18));
    func_80048104(temp_s0);
    M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x74);
    func_800573C0(M2C_FIELD(arg0, s32 *, 0x74), temp_s0 + 0x28, temp_s0 + 0x34);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 8);
    temp_s3 = M2C_FIELD(arg0, u16 **, 0x64);
    if (func_8002ECFC((s32) arg0) != 0) {
        temp_s1 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s1, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
        M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) *temp_s3;
        M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
        M2C_FIELD(temp_s1, u8 *, 0x53) = (u8) M2C_FIELD(temp_s1, u8 *, 0x51);
        M2C_FIELD(temp_s1, u8 *, 0x52) = (u8) M2C_FIELD(temp_s1, u8 *, 0x50);
        M2C_FIELD(temp_s1, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
    }
    M2C_FIELD(temp_s0, s32 *, 0x1C) = 0x3333;
    M2C_FIELD(temp_s0, s8 *, 0x21) = 1;
    M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(temp_s0, s32 *, 0x18) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
    M2C_FIELD(temp_s0, s16 *, 0x24) = -1;
    switch (nivel_actual) {
    case 1:
    case 2:
    case 3:
    case 7:
    case 8:
    case 9:
        if (M2C_FIELD(arg0, u16 *, 0x22) == 0x2E) {
            M2C_FIELD(temp_s0, s16 *, 0x24) = TocarSonido(0x32, 0, 0x2A, 0x7F);
        }
        break;
    case 10:
    case 11:
    case 12:
        if (M2C_FIELD(arg0, u16 *, 0x22) == 0x2E) {
            M2C_FIELD(temp_s0, s16 *, 0x24) = TocarSonido(0x40, 0, 0x2A, 0x7F);
        } else {
            M2C_FIELD(temp_s0, s16 *, 0x24) = TocarSonido(0x32, 0, 0x2A, 0x7F);
        }
        break;
    }
    M2C_FIELD(arg0, s8 *, 0x119) = 1;
}
