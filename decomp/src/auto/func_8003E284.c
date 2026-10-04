#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80074E98;


void func_8003E284(void) {
    *D_80074E98 = (*D_80074E98 & 0xF0FFFFFF) | 0x20000000;
}
