#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8004F918(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        func_8004F568(arg0, arg1);
        return;
    }
    func_8004F834(arg0, arg1);
}
