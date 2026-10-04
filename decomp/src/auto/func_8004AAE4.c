#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_8004AAE4(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) p_sabrina->x;
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (p_sabrina->y + 0xFFFD0000);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) p_sabrina->z;
}
