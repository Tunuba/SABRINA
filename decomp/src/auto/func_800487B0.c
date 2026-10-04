#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_800487B0(s32 arg0, s32 arg1, s32 arg2) {
    return func_80021D44(arg0 + 0x32, (s32) func_8002218C(arg0, M2C_FIELD(arg1, s32 *, 0x24), M2C_FIELD(arg1, s32 *, 0x2C)), (s32) (s16) arg2);
}
