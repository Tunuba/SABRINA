#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007CCBC[];
extern u8 D_8007CD88[];


void func_800219C8(void) {
    func_8001321C((s32) D_8007CD88);
    func_8001315C((s32) D_8007CCBC);
}
