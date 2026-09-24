#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8001FD28(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(M2C_FIELD(arg1, void **, 0), s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) M2C_FIELD(M2C_FIELD(arg1, void **, 4), s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(M2C_FIELD(arg1, void **, 8), s32 *, 8);
}
