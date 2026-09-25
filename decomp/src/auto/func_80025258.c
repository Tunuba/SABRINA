#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80025258(s32 arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x60) != 0) {
        func_800206E8();
        func_8001E230(M2C_FIELD(arg0, s32 *, 0x60));
        M2C_FIELD(arg0, s32 *, 0x60) = 0;
    }
}
