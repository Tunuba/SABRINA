#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80068860[];


void func_8001E2DC(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_v0 != 0) {
        Liberar(temp_v0);
        M2C_FIELD(arg0, s32 *, 0) = 0;
    }
    if (arg1 != 0) {
        M2C_FIELD(arg0, s32 *, 0) = Reservar(func_800150F0(arg1) + 1, (s32) "Object.c");
        strcpy(M2C_FIELD(arg0, s32 *, 0), arg1);
        M2C_FIELD(arg0, u8 *, 0x64) = (u8) (M2C_FIELD(arg0, u8 *, 0x64) | 4);
    }
}
