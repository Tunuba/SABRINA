#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005DCD4(s32 arg0, s32 arg1) {
    s32 var_v0;
    s32 var_v0_2;

    if (arg1 & 1) {
        var_v0 = *arg0 & 0xF7FFFFFF;
    } else {
        var_v0 = *arg0 | 0x08000000;
    }
    *arg0 = var_v0;
    if (arg1 & 2) {
        var_v0_2 = *arg0 | 0x02000000;
    } else {
        var_v0_2 = *arg0 & 0xFDFFFFFF;
    }
    *arg0 = var_v0_2;
    func_8005D9C0(arg0, (s32) (u16) *arg0);
}
