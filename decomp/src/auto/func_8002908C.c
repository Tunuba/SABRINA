#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800913F8;
extern s32 D_800913FC;

void func_8002908C(s32 arg0) {
    D_800913F8 = arg0;
    D_800913FC = (s32) *(u16 *)0x1F801120;
}
