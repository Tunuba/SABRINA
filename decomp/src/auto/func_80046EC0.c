#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA1C;
extern u16 D_8007CA1E;
extern u16 D_8007CBF8;
extern u8 D_8007CBFC;


void func_80046EC0(void) {
    D_8007CA1C = (s16) D_8007CBFC;
    D_8007CA1E = D_8007CBF8;
}
