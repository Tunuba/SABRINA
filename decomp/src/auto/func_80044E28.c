#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80044E28(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xA0) = arg1;
}
