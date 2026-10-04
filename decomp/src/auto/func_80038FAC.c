#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80038FAC(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s16 *, 0x112) = (s16) (M2C_FIELD(arg1, s16 *, 0x112) & 0x7FFF);
    if (M2C_FIELD(arg1, s32 *, 0x60) != 0) {
        func_800206E8();
        func_8001E230(M2C_FIELD(arg1, s32 *, 0x60));
    }
    M2C_FIELD(arg1, s32 *, 0x60) = (s32) M2C_FIELD((arg0 + 0x74), s32 *, 0x40);
    M2C_FIELD(arg1, s32 *, 0x11C) = 0;
    func_800399E8(arg0, (s32) arg1);
    M2C_FIELD(arg0, s8 *, 0x20) = 0x80;
}
