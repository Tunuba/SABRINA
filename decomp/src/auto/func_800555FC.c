#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800555FC(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x78), s16 *, 0x40) = 1;
    thunk_FUN_8004866c((s32) arg0);
}
