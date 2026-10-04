#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_8007CA04;


s32 func_80017C6C(s32 arg0, s32 arg1, void *arg2) {
    M2C_FIELD(arg2, void **, 0) = (void *) D_8007CA04;
    M2C_FIELD(arg2, s32 *, 4) = arg1;
    M2C_FIELD(arg2, s32 *, 8) = arg0;
    D_8007CA04 = arg2;
    return arg0;
}
