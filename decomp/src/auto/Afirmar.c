#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800653D0[];


void Afirmar(s32 arg0) {
    if (arg0 == 0) {
        printf((s32) "Assertion failed: file \"%s\", line %d\n");
        exit();
    }
}
