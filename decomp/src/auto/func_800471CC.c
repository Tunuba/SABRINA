#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA1E;


void func_800471CC(void) {
    D_8007CA1E = 0;
    func_8004C82C();
    func_8004ED5C();
}
