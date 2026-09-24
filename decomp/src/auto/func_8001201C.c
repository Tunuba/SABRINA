#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800831F8[];
extern u32 * D_80063754;


void func_8001201C(u32 arg0) {
    *D_80063754 = arg0;
    D_800831F8[arg0 >> 0x18] = (u8) arg0;
}
