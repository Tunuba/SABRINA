#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_8003BFC4(void *arg0, s32 arg1) {
    if (arg1 == p_sabrina) {
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
    }
}
