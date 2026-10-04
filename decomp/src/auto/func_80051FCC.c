#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D5390;
extern s32 D_800D5394;
extern s32 D_800D5398;
extern s32 D_800D539C;

s32 func_80051FCC(void) {
    return D_800D5390 + (D_800D5394 * 2) + (D_800D5398 * 4) + (D_800D539C * 8);
}
