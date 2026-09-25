#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006CFEC;

static s32 (*D_8006CF9C)() = NULL;

void func_80027368(void *arg0) {
    D_8006CFEC = D_8006CF9C();
    *M2C_FIELD(arg0, s8 **, 0x3C) = 0;
    func_8002622C((s32) arg0, -2);
}
