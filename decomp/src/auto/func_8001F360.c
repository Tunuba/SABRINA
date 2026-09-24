#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007CA84;
extern u8 D_8007CA8C[];
extern u8 D_8007CA90[];


void func_8001F360(s32 arg0) {
    s16 temp_v1;
    s32 *var_s1;
    s32 temp_s2;
    s32 var_s0;

    var_s0 = arg0;
    var_s1 = NULL;
loop_10:
    if (var_s0 != 0) {
        if (M2C_FIELD(var_s0, u8 *, 0x4A) != 0) {
            func_8001F41C(var_s0);
        }
        temp_s2 = M2C_FIELD(var_s0, s32 *, 0);
        M2C_FIELD(var_s0, M2C_UNK (**)(s32), 0x50)(var_s0);
        temp_v1 = M2C_FIELD(var_s0, s16 *, 0x40);
        M2C_FIELD(var_s0, s16 *, 0x40) = (s16) (temp_v1 - 1);
        if (temp_v1 < 0) {
            if (var_s1 == NULL) {
                *D_8007CA8C = temp_s2;
            } else {
                *var_s1 = temp_s2;
            }
            M2C_FIELD(var_s0, s32 *, 0) = (s32) *D_8007CA90;
            *D_8007CA90 = var_s0;
            D_8007CA84 -= 1;
        } else {
            var_s1 = (s32 *) var_s0;
        }
        var_s0 = temp_s2;
        goto loop_10;
    }
}
