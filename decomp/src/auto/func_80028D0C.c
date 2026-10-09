#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_800285FC();
extern s32 func_8002886C();
extern s32 func_80028C54();

extern void (*D_8006CF9C)(s32);
extern s32 (*D_8006CFA0)(s32);
extern s32 (*D_8006CFA4)(s32);

void func_80028D0C(void) {
    D_8006CF9C = func_800285FC;
    D_8006CFA0 = func_80028C54;
    D_8006CFA4 = func_8002886C;
}
