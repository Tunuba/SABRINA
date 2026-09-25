#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_800221A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_8001BE8C(M2C_FIELD(arg0, s32 *, 0x28), 0, arg2, func_8001BF8C(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0x2C), arg1, arg3));
}
