#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800522E4(s32 arg0) {
    ChangeClearPAD();
    func_800143E4();
    if (func_80014A6C() == 0) {

    }
    InitCARD2();
    func_800522B0();
    func_800521AC();
    func_80052240();
    func_800143F4();
}
