#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_8003D094(void *arg0) {
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    M2C_FIELD(temp_s1, s32 *, 0x28) = 0;
    if ((p_sabrina != NULL) && (p_sabrina->forma.banderas & 1)) {
        sp24 = M2C_FIELD(arg0, s32 *, 0x24) - p_sabrina->x;
        sp28 = M2C_FIELD(arg0, s32 *, 0x28) - p_sabrina->y;
        sp2C = M2C_FIELD(arg0, s32 *, 0x2C) - p_sabrina->z;
        if ((u32) ((s32) M2C_FIELD(temp_s1, s32 *, 8) >> 8) >= func_8001C180((s32) &sp24)) {
            M2C_FIELD(arg0, M2C_UNK (**)(void *, Objeto *), 0x10)(arg0, p_sabrina);
        }
    }
}
