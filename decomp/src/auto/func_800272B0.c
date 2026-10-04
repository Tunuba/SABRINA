#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80026CFC();
extern s32 func_80026D50();

static s32 (*D_8006CFA0)() = NULL;

s32 func_800272B0(void *arg0, s32 arg1_reg, s32 arg2_reg) {
    s8 arg1 = (s8) arg1_reg;
    s8 arg2 = (s8) arg2_reg;
    s32 var_v0;

    var_v0 = 0;
    if (D_8006CFA0() == 0) {
        var_v0 = 1;
        M2C_FIELD(arg0, s8 *, 0x46) = 1;
        M2C_FIELD(arg0, s32 (**)(s32), 0x14) = func_80026CFC;
        M2C_FIELD(arg0, s32 (**)(s32), 0x18) = func_80026D50;
        M2C_FIELD(arg0, s8 *, 0x51) = arg1;
        M2C_FIELD(arg0, s8 *, 0x52) = arg2;
        M2C_FIELD(arg0, s8 *, 0x53) = (s8) ((arg1 & 0xFF) == M2C_FIELD(arg0, u8 *, 0xE4));
    }
    return var_v0;
}
