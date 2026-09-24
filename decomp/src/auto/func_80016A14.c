#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 * D_800649A8;


s32 func_80016A14(s32 arg0) {
    u16 temp_v0;

    temp_v0 = *D_800649A8;
    *D_800649A8 = (u16) arg0;
    return (s32) temp_v0;
}
