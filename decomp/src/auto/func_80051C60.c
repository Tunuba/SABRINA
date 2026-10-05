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

void func_80051C60(void) {
    s32 temp_s0;

    temp_s0 = func_800143E4();
    CloseEvent(D_800D5370);
    CloseEvent(D_800D5374);
    CloseEvent(D_800D5378);
    CloseEvent(D_800D537C);
    CloseEvent(D_800D5380);
    CloseEvent(D_800D5384);
    CloseEvent(D_800D5388);
    CloseEvent(D_800D538C);
    if (temp_s0 == 1) {
        func_800143F4();
    }
}
