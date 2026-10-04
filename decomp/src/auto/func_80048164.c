#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];

void func_80048164(s32 arg0, s32 arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s32 var_a1;
    s32 var_a2;

    var_a1 = arg1;
    var_a2 = 0;
    if (var_a1 != 0) {
        if (M2C_FIELD(var_a1, s16 *, 0xE) != 0) {
loop_4:
            temp_v0 = M2C_FIELD(var_a1, s16 *, 0xE);
            if (temp_v0 == 0) {
                goto block_10;
            }
            var_a2 += 1;
            var_a1 = (s32) (D_800D588C + (temp_v0 * 0x18));
            if (var_a2 < 3) {
                goto loop_4;
            }
        } else if (M2C_FIELD(var_a1, s16 *, 0x10) != 0) {
loop_9:
            temp_v0_2 = M2C_FIELD(var_a1, s16 *, 0x10);
            if (temp_v0_2 == 0) {
                goto block_10;
            }
            var_a2 += 1;
            var_a1 = (s32) (D_800D588C + (temp_v0_2 * 0x18));
            if (var_a2 < 3) {
                goto loop_9;
            }
        } else {
block_10:
            if (var_a2 == 1) {
                M2C_FIELD(arg0, s16 *, 0x70) = 0xB;
            }
        }
    }
}
