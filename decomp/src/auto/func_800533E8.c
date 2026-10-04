#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800533E8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x74) = 0;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), void **, 4), s8 *, 0x68) = 5;
}
