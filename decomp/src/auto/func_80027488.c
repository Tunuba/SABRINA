#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006CFD0;
extern s32 D_8006CFE4;
extern s32 D_8006CFEC;

static M2C_UNK (*D_8006CF9C)(s32) = NULL;

s32 func_80027488(void *arg0) {
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0;

    if (D_8006CFEC != 0) {
        D_8006CF9C(M2C_FIELD(arg0, s32 *, 0xC) + 0x1E0);
        D_8006CF9C(M2C_FIELD(arg0, s32 *, 0xC) + 0x2D0);
    }
    var_a1 = 0;
    if (M2C_FIELD(arg0, u8 *, 0x37) == 0) {
        var_a1 = D_8006CFD0;
    }
    var_v0 = func_8002643C((s32) arg0, var_a1);
    if (var_v0 >= 0) {
        temp_v0 = (var_v0 & 0xF) * 2;
        D_8006CFE4 = temp_v0;
        var_v0 = 0;
        if (temp_v0 == 0) {
            D_8006CFE4 = 0x20;
            var_v0 = 0;
        }
    }
    return var_v0;
}
