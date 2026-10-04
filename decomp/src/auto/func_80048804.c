#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_80048804(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_v0;

    if ((func_8002EFD0(arg0) != 0) && (func_80048710(arg2, arg3) != 0)) {
        sp2C = p_sabrina->x;
        sp30 = p_sabrina->y;
        sp34 = p_sabrina->z;
        temp_v0 = func_8002225C(arg0, sp2C, sp30, sp34);
        if (temp_v0 < 0x58001) {
            M2C_FIELD(arg0, s16 *, 0x70) = 7;
            return;
        }
        if (temp_v0 >= 0xF0001) {
            if (arg1 & 2) {
                goto block_9;
            }
            if (arg1 & 1) {
                M2C_FIELD(arg0, s16 *, 0x70) = 2;
                return;
            }
block_9:
            M2C_FIELD(arg0, s16 *, 0x70) = 0;
        }
    }
}
