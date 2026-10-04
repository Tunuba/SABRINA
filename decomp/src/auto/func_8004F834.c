#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D1810[];
extern u8 D_800D3090[];
extern s16 D_8007CA20;
extern s32 D_8007CC40;
extern s32 D_8007CC44;
extern s16 D_8007CC4E;
extern u16 D_8007CC50;
extern u16 D_8007CC56;
extern s16 D_8007CC58;
extern s16 D_8007CC5A;
extern s32 (*D_8007CC38)();


void func_8004F834(s32 arg0, s32 arg1) {
    M2C_UNK sp1C;

    D_8007CA20 = 0xF9;
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC4E = 0;
    if (D_8007CC56 == 2) {
        func_80050AB8(arg0, (s32) ((D_8007CC50 * 0x28) + (D_800D1810 + (arg1 * 0x258))), 1);
        func_80051298(0, 0, (s32) &sp1C);
        D_8007CC40 = func_80050C84((s32) D_800D3090, 0, 0x2000);
        func_80051298(0, 0, (s32) &sp1C);
        func_80050C40();
        D_8007CC44 = 2;
        D_8007CA20 = 0;
        if (D_8007CC38 != NULL) {
            D_8007CC38(D_800D3090 + 0x200);
        }
    }
}
