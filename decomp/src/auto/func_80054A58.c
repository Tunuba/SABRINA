#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C8567[];
extern s8 nivel_actual;


void func_80054A58(void *arg0) {
    s32 var_v0;
    void *temp_s0;

    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s16 *, 0x34) = 0;
    M2C_FIELD(arg0, s16 *, 0x30) = 0;
    M2C_FIELD(arg0, s16 *, 0x70) = 1;
    temp_s0 = arg0 + 0x74;
    M2C_FIELD(temp_s0, s32 *, 4) = (s32) nivel_actual;
    M2C_FIELD(arg0, s32 *, 0x54) = 5;
    M2C_FIELD(arg0, s32 *, 0x58) = 5;
    M2C_FIELD(arg0, s32 *, 0x5C) = 5;
    M2C_FIELD(temp_s0, s32 *, 8) = 0;
    switch (nivel_actual) {
    case 13:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        break;
    case 0:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        break;
    case 1:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        func_800249CC((s32) arg0, 0x1A);
        M2C_FIELD(temp_s0, s32 *, 4) = 0;
        break;
    case 2:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        func_800249CC((s32) arg0, 0x1B);
        var_v0 = 1;
block_16:
        M2C_FIELD(temp_s0, s32 *, 4) = var_v0;
        break;
    case 3:
        M2C_FIELD(temp_s0, s32 *, 8) = 1;
        func_800249CC((s32) arg0, 0x1C);
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        var_v0 = 2;
        goto block_16;
    case 4:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        func_800249CC((s32) arg0, 0x1A);
        var_v0 = 3;
        goto block_16;
    case 5:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        func_800249CC((s32) arg0, 0x1B);
        var_v0 = 4;
        goto block_16;
    case 6:
        M2C_FIELD(temp_s0, s32 *, 8) = 1;
        func_800249CC((s32) arg0, 0x1C);
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        var_v0 = 5;
        goto block_16;
    case 7:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        func_800249CC((s32) arg0, 0x1A);
        var_v0 = 6;
        goto block_16;
    case 8:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        func_800249CC((s32) arg0, 0x1B);
        var_v0 = 7;
        goto block_16;
    case 9:
        M2C_FIELD(temp_s0, s32 *, 8) = 1;
        func_800249CC((s32) arg0, 0x1C);
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        var_v0 = 8;
        goto block_16;
    case 10:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        func_800249CC((s32) arg0, 0x1A);
        var_v0 = 9;
        goto block_16;
    case 11:
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        func_800249CC((s32) arg0, 0x1B);
        var_v0 = 0xA;
        goto block_16;
    case 12:
        M2C_FIELD(temp_s0, s32 *, 8) = 1;
        func_800249CC((s32) arg0, 0x1C);
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        var_v0 = 0xB;
        goto block_16;
    }
    if ((s8) D_800C8567[M2C_FIELD(temp_s0, s32 *, 4)] != 0) {
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
    }
}
