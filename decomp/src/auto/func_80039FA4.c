#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80039FA4(s32 arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_v1;
    void *temp_t0;
    void *temp_t2;

    temp_t0 = M2C_FIELD(arg1, void **, 0);
    temp_t2 = M2C_FIELD(arg0, void **, 0);
    temp_v1 = M2C_FIELD(temp_t0, s32 *, 4);
    temp_t1 = (s32) (M2C_FIELD(temp_t2, s32 *, 8) - M2C_FIELD(temp_t0, s32 *, 8)) >> 8;
    temp_v0 = M2C_FIELD(temp_t2, s32 *, 4);
    temp_a2 = (s32) (M2C_FIELD(temp_t2, s32 *, 0) - M2C_FIELD(temp_t0, s32 *, 0)) >> 8;
    if (((s32) (M2C_FIELD(arg0, s32 *, 0xC) + M2C_FIELD(arg1, s32 *, 0xC)) >> 8) >= (((s32) (temp_a2 * temp_a2) >> 8) + ((s32) (temp_t1 * temp_t1) >> 8))) {
        if (((temp_v0 >> 8) < ((s32) (temp_v1 - M2C_FIELD(arg1, s32 *, 4)) >> 8)) || ((temp_v1 >> 8) < ((s32) (temp_v0 - M2C_FIELD(arg0, s32 *, 4)) >> 8))) {
            goto block_5;
        }
        return 1;
    }
block_5:
    return 0;
}
