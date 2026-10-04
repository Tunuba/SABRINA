#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



u32 func_8002914C(u32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;

    temp_a2 = arg2 & 0x3F;
    if (temp_a2 != 0) {
        if ((0x20 - temp_a2) > 0) {
            return arg0 << temp_a2;
        }
        return 0U;
    }
    return arg0;
}
