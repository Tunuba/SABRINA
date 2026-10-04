#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CB78;
extern void * D_8007CB8C;


void func_800318D4(void) {
    M2C_FIELD(D_8007CB8C, u8 *, 0x20) = (u8) (M2C_FIELD(D_8007CB8C, u8 *, 0x20) | 0x80);
    D_8007CB78 = 0;
}
