#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8002FFB8(s32 arg0) {
    func_8002EC1C();
    func_8002F298();
    switch (arg0) {
    case 1:
    case 2:
    case 3:
        func_8002F780();
        return;
    case 4:
    case 5:
    case 6:
        func_8002F524();
        return;
    case 7:
    case 8:
    case 9:
        func_8002F9A0();
        return;
    case 10:
    case 11:
    case 12:
        func_8002FBFC();
        return;
    case 14:
        func_8002FE64();
        return;
    case 13:
        func_8002FF1C();
        /* fallthrough */
    default:
        return;
    }
}
