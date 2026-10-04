#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80060B50[];
extern u8 D_80060B70[];
extern u8 D_80063688[];
extern u8 D_800636C8[];
extern s32 D_800636CC[];
extern s32 D_800636D8[];
extern u8 D_80063798[];
extern u8 D_8006379A;

u8 D_80063688[0x40];                                /* unable to generate initializer: cannot parse D_80060B18 as integer */
u8 D_800636C8[4];                                   /* unable to generate initializer: cannot parse D_80063688 as integer */

void func_80012B0C(s32 arg0) {
    s32 temp_v1;

    temp_v1 = arg0 & 7;
    if (temp_v1 != 3) {
        if (temp_v1 < 4) {
            if (temp_v1 != 0) {
                goto block_8;
            }
            goto block_6;
        }
        if (temp_v1 != 5) {
block_8:
            if ((u8) D_8006379A >= 2U) {
                D_80063794("ResetGraph(%d)...\n", arg0);
            }
            M2C_FIELD(*D_800636C8, M2C_UNK (**)(M2C_UNK), 0x34)(1);
            return;
        }
        goto block_7;
    }
block_6:
    printf((s32) "ResetGraph:jtb=%08x,env=%08x\n", D_80063688, D_80063798);
block_7:
    func_80012AE4((s32) D_80063798, 0, 0x80);
    func_80016910();
    GPU_cw();
    M2C_FIELD(D_80063798, u8 *, 0) = func_80012640(arg0);
    D_80063798[1] = 1;
    M2C_FIELD(D_80063798, u16 *, 4) = (u16) D_800636CC[M2C_FIELD(D_80063798, u8 *, 0)];
    M2C_FIELD(D_80063798, u16 *, 6) = (u16) D_800636D8[M2C_FIELD(D_80063798, u8 *, 0)];
    func_80012AE4((s32) (D_80063798 + 0x10), -1, 0x5C);
    func_80012AE4((s32) (D_80063798 + 0x6C), -1, 0x14);
}
