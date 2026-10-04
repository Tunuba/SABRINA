#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C86BE[];
extern s8 nivel_actual;


void func_8004C700(s32 arg0) {
    *(arg0 + (D_800C86BE + (nivel_actual * 0x141))) = 1;
}
