#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8004A3B4(s32 arg0, s32 arg1, s32 arg2) {
    s8 temp_v0;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    if (arg2 != 0) {
        M2C_FIELD(temp_s1, s8 *, 5) = 2;
    }
    M2C_FIELD(temp_s1, s32 *, 0xC) = 0;
    temp_v0 = M2C_FIELD(temp_s1, s8 *, 5);
    if (temp_v0 != 0) {
        if (temp_v0 == 1) {
            func_800249CC(arg0, 0x2A);
        } else {
            func_800249CC(arg0, -1);
            M2C_FIELD(temp_s1, s32 *, 0xC) = CrearParticula(0x1D, arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
            M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0xC), s16 *, 0x40) = 3;
        }
    } else {
        func_800249CC(arg0, 0x2B);
    }
    func_800483F8(arg0);
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + 0xFFFED99A);
}
