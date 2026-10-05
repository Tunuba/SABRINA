#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D5380;
extern s32 D_800D5384;
extern s32 D_800D5388;
extern s32 D_800D538C;
extern s32 D_800D5390;
extern s32 D_800D5394;
extern s32 D_800D5398;
extern s32 D_800D539C;

s32 func_80051E1C(void) {
    s32 temp_s0;

    do {
        temp_s0 = D_800D5390 + (D_800D5394 * 2) + (D_800D5398 * 4) + (D_800D539C * 8);
    } while (temp_s0 == 0);
    TestEvent(D_800D5380);
    TestEvent(D_800D5384);
    TestEvent(D_800D5388);
    TestEvent(D_800D538C);
    D_800D539C = 0;
    D_800D5398 = D_800D539C;
    D_800D5394 = D_800D5398;
    D_800D5390 = D_800D5394;
    return temp_s0 >> 1;
}
