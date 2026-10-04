#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800686C4[];
extern s32 D_8007CA3C;


s32 func_8001B000(s32 arg0) {
    s32 temp_s0;
    s32 var_s0;

    var_s0 = D_8007CA3C;
loop_4:
    if (var_s0 == 0) {
        temp_s0 = Reservar(0xC, (s32) D_800686C4);
        M2C_FIELD(temp_s0, s32 *, 4) = Reservar(func_800150F0(arg0) + 1, (s32) D_800686C4);
        strcpy(M2C_FIELD(temp_s0, s32 *, 4), arg0);
        M2C_FIELD(temp_s0, s32 *, 0) = func_8001B0C8(arg0);
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) D_8007CA3C;
        D_8007CA3C = temp_s0;
        return M2C_FIELD(temp_s0, s32 *, 0);
    }
    if (strcmp(M2C_FIELD(var_s0, s32 *, 4), arg0) == 0) {
        return M2C_FIELD(var_s0, s32 *, 0);
    }
    var_s0 = M2C_FIELD(var_s0, s32 *, 8);
    goto loop_4;
}
