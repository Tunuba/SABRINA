#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80045FA4(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xA0) = arg1;
}
