#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CA2C;


void func_80049218(s32 arg0, void *arg1, void *arg2) {
    s8 var_v0;

    if ((D_8007CA2C == 0) && (func_8004906C(arg0, (s32) p_sabrina) != 0)) {
        if (M2C_FIELD(arg1, s8 *, 0x31) >= 0) {
            var_v0 = -1;
        } else {
            var_v0 = 1;
        }
        M2C_FIELD(arg1, s8 *, 0x31) = var_v0;
    }
    func_80048754(arg0, (s32) (arg1 + 0x2C), (s32) (s16) M2C_FIELD(arg2, u16 *, 0), (s32) (s16) M2C_FIELD(arg2, u16 *, 2));
}
