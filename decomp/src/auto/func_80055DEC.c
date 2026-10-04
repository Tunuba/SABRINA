#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007CBD4;


void func_80055DEC(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x94) = 0;
    D_8007CBD4 &= ~0x40;
}
