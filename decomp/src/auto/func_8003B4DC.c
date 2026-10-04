#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003B4DC(void *arg0, void *arg1) {
    s16 temp_a2;
    void *temp_a3;

    temp_a3 = arg0 + 0x74;
    if (M2C_FIELD(arg1, s16 *, 0x112) & 3) {
        temp_a2 = M2C_FIELD(temp_a3, s16 *, 0x14);
        if ((temp_a2 < 5) && ((M2C_FIELD(arg0, s32 *, 0x28) + 0x10000) < M2C_FIELD(arg1, s32 *, 0x28))) {
            M2C_FIELD(temp_a3, s16 *, 0x14) = (s16) (temp_a2 + 1);
            *(temp_a3 + (temp_a2 * 4)) = arg1;
        }
    }
}
