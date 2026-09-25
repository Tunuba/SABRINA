#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8002225C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_8001C004(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0x28), M2C_FIELD(arg0, s32 *, 0x2C), arg1, /* extra? */ arg2, /* extra? */ arg3);
}
