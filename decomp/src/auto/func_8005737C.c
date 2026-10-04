#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005737C(s32 arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD((arg0 + 0x74), s16 *, 0x24);
    if (temp_v0 >= 0) {
        thunk_FUN_80042924((s32) temp_v0);
    }
    thunk_FUN_8004866c(arg0);
}
