#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_8007CC18;
extern s32 D_8007CC1C;


void func_8004CA4C(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    D_8007CC18 = 0;
    D_8007CC1C = 0;
}
