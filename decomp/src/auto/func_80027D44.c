#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



static s32 (*D_8006CF98)() = NULL;

s32 func_80027D44(s32 arg0, s32 arg1) {
    return func_80027248(D_8006CF98(), arg1);
}
