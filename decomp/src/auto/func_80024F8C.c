#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80024F8C(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 0x1C) != 0) && (M2C_FIELD(arg0, s32 *, 0x60) != 0)) {
        func_8002ED4C((s32) arg0);
        func_8002EF8C((s32) arg0);
        func_8002EDC8((s32) arg0);
        func_8001E998((s32) arg0);
    }
    func_8001E588((s32) arg0);
}
