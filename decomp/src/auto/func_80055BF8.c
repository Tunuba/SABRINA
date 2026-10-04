#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80055BF8(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x74) = arg2;
    M2C_FIELD((arg0 + 0x74), s32 *, 4) = arg1;
}
