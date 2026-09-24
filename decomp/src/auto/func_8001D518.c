#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CA48;
extern s32 D_8007CBCC;
extern s32 D_8007CBD0;


void func_8001D518(void) {
    Liberar(D_8007CA48);
    Liberar(D_8007CBCC);
    Liberar(D_8007CBD0);
}
