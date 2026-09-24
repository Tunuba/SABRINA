#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8001FC5C(s32 arg0) {
    s16 temp_t0;
    s16 temp_t1;
    s16 temp_t2;
    s16 temp_t3;
    s16 temp_t4;
    s16 temp_t5;

    temp_t0 = M2C_FIELD(arg0, s16 *, 8);
    temp_t1 = M2C_FIELD(arg0, s16 *, 0x14);
    temp_t2 = M2C_FIELD(arg0, s16 *, 0x20);
    if (((temp_t0 >= 0) || (temp_t1 >= 0) || (temp_t2 > 0)) && ((temp_t0 < 0x200) || (temp_t1 < 0x200) || (temp_t2 <= 0x200)) && ((temp_t3 = M2C_FIELD(arg0, s16 *, 0xA), temp_t4 = M2C_FIELD(arg0, s16 *, 0x16), temp_t5 = M2C_FIELD(arg0, s16 *, 0x22), (temp_t3 >= 0)) || (temp_t4 >= 0) || (temp_t5 > 0)) && ((temp_t3 < 0xDC) || (temp_t4 < 0xDC) || (temp_t5 <= 0xDC))) {
        return 0;
    }
    return 1;
}
