#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 jugando;
extern s8 nivel_actual;
extern s8 D_8007CA01;
extern s8 D_8007CA38;


void func_80046B50(void) {
    jugando = 0;
    D_8007CA01 = nivel_actual;
    D_8007CA38 = 0;
    nivel_actual = 0xD;
}
