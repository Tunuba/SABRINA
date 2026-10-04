#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8004E72C(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0xF0) = 0;
    M2C_FIELD(arg0, s32 *, 0xF4) = 0;
    memset(arg0 + 0xC, 0, 0xE4);
    M2C_FIELD(arg0, s32 *, 0xF8) = 0;
    M2C_FIELD(arg0, s32 *, 0xFC) = 0;
    M2C_FIELD(arg0, s8 *, 0x100) = 1;
}
