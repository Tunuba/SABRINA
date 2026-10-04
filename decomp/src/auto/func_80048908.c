#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80048908(void *arg0, s16 *arg1, s32 *arg2, s32 arg3) {
    s16 var_v1;

    *arg1 -= 1;
    if (*arg1 <= 0) {
        M2C_FIELD(arg0, M2C_UNK (**)(), 0xC)();
        if (*arg2 != 0) {
            if (arg3 & 4) {
                var_v1 = 0xB;
            } else {
                var_v1 = 3;
            }
            goto block_9;
        }
        if (arg3 & 1) {
            if (arg3 & 4) {
                var_v1 = 0xB;
            } else {
                var_v1 = 2;
            }
block_9:
            M2C_FIELD(arg0, s16 *, 0x70) = var_v1;
        }
    }
}
