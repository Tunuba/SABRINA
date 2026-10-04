#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800D1610;
extern s8 D_800D1611;
extern s8 D_800D1612;
extern s8 D_800D1613;
extern u8 D_800D1614[];
extern u8 D_800D1670[];
extern u8 D_800D1690[];
extern u8 D_8007594C[];
extern u8 D_80075964[];
extern u8 D_800759E4[];


void func_8004EB04(void) {
    s32 var_a0;
    s32 var_a1;

    D_800D1610 = 0x53;
    D_800D1611 = 0x43;
    D_800D1612 = 0x11;
    D_800D1613 = 1;
    strcpy((s32) D_800D1614, (s32) D_8007594C);
    memcpy((s32) D_800D1690, (s32) D_80075964, 0x80);
    memset((s32) D_800D1670, 0, 0x20);
    var_a0 = 0;
    var_a1 = 0;
loop_2:
    if (var_a0 != 0x10) {
        D_800D1670[var_a1] = (u16) D_800759E4[var_a1];
        var_a0 = (var_a0 + 1) & 0xFFFF;
        var_a1 += 2;
        goto loop_2;
    }
}
