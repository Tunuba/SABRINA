#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80034F84(s32 arg0, s32 arg1) {
    func_80021E54(arg0 + 0x32, (s32) func_8002218C(arg0, M2C_FIELD(arg1, s32 *, 0x24), M2C_FIELD(arg1, s32 *, 0x2C)), 3, 3);
    return 1;
}
