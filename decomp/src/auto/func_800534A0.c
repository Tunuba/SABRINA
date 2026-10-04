#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086324[];
extern s32 D_8007CA24;


void func_800534A0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x74) = 0;
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    *(D_80086324 + (D_8007CA24 * 4)) = arg0;
    D_8007CA24 += 1;
}
