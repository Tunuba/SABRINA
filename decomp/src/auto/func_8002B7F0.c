#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8002B7F0(s32 arg0, s32 arg1) {
    return strncmp(arg0, arg1, 0xC) == 0;
}
