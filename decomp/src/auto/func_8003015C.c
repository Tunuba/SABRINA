#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_8007CB8C;


s32 func_8003015C(void) {
    s32 var_v0;

    var_v0 = 0;
    if (M2C_FIELD(M2C_FIELD(D_8007CB8C, void **, 0x1C), u8 *, 0x50) == 2) {
        var_v0 = 1;
    }
    return var_v0;
}
