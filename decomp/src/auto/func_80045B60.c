#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;
extern s32 D_8007CBF4;


void func_80045B60(void *arg0) {
    void *temp_s0;

    M2C_FIELD(arg0, s8 *, 0x119) = 1;
    temp_s0 = arg0 + 0x74;
    M2C_FIELD(temp_s0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s8 *, 0x118) = 2;
    switch (nivel_actual) {
    case 1:
    case 2:
    case 3:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0x19999;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
        M2C_FIELD(temp_s0, s8 *, 0x23) = 9;
        M2C_FIELD(arg0, s8 *, 0x118) = 2;
        D_8007CBF4 = 0x36;
        break;
    case 4:
    case 5:
    case 6:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0x18000;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
        M2C_FIELD(temp_s0, s8 *, 0x23) = 0xB;
        M2C_FIELD(arg0, s8 *, 0x118) = 2;
        D_8007CBF4 = 0x37;
        break;
    case 7:
    case 8:
    case 9:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0xE666;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
        M2C_FIELD(temp_s0, s8 *, 0x23) = 6;
        M2C_FIELD(arg0, s8 *, 0x118) = 1;
        D_8007CBF4 = 0x37;
        M2C_FIELD(temp_s0, s32 *, 0x1C) = 0x1999;
        break;
    case 10:
    case 11:
    case 12:
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0x18000;
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
        M2C_FIELD(temp_s0, s8 *, 0x23) = 7;
        M2C_FIELD(arg0, s8 *, 0x118) = 2;
        D_8007CBF4 = 0x38;
        break;
    }
    M2C_FIELD(arg0, s8 *, 0x119) = 1;
    M2C_FIELD(temp_s0, s16 *, 0x42) = -1;
    func_8003D278((s32) arg0);
    M2C_FIELD(temp_s0, s32 *, 0x3C) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
    if ((nivel_actual == 3) || (nivel_actual == 2) || (nivel_actual == 1)) {
        M2C_FIELD(arg0, s16 *, 0x112) = (s16) (M2C_FIELD(arg0, s16 *, 0x112) | 0x100);
    }
}
