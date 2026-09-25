#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80032F50(s32 arg0) {
    s32 temp_s0;

    temp_s0 = arg0 + 0x74;
    func_80021F70(temp_s0 + 0x1F, 0, 1);
    func_80021F70(temp_s0 + 0x20, 0, 2);
}
