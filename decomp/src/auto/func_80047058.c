#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 jugando;
extern s8 D_8007CA38;


void func_80047058(void) {
    jugando = 0;
    D_8007CA38 = 0;
}
