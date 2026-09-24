#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80084B14[];


void func_80014670(s32 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_UNK (*temp_s3)(s32 *, M2C_UNK, M2C_UNK);
    s32 temp_a0;
    u32 temp_v1;
    u32 var_s0;

    if (*arg0 == 0) {
        *arg0 = 1;
    }
    var_s0 = *(u32 *)0x150;
    temp_s3 = D_80084B0C;
    temp_v1 = var_s0 + ((*(s32 *)0x154 / 80) * 0x50);
    if (var_s0 < temp_v1) {
loop_4:
        temp_a0 = M2C_FIELD(var_s0, s32 *, 0);
        if ((temp_a0 != 0) && (strcmp(temp_a0, (s32) D_80084B14) == 0)) {
            M2C_FIELD(var_s0, M2C_UNK (**)(s32 *, M2C_UNK, M2C_UNK), 0x34) = temp_s3;
        } else {
            var_s0 += 0x50;
            if (var_s0 < temp_v1) {
                goto loop_4;
            }
        }
    }
    D_80084B0C(arg0, arg1, arg2);
}
