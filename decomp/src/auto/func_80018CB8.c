#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007C798[];


void func_80018CB8(s32 arg0, s32 arg1) {
    u16 sp26;
    s32 temp_v0;

    temp_v0 = Reservar(0x4B0, (s32) D_8007C798);
    sp26 = func_8001B9C0(temp_v0, arg0);
    func_80029530(arg1, (s32) &sp26);
    func_80029530(arg1, temp_v0);
}
