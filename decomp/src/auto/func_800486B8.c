#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_800486B8(s32 arg0, s32 arg1) {
    if (func_8002225C(arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z) < arg1) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    }
}
