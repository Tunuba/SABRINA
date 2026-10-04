#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D52D4;

void func_80050C40(void) {
    if (D_800D52D4 >= 0) {
        close();
        D_800D52D4 = -1;
    }
}
