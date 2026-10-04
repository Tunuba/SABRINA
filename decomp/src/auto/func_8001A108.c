#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006561C[];


void func_8001A108(s32 arg0, s32 arg1, s32 arg2) {
    s16 var_v1;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;
    s32 var_v0;
    u16 temp_v1;

    var_s0 = arg2;
    var_s2 = M2C_FIELD(arg1, s16 *, 8) * M2C_FIELD(arg1, s16 *, 0xA);
    temp_a0 = var_s2 * 2;
    temp_v0 = Reservar(temp_a0, (s32) D_8006561C);
    ArchivoLeer(arg0, temp_v0, temp_a0);
    var_v0 = temp_v0;
loop_8:
    var_s2 -= 1;
    if (var_s2 != 0) {
        temp_v1 = *var_v0;
        if (temp_v1 == 0) {
            var_v1 = 1;
            goto block_6;
        }
        if (temp_v1 == 0x7C1F) {
            *var_s0 = 0;
        } else {
            var_v1 = (((temp_v1 << 9) & 0x3C00 & 0xFFFF) | ((((s32) temp_v1 >> 0xB) & 0xF & 0xFFFF) | (((s32) temp_v1 >> 1) & 0x1E0 & 0xFFFF))) + 1;
block_6:
            *var_s0 = var_v1;
        }
        var_s0 += 2;
        var_v0 += 2;
        goto loop_8;
    }
    Liberar(temp_v0);
    M2C_FIELD(arg1, s16 *, 0x1A) = 0x10;
    M2C_FIELD(arg1, s8 *, 0x1D) = 0;
}
