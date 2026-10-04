#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80039D4C(s32 arg0, s32 arg1) {
    return ((s32) ((M2C_FIELD(arg1, s32 *, 0x10) - M2C_FIELD(arg0, s32 *, 4)) | (M2C_FIELD(arg0, s32 *, 0x10) - M2C_FIELD(arg1, s32 *, 4)) | (M2C_FIELD(arg1, s32 *, 0x14) - M2C_FIELD(arg0, s32 *, 8)) | (M2C_FIELD(arg0, s32 *, 0x14) - M2C_FIELD(arg1, s32 *, 8)) | (M2C_FIELD(arg1, s32 *, 0x18) - M2C_FIELD(arg0, s32 *, 0xC)) | (M2C_FIELD(arg0, s32 *, 0x18) - M2C_FIELD(arg1, s32 *, 0xC))) >> 0x1F) == 0;
}
