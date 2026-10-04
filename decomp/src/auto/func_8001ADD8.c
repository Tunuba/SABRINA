#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006561C[];


s32 func_8001ADD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t1;
    s32 var_v0;
    s8 var_s1;
    u16 temp_a0;
    u8 var_t0;

    var_v0 = 0;
    var_s1 = 0;
    M2C_FIELD(arg1, u8 *, 5) = 0U;
loop_2:
    temp_v1 = arg3 + var_s1;
    if ((*(arg0 + (temp_v1 * 2)) != 0x1F0) && (arg2 != temp_v1)) {
        var_s1 = (var_s1 + 1) & 0xFF;
        goto loop_2;
    }
    M2C_FIELD(arg1, s8 *, 0xA) = var_s1;
    M2C_FIELD(arg1, s8 *, 0xB) = 0x20;
    if (arg2 != (arg3 + var_s1)) {
        var_v0 = Reservar(var_s1 << 7, (s32) D_8006561C);
        var_a1 = arg0 + (arg3 * 2);
        var_a2 = var_v0;
        var_a3 = 0;
loop_13:
        var_t0 = 0;
        if (var_a3 != 0x20) {
            var_t1 = 0;
loop_11:
            if (var_t0 != var_s1) {
                if ((*(var_a1 + var_t1) != 0) && ((u8) M2C_FIELD(arg1, u8 *, 5) < var_t0)) {
                    M2C_FIELD(arg1, u8 *, 5) = var_t0;
                }
                temp_a0 = *(var_a1 + var_t1);
                var_t1 += 2;
                temp_v1_2 = var_a2;
                var_a2 = temp_v1_2 + 2;
                *temp_v1_2 = temp_a0;
                var_t0 = (var_t0 + 1) & 0xFF;
                goto loop_11;
            }
            var_a1 += arg2 * 2;
            var_a3 = (var_a3 + 1) & 0xFF;
            goto loop_13;
        }
    }
    M2C_FIELD(arg1, u8 *, 5) = (u8) (M2C_FIELD(arg1, u8 *, 5) + 1);
    return var_v0;
}
