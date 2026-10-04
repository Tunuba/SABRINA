#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074EDC;


void func_8003FD68(s32 arg0) {
    if (arg0 == 1) {
        D_80074EDC = 0;
        return;
    }
    D_80074EDC = 1;
}
