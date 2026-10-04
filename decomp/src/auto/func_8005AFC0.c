#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005AFC0(s32 arg0, s32 arg1) {
    func_80048468(arg0, arg1);
    if (M2C_FIELD(arg1, u16 *, 0x22) == 1) {
        M2C_FIELD(arg0, s16 *, 0x70) = 1;
    }
}
