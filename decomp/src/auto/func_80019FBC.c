#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006561C[];


void func_80019FBC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_s0;
    s32 var_s2;
    s32 var_v0;
    u8 temp_v1;

    var_s0 = arg2;
    var_s2 = (M2C_FIELD(arg1, s16 *, 8) * M2C_FIELD(arg1, s16 *, 0xA)) & 0xFFFF;
    temp_a0 = var_s2 * 3;
    temp_v0 = Reservar(temp_a0, (s32) D_8006561C);
    ArchivoLeer(arg0, temp_v0, temp_a0);
    var_v0 = temp_v0;
loop_7:
    var_s2 = (var_s2 - 1) & 0xFFFF;
    if (var_s2 != 0) {
        temp_v1 = M2C_FIELD(var_v0, u8 *, 0);
        if ((temp_v1 == 0xFF) && (M2C_FIELD(var_v0, u8 *, 1) == 0) && (M2C_FIELD(var_v0, u8 *, 2) == 0xFF)) {
            temp_v1_2 = var_s0;
            var_s0 = temp_v1_2 + 2;
            *temp_v1_2 = 0;
        } else {
            temp_v1_3 = var_s0;
            var_s0 = temp_v1_3 + 2;
            *temp_v1_3 = (s16) ((((((s32) temp_v1 >> 4) & 0xFF) << 0xA) | ((((s32) M2C_FIELD(var_v0, u8 *, 2) >> 4) & 0xFF) | ((((s32) M2C_FIELD(var_v0, u8 *, 1) >> 4) & 0xFF) << 5))) + 1);
        }
        var_v0 += 3;
        goto loop_7;
    }
    Liberar(temp_v0);
    M2C_FIELD(arg1, s16 *, 0x1A) = 0x100;
    M2C_FIELD(arg1, s8 *, 0x1D) = 1;
}
