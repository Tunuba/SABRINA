#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D5370;
extern s32 D_800D5374;
extern s32 D_800D5378;
extern s32 D_800D537C;
extern s32 D_800D5380;
extern s32 D_800D5384;
extern s32 D_800D5388;
extern s32 D_800D538C;
extern s32 D_800D5390;
extern s32 D_800D5394;
extern s32 D_800D5398;
extern s32 D_800D539C;
extern s32 D_800D53A0;
extern s32 D_800D53A4;
extern s32 D_800D53A8;
extern s32 D_800D53AC;

void func_80051D14(void) {
    TestEvent(D_800D5370);
    TestEvent(D_800D5374);
    TestEvent(D_800D5378);
    TestEvent(D_800D537C);
    TestEvent(D_800D5380);
    TestEvent(D_800D5384);
    TestEvent(D_800D5388);
    TestEvent(D_800D538C);
    D_800D539C = 0;
    D_800D5398 = D_800D539C;
    D_800D5394 = D_800D5398;
    D_800D5390 = D_800D5394;
    D_800D53AC = 0;
    D_800D53A8 = D_800D53AC;
    D_800D53A4 = D_800D53A8;
    D_800D53A0 = D_800D53A4;
}
