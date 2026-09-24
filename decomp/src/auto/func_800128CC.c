#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80063780;
extern s32 D_80063784;


void func_800128CC(void) {
    D_80063780 = func_8001626C(-1) + 0xF0;
    D_80063784 = 0;
}
