#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



extern M2C_UNK (*D_8006CF88)();

s32 func_80026D50(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x53) != 0) {
        if (M2C_FIELD(arg0, u8 *, 0x46) == 2) {
            return 1;
        }
        M2C_FIELD(arg0, u8 *, 0x46) = 0xFEU;
        goto block_5;
    }
    D_8006CF88();
block_5:
    return 0;
}
