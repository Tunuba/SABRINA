#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8002713C(s32 arg0) {
    return (((s32) (M2C_FIELD(arg0, u8 *, 0xE3) + 1) >> 1) * 4) + ((((M2C_FIELD(arg0, u8 *, 0xE9) * 5) + 3) & 0xFFC) + 4) + M2C_FIELD(arg0, u16 *, 0xEC);
}
