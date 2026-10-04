#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D5390;
extern s32 D_800D5394;
extern s32 D_800D5398;
extern s32 D_800D539C;
extern s32 D_800D53A0;
extern s32 D_800D53A4;
extern s32 D_800D53A8;
extern s32 D_800D53AC;

void func_80051D14(void) {
    TestEvent();
    TestEvent();
    TestEvent();
    TestEvent();
    TestEvent();
    TestEvent();
    TestEvent();
    TestEvent();
    D_800D539C = 0;
    D_800D5398 = D_800D539C;
    D_800D5394 = D_800D5398;
    D_800D5390 = D_800D5394;
    D_800D53AC = 0;
    D_800D53A8 = D_800D53AC;
    D_800D53A4 = D_800D53A8;
    D_800D53A0 = D_800D53A4;
}
