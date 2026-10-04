#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D5830[];
extern u8 D_800D5832[];
extern s16 D_800D5840;
extern s16 D_800D5842;
extern s16 D_800D584A;
extern s16 D_800D584C;

void func_8005D1D0(void) {
    s32 temp_v0;
    s32 var_v1;

    var_v1 = 0x800000;
loop_2:
    if (D_800D584A == 0) {
        temp_v0 = var_v1 - 1;
        var_v1 = temp_v0;
        if (temp_v0 != 0) {
            goto loop_2;
        }
    }
    D_800D584A = 0;
    D_800D584C ^= 1;
    D_800D5840 = *(D_800D5830 + (D_800D584C * 8));
    D_800D5842 = *(D_800D5832 + (D_800D584C * 8));
}
