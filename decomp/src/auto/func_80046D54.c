#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA1C;
extern u16 D_8007CA1E;
extern u16 D_8007CBFA;
extern u8 D_8007CBFD;


void func_80046D54(void) {
    D_8007CA1C = (s16) D_8007CBFD;
    D_8007CA1E = D_8007CBFA;
}
