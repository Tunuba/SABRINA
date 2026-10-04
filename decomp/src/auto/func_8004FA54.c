#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D1604;
extern s32 D_800D1608;
extern s32 D_800D160C;
extern u8 D_80075AA4[];
extern u16 D_80075AC0[];
extern u16 D_80075AD0[];
extern u8 D_8007C8F8[];
extern u8 D_8007C8FC[];
extern u8 D_8007C904[];
extern u8 D_8007C90C[];
extern u8 D_8007C914[];
extern u8 D_8007C91C[];
extern u8 D_8007C924[];
extern s32 D_8007CA58;
extern s32 D_8007CC44;
extern s16 D_8007CC4A;
extern u16 D_8007CC4E;
extern u16 D_8007CC52;
extern u16 D_8007CC54;

u8 D_80075AA4[0x1C];                                /* unable to generate initializer: cannot parse D_8007C8F8 as integer */

void func_8004FA54(s32 arg0, s32 arg1) {
    s32 temp_a3;
    u16 temp_v0;

    temp_v0 = D_80075AC0[D_8007CC4E];
    if (D_8007CC54 != temp_v0) {
        D_8007CC52 = D_80075AD0[D_8007CC4E];
        D_8007CC54 = temp_v0;
    }
    if (D_8007CC44 != 1) {
        if (D_8007CA58 & 0x4000) {
            if (D_8007CC52 != D_80075AD0[D_8007CC4E]) {
                TocarSonido((s32) (s16) D_800D1604, 0, 0x2A, 0x7F);
                D_8007CC52 += 1;
            } else {
                TocarSonido((s32) (s16) D_800D1608, 0, 0x2A, 0x7F);
            }
        }
        if (D_8007CA58 & 0x1000) {
            if (D_8007CC52 != 0) {
                TocarSonido((s32) (s16) D_800D1604, 0, 0x2A, 0x7F);
                D_8007CC52 -= 1;
            } else {
                TocarSonido((s32) (s16) D_800D1608, 0, 0x2A, 0x7F);
            }
        }
        if (D_8007CA58 & 0x40) {
            TocarSonido((s32) (s16) D_800D160C, 0, 0x2A, 0x7F);
            temp_a3 = D_8007CC4E * 4;
            *(*(D_80075AA4 + temp_a3) + (D_8007CC52 * 4))(arg0, arg1, D_8007CC4A & 0xFFFF, temp_a3);
        }
    }
}
