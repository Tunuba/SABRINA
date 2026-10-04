#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074EDC;


s32 func_8003FD90(void) {
    return D_80074EDC != 1;
}
