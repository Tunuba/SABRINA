#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80084BB8[];
extern u8 D_80084C0C[];
extern s16 D_80084C20;

void func_80016E1C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4_reg) {
    u16 arg4 = (u16) arg4_reg;
    s32 temp_v0_2;
    s32 var_a0;
    u8 *temp_v0;

    var_a0 = 0;
    if ((((u32) arg2 >> 4) & 3) == 3) {
        var_a0 = 3;
    }
    func_80012B0C(var_a0);
    M2C_FIELD(D_80084BB8, s16 *, 2) = 0;
    M2C_FIELD(D_80084BB8, s16 *, 0) = 0;
    M2C_FIELD(D_80084BB8, s16 *, 0xA) = 0;
    M2C_FIELD(D_80084BB8, s16 *, 8) = 0;
    M2C_FIELD(D_80084BB8, s16 *, 6) = 0;
    M2C_FIELD(D_80084BB8, s16 *, 4) = 0;
    M2C_FIELD(D_80084BB8, s16 *, 0xC) = 0;
    M2C_FIELD(D_80084BB8, s8 *, 0xE) = (s8) arg3;
    M2C_FIELD(D_80084BB8, s8 *, 0xF) = 0;
    M2C_FIELD(D_80084BB8, s8 *, 0x10) = 0;
    func_8001315C((s32) (D_80084BB8 - 8));
    temp_v0 = D_80084C0C + 8;
    M2C_FIELD(D_80084C0C, s16 *, 0) = 0;
    M2C_FIELD(D_80084C0C, s16 *, 2) = 0;
    M2C_FIELD(D_80084C0C, s16 *, 4) = (s16) arg0;
    M2C_FIELD(D_80084C0C, s16 *, 6) = (s16) arg1;
    M2C_FIELD(D_80084C0C, s16 *, 8) = 0;
    M2C_FIELD(temp_v0, s16 *, 2) = 0;
    M2C_FIELD(temp_v0, s16 *, 4) = 0;
    M2C_FIELD(temp_v0, s16 *, 6) = 0;
    temp_v0_2 = func_80016E00();
    if (temp_v0_2 == 1) {
        M2C_FIELD(D_80084C0C, s16 *, 0xA) = 0x18;
        M2C_FIELD(D_80084C0C, s8 *, 0x12) = (s8) temp_v0_2;
    }
    M2C_FIELD(D_80084C0C, s8 *, 0x10) = (s8) (arg2 & 1);
    D_80084C20 = arg2 & 4;
    M2C_FIELD(D_80084C0C, s8 *, 0x11) = (s8) arg4;
    func_8001321C((s32) D_80084C0C);
}
