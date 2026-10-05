#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80026C18();
extern s32 func_80026C34();

extern s32 (*D_8006CFA0)();

s32 func_80027248(s32 arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 0;
    if (D_8006CFA0() == 0) {
        var_v0 = 1;
        M2C_FIELD(arg0, s8 *, 0x46) = 1;
        M2C_FIELD(arg0, s32 (**)(s32), 0x14) = func_80026C18;
        M2C_FIELD(arg0, s32 *, 0x20) = arg1;
        M2C_FIELD(arg0, s32 (**)(s32), 0x18) = func_80026C34;
    }
    return var_v0;
}
