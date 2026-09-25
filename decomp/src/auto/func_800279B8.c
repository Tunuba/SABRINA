#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006CFB8;
extern s32 D_8006CFD0;


s32 func_800279B8(s32 arg0) {
    if (D_8006CFD0 == 0) {
        return 0;
    }
    return M2C_FIELD((((arg0 >> 4) * 0xF0) + D_8006CFB8), u8 *, 0xE8) == 8;
}
