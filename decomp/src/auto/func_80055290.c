#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80055290(void *arg0, void *arg1) {
    if (M2C_FIELD(arg1, u16 *, 0x22) == 5) {
        M2C_FIELD((arg0 + 0x74), s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x74);
        M2C_FIELD(arg0, s16 *, 0x114) = 0;
        M2C_FIELD(arg0, s16 *, 0x112) = 0;
    }
}
