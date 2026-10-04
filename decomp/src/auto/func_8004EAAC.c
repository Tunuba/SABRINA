#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8004EAAC(s32 arg0) {
    return M2C_FIELD((arg0 - 4), s32 *, 0xFC);
}
