#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006561C[];


void func_8001A668(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_lo;
    s32 temp_s4;
    s32 var_s1;
    s32 var_s3;
    u32 var_s2;

    var_s3 = arg0;
    temp_lo = arg1 * M2C_ERROR(/* Read from unset register $a3 */);
    var_s1 = (var_s3 + (M2C_ERROR(/* Read from unset register $a3 */) * (arg1 * arg2))) - temp_lo;
    temp_s4 = Reservar(temp_lo, (s32) D_8006561C);
    var_s2 = 0;
loop_2:
    if (var_s2 < (u32) ((u32) arg2 >> 1)) {
        memcpy(temp_s4, var_s3, temp_lo);
        memcpy(var_s3, var_s1, temp_lo);
        memcpy(var_s1, temp_s4, temp_lo);
        var_s1 -= temp_lo;
        var_s3 += temp_lo;
        var_s2 += 1;
        goto loop_2;
    }
    Liberar(temp_s4);
}
