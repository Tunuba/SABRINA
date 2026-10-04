#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006D304;
extern s32 D_8006D308;
extern s32 D_8006D310;
extern s32 D_8006D314;
extern s32 func_8002A5F8();


void func_8002B270(s32 arg0, s32 arg1, s32 arg2) {
    D_8006D308 = 0;
    D_8006D304 = 0;
    D_8006D314 = 0;
    D_8006D310 = 0;
    func_80016910(arg0, arg1, arg2);
    func_80016940(2, (s32) func_8002A5F8);
}
