#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80060B84[];
extern u8 D_8006379A[];


void func_80012C80(s32 arg0) {
    u8 temp_s0;

    temp_s0 = M2C_FIELD(D_8006379A, u8 *, 0);
    M2C_FIELD(D_8006379A, u8 *, 0) = (u8) arg0;
    if (arg0 & 0xFF) {
        D_80063794("SetGraphDebug:level:%d,type:%d reverse:%d\n\0\0SetGrapQue(%d)...\n\0\0DrawSyncCallback(%08x)...\n", M2C_FIELD(D_8006379A, u8 *, 0), M2C_FIELD(D_8006379A, u8 *, -2), M2C_FIELD(D_8006379A, u8 *, 1));
    }
}
