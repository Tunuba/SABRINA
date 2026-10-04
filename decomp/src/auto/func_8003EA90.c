#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003EA90(void) {
    s32 sp0;
    s32 sp4;

    sp4 = 0xD;
    sp0 = 0;
loop_2:
    if (sp0 < 0x3C) {
        sp4 *= 0xD;
        sp0 += 1;
        goto loop_2;
    }
}
