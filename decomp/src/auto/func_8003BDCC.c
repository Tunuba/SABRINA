#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_8003BDCC(s32 arg0) {
    if (func_8002225C(arg0, p_sabrina->x, (p_sabrina->y - 0x4001) - 0x7FFF, p_sabrina->z) < M2C_FIELD(arg0, s32 *, 0x74)) {
        M2C_FIELD(arg0, M2C_UNK (**)(s32, Objeto *), 8)(arg0, p_sabrina);
    }
}
