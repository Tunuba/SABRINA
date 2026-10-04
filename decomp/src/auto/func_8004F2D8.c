#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D1604;
extern s32 D_800D1608;
extern u8 D_800D2AD0[];
extern u8 D_800D5090[];
extern u8 D_8007594C[];
extern s32 D_8007CA58;
extern s16 D_8007CC4E;
extern u16 D_8007CC50;
extern u16 D_8007CC58;
extern u16 D_8007CC5A;


void func_8004F2D8(s32 arg2) {
    s32 var_a0;

    if (D_8007CA58 & 0x8000) {
        if (D_8007CC50 != 0) {
            TocarSonido((s32) (s16) D_800D1604, 0, 0x2A, 0x7F);
            D_8007CC50 -= 1;
        } else {
            TocarSonido((s32) (s16) D_800D1608, 0, 0x2A, 0x7F);
        }
    }
    if (D_8007CA58 & 0x2000) {
        if (D_8007CC50 != ((D_8007CC58 + D_8007CC5A) - 1)) {
            TocarSonido((s32) (s16) D_800D1604, 0, 0x2A, 0x7F);
            D_8007CC50 += 1;
        } else {
            TocarSonido((s32) (s16) D_800D1608, 0, 0x2A, 0x7F);
        }
    }
    if (arg2 != 0) {
        if ((D_8007CC58 + D_8007CC5A) != 0) {
            if (*(D_800D5090 + (D_8007CC50 * 2)) != 0) {
                D_8007CC4E = 6;
            } else {
                D_8007CC4E = 2;
            }
        } else {
            D_8007CC4E = 0;
        }
    } else {
        D_8007CC4E = 1;
        var_a0 = 0;
loop_18:
        if (var_a0 != 0x10) {
            if ((s8) D_8007594C[var_a0] != *(var_a0 + (D_800D2AD0 + (D_8007CC50 << 6)))) {
                D_8007CC4E = 0;
            }
            var_a0 = (var_a0 + 1) & 0xFFFF;
            goto loop_18;
        }
    }
    if (*(D_800D5090 + (D_8007CC50 * 2)) != 0) {
        func_80019738();
    }
}
