#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800909DC[];
extern s32 func_800259A8();
extern s32 func_80025A10();

void func_80025DA8(void) {
    M2C_FIELD(D_800909DC, s32 (**)(), 0) = func_80025A10;
    M2C_FIELD(D_800909DC, s32 (**)(), 4) = func_800259A8;
    M2C_FIELD(D_800909DC, s32 *, -4) = 0;
    M2C_FIELD(D_800909DC, s32 *, 8) = 0;
}
