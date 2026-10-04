#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80037DE0();


void func_80037DBC(s32 (**arg0)(s32), s32 arg1) {
    if (arg1 == p_sabrina) {
        *arg0 = func_80037DE0;
    }
}
