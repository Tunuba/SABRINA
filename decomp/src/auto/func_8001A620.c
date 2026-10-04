#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8001A620(s32 arg0, s32 arg1, s32 arg2) {
    u16 sp18;
    u16 sp1A;
    s16 sp1C;
    s16 sp1E;

    sp18 = M2C_FIELD(arg0, u16 *, 0x12);
    sp1A = M2C_FIELD(arg0, u16 *, 0x14);
    sp1C = (s16) arg1;
    sp1E = M2C_FIELD(arg0, s16 *, 0xA);
    SubirAVRAM((s32) &sp18, arg2);
}
