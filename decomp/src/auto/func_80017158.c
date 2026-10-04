#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_80084BAC;

void func_80017158(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4_reg) {
    u16 arg4 = (u16) arg4_reg;
    s32 temp_s0;
    s32 temp_s1;

    temp_s1 = arg0 & 0xFFFF;
    temp_s0 = arg1 & 0xFFFF;
    func_80016E1C(temp_s1, temp_s0, arg2 & 0xFFFF, arg3 & 0xFFFF, /* extra? */ (s32) arg4);
    func_800175F4();
    D_80084BAC = 0;
    func_80016F38(temp_s1, temp_s0);
    GsSetDrawBuffClip();
    GsSetDrawBuffOffset();
}
