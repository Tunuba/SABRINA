#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_80059F2C(s32 arg0) {
    if ((p_sabrina != NULL) && (p_sabrina->forma.banderas & 1) && (M2C_FIELD((arg0 + 0x74), s32 *, 8) >= func_8002225C(arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z))) {
        M2C_FIELD(arg0, M2C_UNK (**)(s32, Objeto *), 0x10)(arg0, p_sabrina);
    }
}
