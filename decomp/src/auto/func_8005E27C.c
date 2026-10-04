#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005E27C(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s16 *, 0) = (s16) arg0;
    M2C_FIELD(arg2, s16 *, 2) = (s16) arg1;
}
