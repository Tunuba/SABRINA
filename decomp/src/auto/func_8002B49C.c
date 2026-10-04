#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80091460;
extern s32 D_80091464;
extern u8 D_80091468[];
extern u8 D_80061244[];
extern u8 D_80061250[];
extern u8 D_8006125C[];
extern u8 D_80061268[];
extern u8 D_80061274[];
extern u8 D_80061280[];
extern u8 D_8006128C[];
extern u8 D_80061298[];
extern u8 D_8006129C[];
extern u8 D_800612A8[];
extern u8 D_800612B8[];
extern u8 D_800612C4[];
extern u8 D_800612CC[];
extern u8 D_800612D8[];
extern u8 D_800612E4[];
extern u8 D_800612EC[];
extern u8 D_800612F8[];
extern u8 D_80061304[];
extern u8 D_80061310[];
extern u8 D_8006131C[];
extern u8 D_80061324[];
extern u8 D_80061330[];
extern u8 D_80061338[];
extern u8 D_80061340[];
extern u8 D_8006134C[];
extern u8 D_80061354[];
extern u8 D_80061360[];
extern u8 D_8006136C[];
extern u8 D_80061378[];
extern u8 D_80061380[];
extern u8 D_80061390[];
extern u8 D_8006148C[];
extern u8 D_8006D2C8[];
extern s32 * D_8006D2F4;
extern u8 D_8006D321;
extern u8 D_8006D328[];
extern u8 D_8006D3A8[];

u8 D_8006D328[0x80];                                /* unable to generate initializer: cannot parse D_80061338 as integer */
u8 D_8006D3A8[0x20];                                /* unable to generate initializer: cannot parse D_80061378 as integer */

void func_8002B49C(s32 arg0) {
    s32 var_v0;

    D_80091460 = func_8001626C(-1) + 0x3C0;
    D_80091464 = 0;
    *D_80091468 = D_8006148C;
loop_1:
    if ((D_80091460 < func_8001626C(-1)) || (D_80091464 += 1, ((D_80091464 > 0x3C0000) != 0))) {
        puts((s32) D_80061380);
        printf((s32) D_80061390, *D_80091468, *((D_8006D321 * 4) + D_8006D328), *((M2C_FIELD(D_8006D2C8, u8 *, 0) * 4) + D_8006D3A8), *((M2C_FIELD(D_8006D2C8, u8 *, 1) * 4) + D_8006D3A8));
        func_8002B0AC();
        var_v0 = -1;
    } else {
        var_v0 = 0;
    }
    if ((var_v0 == 0) && (*D_8006D2F4 & 0x01000000) && (arg0 == 0)) {
        goto loop_1;
    }
}
