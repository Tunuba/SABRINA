#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006CFD0;
extern s32 D_8006CFF0;

static s32 (*D_8006CF8C)(void *, s32) = NULL;
static M2C_UNK (*D_8006CF90)(void *) = NULL;

s32 func_80027534(void *arg0) {
    s32 temp_v0;
    s32 var_a0;
    s32 var_v0;

    var_a0 = 0;
    if ((D_8006CFD0 != 0) && (((u8) *M2C_FIELD(arg0, u8 **, 0x3C) >> 4) == 8)) {
        var_a0 = M2C_FIELD(arg0, u8 *, 0x37) == 0;
    }
    D_8006CFF0 = var_a0;
    if (var_a0 == 0) {
        D_8006CF90(arg0);
    }
    temp_v0 = func_8002643C((s32) arg0, D_8006CF8C(arg0, D_8006CFF0) & 0xFF);
    var_v0 = temp_v0;
    if ((temp_v0 != 0x5A) && (temp_v0 != 0)) {
        var_v0 = -4;
        if (temp_v0 < 0) {
            var_v0 = temp_v0;
        }
    }
    return var_v0;
}
