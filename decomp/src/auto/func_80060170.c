#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;


void func_80060170(void *arg0) {
    s32 temp_v0;
    s32 var_v0;
    void *temp_a0;

    temp_a0 = arg0 + 0x74;
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x74);
    if (temp_v0 < 0) {
        var_v0 = -0x28F;
        goto block_4;
    }
    if (temp_v0 > 0) {
        var_v0 = 0x51E;
block_4:
        M2C_FIELD(arg0, s32 *, 0x74) = var_v0;
    }
    switch (nivel_actual) {                         /* irregular */
    case 9:
    case 8:
    case 7:
        M2C_FIELD(arg0, s32 *, 0x74) = -0x28F;
        M2C_FIELD(temp_a0, s32 *, 4) = -1;
        M2C_FIELD(temp_a0, s32 *, 8) = 0x12;
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x3333;
        M2C_FIELD(temp_a0, s32 *, 0x10) = 0x32;
        break;
    case 3:
    case 2:
    case 1:
        M2C_FIELD(arg0, s32 *, 0x74) = 0x51E;
        M2C_FIELD(temp_a0, s32 *, 4) = 1;
        M2C_FIELD(temp_a0, s32 *, 8) = 0x12;
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x3333;
        M2C_FIELD(temp_a0, s32 *, 0x10) = 0x32;
        break;
    default:
        M2C_FIELD(arg0, s32 *, 0x74) = -0x51E;
        M2C_FIELD(temp_a0, s32 *, 4) = 1;
        M2C_FIELD(temp_a0, s32 *, 8) = 0x32;
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x3333;
        M2C_FIELD(temp_a0, s32 *, 0x10) = 0x32;
        break;
    }
    M2C_FIELD(temp_a0, s32 *, 0x14) = (s32) M2C_FIELD(temp_a0, s32 *, 0x10);
}
