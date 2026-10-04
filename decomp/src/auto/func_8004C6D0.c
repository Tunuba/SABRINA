#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C86B6[];
extern s8 nivel_actual;


void func_8004C6D0(s32 arg0) {
    *(arg0 + (D_800C86B6 + (nivel_actual * 0x141))) = 1;
}
