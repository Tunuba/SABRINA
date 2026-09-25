#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



u8 func_80027F4C(void *arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_v1;
    s32 var_a1;
    s32 var_v1;
    u8 *var_v0_2;
    u8 temp_v0;
    u8 temp_v1_2;
    u8 var_v0;
    void *var_a0;

    var_a0 = arg0;
    temp_v0 = M2C_FIELD(var_a0, u8 *, 0x45);
    temp_a2 = temp_v0 - 3;
    if (arg1 != 0) {
        var_v1 = temp_a2;
        if (temp_a2 < 0) {
            var_v1 = temp_v0 + 4;
        }
        temp_v1 = var_v1 >> 3;
        var_a1 = (temp_a2 - (temp_v1 * 8)) - 2;
        var_a0 = M2C_FIELD(var_a0, s32 *, 0xC) + (temp_v1 * 0xF0);
    } else {
        var_a1 = temp_a2;
    }
    temp_v1_2 = M2C_FIELD(var_a0, u8 *, 0x37);
    if (var_a1 >= 0) {
        switch (temp_v1_2) {                        /* irregular */
        case 0x0:
            if ((var_a1 >= 6) || (var_v0 = 0, (M2C_FIELD((var_a0 + var_a1), u8 *, 0x57) != 0))) {
                var_v0 = 0;
                if (var_a1 < (s32) M2C_FIELD(var_a0, u8 *, 0x34)) {
                    var_v0_2 = M2C_FIELD(var_a0, s32 *, 0x28) + var_a1;
block_13:
                    return *var_v0_2;
                }
            }
            /* Duplicate return node #21. Try simplifying control flow for better match */
            return var_v0;
        case 0x4D:
            var_v0 = 0xFF;
            if (var_a1 < (s32) M2C_FIELD(var_a0, u8 *, 0x36)) {
                var_v0_2 = M2C_FIELD(var_a0, s32 *, 0x2C) + var_a1;
                goto block_13;
            }
            /* Duplicate return node #21. Try simplifying control flow for better match */
            return var_v0;
        default:
            var_v0 = 0;
            if (var_a1 < (s32) M2C_FIELD(var_a0, u8 *, 0x36)) {
                var_v0_2 = M2C_FIELD(var_a0, s32 *, 0x2C) + var_a1;
                goto block_13;
            }
            /* Duplicate return node #21. Try simplifying control flow for better match */
            return var_v0;
        }
    } else {
        var_v0 = 0;
        if ((var_a1 + 2) == 0) {
            var_v0 = 0x42;
            if (temp_v1_2 != 0) {
                var_v0 = temp_v1_2 & 0xFF;
            }
        }
        return var_v0;
    }
}
