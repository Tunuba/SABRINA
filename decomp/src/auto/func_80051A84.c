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

void func_80051A84(void) {
    s32 temp_s0;

    temp_s0 = func_800143E4();
    D_800D5370 = OpenEvent();
    D_800D5374 = OpenEvent();
    D_800D5378 = OpenEvent();
    D_800D537C = OpenEvent();
    D_800D5380 = OpenEvent();
    D_800D5384 = OpenEvent();
    D_800D5388 = OpenEvent();
    D_800D538C = OpenEvent();
    EnableEvent();
    EnableEvent();
    EnableEvent();
    EnableEvent();
    EnableEvent();
    EnableEvent();
    EnableEvent();
    EnableEvent();
    func_80051D14();
    if (temp_s0 == 1) {
        func_800143F4();
    }
}
