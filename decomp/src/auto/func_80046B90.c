#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA1E;
extern s16 D_8007CA20;
extern s8 D_8007CA38;
extern s16 D_8007CBFE;


void func_80046B90(void) {
    D_8007CA38 = 0;
    D_8007CA20 = 0;
    D_8007CBFE = 0x14;
    D_8007CA1E = 0;
    func_8003DDFC();
}
