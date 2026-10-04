#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_800605C8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_s2;
    s32 temp_s4;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    void *temp_a0;

    temp_a0 = *arg2;
    temp_s2 = M2C_FIELD(arg1, s32 *, 0);
    sp2C = M2C_FIELD(temp_a0, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x24);
    sp30 = M2C_FIELD(temp_a0, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x28);
    sp34 = M2C_FIELD(temp_a0, s32 *, 8) - M2C_FIELD(arg0, s32 *, 0x2C);
    temp_s4 = func_8001C0D0(sp2C, sp30, sp34);
    func_8001C45C((s32) &sp2C);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) + ((s32) (sp2C * temp_s2) >> 0xC));
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (M2C_FIELD(arg0, s32 *, 0x3C) + ((s32) (sp30 * temp_s2) >> 0xC));
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + ((s32) (sp34 * temp_s2) >> 0xC));
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x38);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (temp_v1 - (temp_v1 >> 1));
    temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x3C);
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (temp_v1_2 - (temp_v1_2 >> 1));
    temp_v1_3 = M2C_FIELD(arg0, s32 *, 0x40);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (temp_v1_3 - (temp_v1_3 >> 1));
    if (temp_s4 < 0x8000) {
        if (M2C_FIELD(arg1, s8 *, 5) >= 0) {
            var_v0 = func_80060558((s32) *arg2);
        } else {
            var_v0 = func_80060590((s32) *arg2);
        }
        *arg2 = (void *) var_v0;
        if (*arg2 == NULL) {
            return 8;
        }
        goto block_6;
    }
block_6:
    return 0;
}
