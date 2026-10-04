#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80063824[];


void func_800144C4(s32 arg0, s32 arg1, s32 arg2) {
    s16 var_a3;
    s32 temp_t0;
    s32 var_v0;
    void *temp_v1;

    temp_t0 = arg0 & 0xFFFF;
    var_a3 = 0x48;
    if (temp_t0 >= 3) {
        return;
    }
    temp_v1 = (temp_t0 * 0x10) + *D_80063824;
    M2C_FIELD(temp_v1, s16 *, 4) = 0;
    M2C_FIELD(temp_v1, s16 *, 8) = (s16) arg1;
    if ((u32) temp_t0 < 2U) {
        if (arg2 & 0x10) {
            var_a3 = 0x49;
        }
        var_v0 = arg2 & 0x1000;
        if (!(arg2 & 1)) {
            var_a3 |= 0x100;
        }
    } else {
        var_v0 = arg2 & 0x1000;
        if (temp_t0 == 2) {
            var_v0 = arg2 & 0x1000;
            if (!(arg2 & 1)) {
                var_a3 = 0x248;
            }
        }
    }
    if (var_v0 != 0) {
        var_a3 |= 0x10;
    }
    M2C_FIELD(((temp_t0 * 0x10) + *D_80063824), s16 *, 4) = var_a3;
}
