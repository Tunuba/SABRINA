#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_80034710(s32 arg0) {
    if (func_8002225C(arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z) < 0x40001) {
        M2C_FIELD((arg0 + 0x74), Objeto **, 0x10) = (Objeto *) p_sabrina;
    }
}
