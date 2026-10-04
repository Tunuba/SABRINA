#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 jugando;
extern s8 nivel_actual;
extern s16 D_8007CA1E;
extern s8 D_8007CA38;


void func_80046EAC(void) {
    jugando = 0;
    D_8007CA38 = 0;
    nivel_actual = 0;
    D_8007CA1E = 0;
}
