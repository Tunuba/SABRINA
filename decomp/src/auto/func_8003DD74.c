#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007C8C0;
extern s16 D_8007C8C2;


void func_8003DD74(s32 arg0_reg) {
    s16 arg0 = (s16) arg0_reg;
    D_8007C8C0 = arg0;
    D_8007C8C2 = arg0 & 0xFFFF;
}
