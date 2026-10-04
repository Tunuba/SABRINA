#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005E9FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;

    temp_s2 = func_80021CE4(0x1999) - 0xCCC;
    temp_s1 = func_80021CE4(0x1999) - 0xCCC;
    temp_v0 = CrearParticula(0x12, arg0, (s32) (s16) (func_80021CE4(arg3) - (arg3 >> 1)), 0, /* extra? */ 0, /* extra? */ arg1, /* extra? */ temp_s2, /* extra? */ arg2, /* extra? */ temp_s1, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x1E, /* extra? */ 2, /* extra? */ 0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 0x24) = 0x10000;
    }
}
