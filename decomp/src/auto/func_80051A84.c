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
extern s32 func_800519E4();
extern s32 func_800519F8();
extern s32 func_80051A0C();
extern s32 func_80051A20();
extern s32 func_80051A34();
extern s32 func_80051A48();
extern s32 func_80051A5C();
extern s32 func_80051A70();

void func_80051A84(void) {
    s32 temp_s0;

    temp_s0 = func_800143E4();
    D_800D5370 = OpenEvent(-0x0BFFFFFF, 4, 0x1000, (s32) func_800519E4);
    D_800D5374 = OpenEvent(-0x0BFFFFFF, 0x8000, 0x1000, (s32) func_800519F8);
    D_800D5378 = OpenEvent(-0x0BFFFFFF, 0x100, 0x1000, (s32) func_80051A0C);
    D_800D537C = OpenEvent(-0x0BFFFFFF, 0x2000, 0x1000, (s32) func_80051A20);
    D_800D5380 = OpenEvent(-0x0FFFFFEF, 4, 0x1000, (s32) func_80051A34);
    D_800D5384 = OpenEvent(-0x0FFFFFEF, 0x8000, 0x1000, (s32) func_80051A48);
    D_800D5388 = OpenEvent(-0x0FFFFFEF, 0x100, 0x1000, (s32) func_80051A5C);
    D_800D538C = OpenEvent(-0x0FFFFFEF, 0x2000, 0x1000, (s32) func_80051A70);
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
