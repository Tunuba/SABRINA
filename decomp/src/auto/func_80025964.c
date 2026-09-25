#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8008AF88[];
extern u8 D_8008AFD8[];
extern s32 D_8007CB44;


void func_80025964(void) {
    memset((s32) D_8008AFD8, 0, 0x5A00);
    memset((s32) D_8008AF88, 0, 0x50);
    D_8007CB44 = 0;
}
