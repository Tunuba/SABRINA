#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800831F8[];

u8 func_80012040(s32 arg0) {
    return D_800831F8[arg0];
}
