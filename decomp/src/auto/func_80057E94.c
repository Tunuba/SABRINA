#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80057E94(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s1 = func_80021CE4(0x1000) << 0x11;
    temp_s0 = func_80021CE4(0x1000) << 0x11;
    CrearParticula(3, arg0, 0, temp_s1, /* extra? */ 0, /* extra? */ temp_s0, /* extra? */ 0, /* extra? */ ((func_80021CE4(0x32) << 7) & 0xFFFF), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x41, /* extra? */ 2, /* extra? */ 0);
}
