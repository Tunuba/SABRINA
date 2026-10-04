#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D53A0;
extern s32 D_800D53A4;
extern s32 D_800D53A8;
extern s32 D_800D53AC;

s32 func_80052008(void) {
    return D_800D53A0 + (D_800D53A4 * 2) + (D_800D53A8 * 4) + (D_800D53AC * 8);
}
