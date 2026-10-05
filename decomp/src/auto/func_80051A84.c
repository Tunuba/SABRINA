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
    D_800D5370 = OpenEvent(-0x0BFFFFFF, 4, 0x1000);
    D_800D5374 = OpenEvent(-0x0BFFFFFF, 0x8000, 0x1000);
    D_800D5378 = OpenEvent(-0x0BFFFFFF, 0x100, 0x1000);
    D_800D537C = OpenEvent(-0x0BFFFFFF, 0x2000, 0x1000);
    D_800D5380 = OpenEvent(-0x0FFFFFEF, 4, 0x1000);
    D_800D5384 = OpenEvent(-0x0FFFFFEF, 0x8000, 0x1000);
    D_800D5388 = OpenEvent(-0x0FFFFFEF, 0x100, 0x1000);
    D_800D538C = OpenEvent(-0x0FFFFFEF, 0x2000, 0x1000);
    EnableEvent(D_800D5370);
    EnableEvent(D_800D5374);
    EnableEvent(D_800D5378);
    EnableEvent(D_800D537C);
    EnableEvent(D_800D5380);
    EnableEvent(D_800D5384);
    EnableEvent(D_800D5388);
    EnableEvent(D_800D538C);
    func_80051D14();
    if (temp_s0 == 1) {
        func_800143F4();
    }
}
