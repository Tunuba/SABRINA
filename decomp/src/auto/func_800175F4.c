#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_80084C2C;
extern s16 D_80084C2E;

void func_800175F4(void) {
    func_800177B4();
    SetFarColor(0, 0, 0);
    func_80017B5C(0, 0);
    D_80084C2E = 0;
    D_80084C2C = 0;
}
