#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8001C280(s32 arg0, s32 arg1) {
    return (s32) ((u32) ((M2C_FIELD(arg0, s32 *, 0) * M2C_FIELD(arg1, s32 *, 0)) + (M2C_FIELD(arg0, s32 *, 4) * M2C_FIELD(arg1, s32 *, 4)) + (M2C_FIELD(arg0, s32 *, 8) * M2C_FIELD(arg1, s32 *, 8))) >> 0xC);
}
