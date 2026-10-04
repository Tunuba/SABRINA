#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007CA1C;
extern u16 D_8007CA1E;
extern u16 D_8007CBF8;
extern s8 D_8007CBFC;


void func_80046B6C(void) {
    D_8007CBF8 = D_8007CA1E;
    D_8007CA1E = 0;
    D_8007CBFC = (s8) D_8007CA1C;
    D_8007CA1C = 1;
}
