#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80076D0C[];
extern u8 D_80076D5C[];
extern u8 D_80076D94[];
extern u8 D_80076E3C[];
extern u8 D_80076E6C[];
extern u8 D_80076E9C[];
extern u8 D_80076ED0[];
extern u8 D_80076F04[];
extern u8 D_80076F3C[];
extern u8 D_80076F74[];
extern u8 D_80076FAC[];
extern u8 D_80076FE4[];
extern u8 D_8007705C[];
extern u8 D_800770E4[];
extern u8 D_80077110[];
extern u8 D_8007717C[];
extern u8 D_800771AC[];
extern u8 D_800771DC[];
extern u8 D_80077210[];
extern u8 D_80077240[];
extern u8 D_80077274[];
extern u8 D_800772BC[];
extern u8 D_80077344[];
extern u8 D_80077378[];
extern u8 D_800773A4[];
extern u8 D_800773EC[];
extern u8 D_80077418[];
extern u8 D_80077460[];
extern u8 D_800774A0[];
extern u8 D_800774E4[];
extern u8 D_80077524[];
extern u8 D_80077564[];
extern u8 D_800775A4[];
extern u8 D_800775EC[];
extern u8 D_80077620[];
extern u8 D_80079D48[];
extern u8 D_8007C938[];
extern u8 D_8007C95C[];
extern u8 D_8007C96C[];
extern u8 D_8007C970[];
extern u8 D_8007C974[];
extern u8 D_8007C97C[];
extern u8 D_8007C984[];
extern u8 D_8007C988[];

u8 D_80079D48[0xEC];                                /* unable to generate initializer: cannot parse D_8007C938 as integer */

void func_800193F8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s8 *var_v0;
    s8 var_a3;
    s8 var_v1;

    temp_a0 = *(D_80079D48 + (arg0 * 4));
    var_a3 = 0;
loop_5:
    if (var_a3 != 8) {
        if (var_a3 < arg1) {
            var_v1 = 0x50;
            var_v0 = temp_a0 + (arg2 + var_a3);
        } else {
            var_v1 = 0x4D;
            var_v0 = temp_a0 + (arg2 + var_a3);
        }
        *var_v0 = var_v1;
        var_a3 += 1;
        goto loop_5;
    }
}
