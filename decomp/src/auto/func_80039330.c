#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80039330(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    M2C_FIELD(arg0, s8 *, 0x119) = 0xA;
    M2C_FIELD(arg0, s16 *, 0xA6) = 0;
    func_8002244C((s32) arg0);
}
