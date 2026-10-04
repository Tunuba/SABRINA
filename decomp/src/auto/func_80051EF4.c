#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D53A0;
extern s32 D_800D53A4;
extern s32 D_800D53A8;
extern s32 D_800D53AC;

s32 func_80051EF4(void) {
    s32 temp_s0;

    do {
        temp_s0 = D_800D53A0 + (D_800D53A4 * 2) + (D_800D53A8 * 4) + (D_800D53AC * 8);
    } while (temp_s0 == 0);
    TestEvent();
    TestEvent();
    TestEvent();
    TestEvent();
    D_800D53AC = 0;
    D_800D53A8 = D_800D53AC;
    D_800D53A4 = D_800D53A8;
    D_800D53A0 = D_800D53A4;
    return temp_s0 >> 1;
}
