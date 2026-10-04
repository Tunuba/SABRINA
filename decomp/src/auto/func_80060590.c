#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];

s32 func_80060590(s32 arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xE);
    if (temp_v0 != 0) {
        return (s32) (D_800D588C + (temp_v0 * 0x18));
    }
    return 0;
}
