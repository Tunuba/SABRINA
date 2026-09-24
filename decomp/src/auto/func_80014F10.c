#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u32 D_80084B7C;

s32 func_80014F10(void) {
    u32 temp_v0;

    temp_v0 = (D_80084B7C * 0x41C64E6D) + 0x3039;
    D_80084B7C = temp_v0;
    return (temp_v0 >> 0x10) & 0x7FFF;
}
