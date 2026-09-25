#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003D00C(void *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x70) = 1;
        return;
    case 2:
        func_80048754((s32) arg0, (s32) (arg0 + 0x74 + 0x1C), 0, 0);
        return;
    case 3:
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        return;
    default:
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        /* fallthrough */
    case 1:
        return;
    }
}
