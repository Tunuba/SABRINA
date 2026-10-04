#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];

void func_80048104(s32 arg0) {
    s16 temp_v0;
    void *temp_a2;
    void *var_v1;

    var_v1 = *arg0;
    temp_a2 = var_v1;
loop_3:
    temp_v0 = M2C_FIELD(var_v1, s16 *, 0xE);
    if (temp_v0 != 0) {
        var_v1 = D_800D588C + (temp_v0 * 0x18);
        if (var_v1 == temp_a2) {
            var_v1 = D_800D588C + (M2C_FIELD(var_v1, s16 *, 0x10) * 0x18);
        } else {
            goto loop_3;
        }
    }
    *arg0 = var_v1;
}
