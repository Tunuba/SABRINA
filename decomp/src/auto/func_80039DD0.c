#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80039DD0(s32 arg0, s32 arg1) {
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5_2;
    s32 temp_v0;
    s32 var_v0;
    void *temp_t5;

    temp_t5 = M2C_FIELD(arg0, void **, 0);
    temp_t3 = (s32) M2C_FIELD(temp_t5, s32 *, 0) >> 8;
    temp_t4 = (s32) M2C_FIELD(temp_t5, s32 *, 4) >> 8;
    temp_v0 = (s32) M2C_FIELD(arg0, s32 *, 8) >> 8;
    temp_t5_2 = (s32) M2C_FIELD(temp_t5, s32 *, 8) >> 8;
    if ((temp_t3 + temp_v0) < ((s32) M2C_FIELD(arg1, s32 *, 4) >> 8)) {
        return 0;
    }
    if (((s32) M2C_FIELD(arg1, s32 *, 0x10) >> 8) < (temp_t3 - temp_v0)) {
        return 0;
    }
    if ((temp_t5_2 + temp_v0) < ((s32) M2C_FIELD(arg1, s32 *, 0xC) >> 8)) {
        return 0;
    }
    if (((s32) M2C_FIELD(arg1, s32 *, 0x18) >> 8) < (temp_t5_2 - temp_v0)) {
        return 0;
    }
    if (((s32) M2C_FIELD(arg1, s32 *, 0x14) >> 8) < (temp_t4 - ((s32) M2C_FIELD(arg0, s32 *, 4) >> 8))) {
        return 0;
    }
    var_v0 = 1;
    if (temp_t4 < ((s32) M2C_FIELD(arg1, s32 *, 8) >> 8)) {
        var_v0 = 0;
    }
    return var_v0;
}
