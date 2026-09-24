#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CA8C;
extern s32 D_8007CA94;
extern s32 * D_8007CA98;


void func_8001F300(void) {
    if (D_8007CA98 != NULL) {
        *D_8007CA98 = D_8007CA8C;
        D_8007CA98 = NULL;
        D_8007CA8C = D_8007CA94;
        D_8007CA94 = 0;
    }
}
