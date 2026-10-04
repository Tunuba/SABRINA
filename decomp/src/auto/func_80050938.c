#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D52C0[];

void func_80050938(void) {
    M2C_FIELD(D_800D52C0, s32 *, 0xC) = 0;
    M2C_FIELD(D_800D52C0, s32 *, 0x44) = 0;
    UserFuncInit();
    M2C_FIELD(D_800D52C0, s32 *, 0) = 0;
    M2C_FIELD(D_800D52C0, s32 *, 4) = 0;
    M2C_FIELD(D_800D52C0, s32 *, 8) = 0;
    M2C_FIELD(D_800D52C0, s32 *, 0x54) = 0;
    M2C_FIELD(D_800D52C0, s32 *, 0x14) = -1;
    M2C_FIELD(D_800D52C0, s32 *, 0x4C) = 1;
    M2C_FIELD(D_800D52C0, s32 *, 0x48) = 1;
    M2C_FIELD(D_800D52C0, s32 *, 0x50) = (s32) M2C_FIELD(D_800D52C0, s32 *, 0x54);
    func_80051A84();
    func_800169D4();
}
