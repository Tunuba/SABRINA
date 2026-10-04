#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80048710(s32 arg0, s32 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0x53) != arg1) {
        if (M2C_FIELD(arg0, u8 *, 0x51) != arg1) {
            M2C_FIELD(arg0, u8 *, 0x51) = (u8) arg1;
            M2C_FIELD(arg0, s8 *, 0x50) = 0;
            M2C_FIELD(arg0, s16 *, 0x4E) = 0x800;
        }
        return 0;
    }
    return 1;
}
