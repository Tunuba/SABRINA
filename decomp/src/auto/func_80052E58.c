#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80052E58(void *arg0, void *arg1) {
    if ((M2C_FIELD(arg1, s16 *, 0x112) & 0x1000) && !(M2C_FIELD(arg0, s16 *, 0x112) & 0x100)) {
        M2C_FIELD(arg0, s8 *, 0x118) = (s8) (M2C_FIELD(arg0, s8 *, 0x118) - M2C_FIELD(arg1, s8 *, 0x119));
    }
}
