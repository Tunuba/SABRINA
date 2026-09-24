#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8001C304(s32 arg0, s32 arg1) {
    return ((u32) (arg0 * arg1) >> 0x10) | (MULT_HI(arg0, arg1) << 0x10);
}
