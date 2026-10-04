#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;
extern s32 D_8007CBD8;


void func_8003D478(void *arg0) {
    void *temp_v0;

    M2C_FIELD(arg0, s8 *, 0x119) = 1;
    temp_v0 = arg0 + 0x74;
    M2C_FIELD(temp_v0, s32 *, 0x28) = 0;
    M2C_FIELD(temp_v0, s8 *, 0x23) = 0xA;
    M2C_FIELD(arg0, s8 *, 0x118) = 2;
    switch (nivel_actual) {
    case 1:
    case 2:
    case 3:
        M2C_FIELD(temp_v0, s32 *, 0xC) = 0x1E666;
        M2C_FIELD(temp_v0, s32 *, 0x10) = 0;
        M2C_FIELD(temp_v0, s32 *, 0x14) = 0;
        M2C_FIELD(temp_v0, s8 *, 0x23) = 0xA;
        M2C_FIELD(arg0, s8 *, 0x118) = 2;
        D_8007CBD8 = 0x35;
        break;
    case 4:
    case 5:
    case 6:
        M2C_FIELD(temp_v0, s32 *, 0xC) = 0x19999;
        M2C_FIELD(temp_v0, s32 *, 0x10) = 0;
        M2C_FIELD(temp_v0, s32 *, 0x14) = 0;
        M2C_FIELD(temp_v0, s8 *, 0x23) = 0xD;
        M2C_FIELD(arg0, s8 *, 0x118) = 2;
        D_8007CBD8 = 0x35;
        break;
    case 7:
    case 8:
    case 9:
        M2C_FIELD(temp_v0, s32 *, 0xC) = 0x18F9D;
        M2C_FIELD(temp_v0, s32 *, 0x10) = 0;
        M2C_FIELD(temp_v0, s32 *, 0x14) = 0;
        M2C_FIELD(temp_v0, s8 *, 0x23) = 8;
        M2C_FIELD(arg0, s8 *, 0x118) = 2;
        D_8007CBD8 = 0x2D;
        break;
    case 10:
    case 11:
    case 12:
        M2C_FIELD(temp_v0, s32 *, 0xC) = 0x13333;
        M2C_FIELD(temp_v0, s32 *, 0x10) = 0;
        M2C_FIELD(temp_v0, s32 *, 0x14) = 0;
        M2C_FIELD(temp_v0, s8 *, 0x23) = 8;
        M2C_FIELD(arg0, s8 *, 0x118) = 1;
        D_8007CBD8 = 0x35;
        break;
    }
    M2C_FIELD(arg0, s8 *, 0x119) = 1;
    func_8003D278((s32) arg0);
    if ((nivel_actual == 3) || (nivel_actual == 2) || (nivel_actual == 1)) {
        M2C_FIELD(arg0, s16 *, 0x112) = (s16) (M2C_FIELD(arg0, s16 *, 0x112) | 0x100);
    }
}
