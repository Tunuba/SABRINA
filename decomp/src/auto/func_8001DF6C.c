#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_80068840[];
extern void * D_8007CA70;
extern s32 D_8007CA78;


void func_8001DF6C(void) {
    s32 temp_a2;
    s32 temp_a3;

    temp_a2 = -(M2C_FIELD(D_8007CA70, u8 *, 0x22) - M2C_FIELD(D_8007CA70, u8 *, 0x26));
    temp_a3 = -(M2C_FIELD(D_8007CA70, u8 *, 0x23) - M2C_FIELD(D_8007CA70, u8 *, 0x27));
    M2C_FIELD(D_8007CA70, s32 *, 0x34) = func_8001BE8C(0, 0, temp_a2, temp_a3);
    M2C_FIELD(D_8007CA70, s32 *, 0x38) = func_8001BF8C(0, 0, temp_a2, temp_a3);
    if (M2C_FIELD(D_8007CA70, s32 *, 0x38) >= 0x51) {
        D_8007CA78 |= D_80068840[(s32) M2C_FIELD(D_8007CA70, s32 *, 0x34) >> 8];
    }
}
