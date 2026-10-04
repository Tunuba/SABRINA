#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800224B8(s32 arg0) {
    s32 sp1C;
    s32 sp20;
    s32 sp24;

    sp1C = func_80021CE4(0x2000) - 0x1000;
    sp24 = func_80021CE4(0x2000) - 0x1000;
    sp20 = -func_80021CE4(0x1000);
    func_8001C45C((s32) &sp1C);
    M2C_FIELD(arg0, s32 *, 0) = sp1C;
    M2C_FIELD(arg0, s32 *, 4) = sp20;
    M2C_FIELD(arg0, s32 *, 8) = sp24;
}
