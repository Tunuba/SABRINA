#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_8007CAFC;


void func_80037268(void) {
    M2C_FIELD(D_8007CAFC, s16 *, 0x70) = 8;
}
