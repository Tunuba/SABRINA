#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8004E32C(s32 arg0, s32 arg1) {
    s32 *temp_v0_4;
    s32 temp_a0;
    s32 temp_s5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;
    u32 var_s1_2;
    u32 var_s4;
    void **temp_v0_3;

    var_s4 = (arg1 + 0xB) & ~3;
    if (var_s4 < 0x10U) {
        var_s4 = 0x10;
    }
    temp_v0 = func_8004E2A4((s32) var_s4);
    if (temp_v0 >= 0x38) {
        return 0;
    }
    var_s0_2 = func_8004E774(arg0, temp_v0 + 1);
    if (var_s0_2 != 0) {
        func_8004E7FC(arg0, var_s0_2, (s32) var_s4);
    } else {
        if (M2C_FIELD(arg0, u8 *, 0x100) != 0) {
            var_s1 = 0;
loop_9:
            temp_v0_2 = func_8004E774(arg0, temp_v0);
            var_s0_2 = temp_v0_2;
            if (temp_v0_2 != 0) {
                if ((u32) M2C_FIELD(var_s0_2, u32 *, 0) >= var_s4) {

                } else {
                    M2C_FIELD(var_s0_2, s32 *, 4) = var_s1;
                    var_s1 = var_s0_2;
                    goto loop_9;
                }
            }
loop_13:
            temp_s5 = M2C_FIELD(var_s1, s32 *, 4);
            if (var_s1 != 0) {
                func_8004E86C(arg0, var_s1, temp_v0);
                var_s1 = temp_s5;
                goto loop_13;
            }
            if (var_s0_2 != 0) {
                func_8004E7FC(arg0, var_s0_2, (s32) var_s4);
            }
        }
        if (var_s0_2 == 0) {
            var_s1_2 = var_s4 + 8;
            if (var_s1_2 < 0x20000U) {
                var_s1_2 = 0x20000;
            }
            temp_v0_3 = M2C_FIELD(arg0, void ***, 0);
            if (temp_v0_3 != NULL) {
                var_v0 = M2C_FIELD(*temp_v0_3, s32 (**)(void **, u32), 0xC)(temp_v0_3, var_s1_2);
            } else {
                var_v0 = func_80017CBC((s32) var_s1_2);
            }
            var_s0_2 = var_v0;
            if (var_s0_2 != 0) {
                Afirmar((var_s0_2 & 3) == 0);
                temp_v0_4 = M2C_FIELD(arg0, s32 **, 0xF4);
                if ((temp_v0_4 != NULL) && (var_s0_2 != (temp_v0_4 + 4))) {
                    *temp_v0_4 = (var_s0_2 - temp_v0_4) + 4 + 1;
                    temp_a0 = *temp_v0_4;
                    var_s0_2 += 4;
                    M2C_FIELD((temp_v0_4 + temp_a0), M2C_UNK *, -2) = M2C_UNALIGNED32(temp_a0);
                    var_v0_2 = var_s1_2 - 7;
                    goto block_29;
                }
                if (temp_v0_4 != NULL) {
                    var_s0_2 = (s32) temp_v0_4;
                    *temp_v0_4 = var_s1_2 + 1;
                } else {
                    var_s0_2 += 4;
                    var_v0_2 = var_s1_2 - 7;
block_29:
                    *var_s0_2 = var_v0_2;
                }
                temp_v1 = *var_s0_2;
                M2C_FIELD((var_s0_2 + temp_v1), M2C_UNK *, -2) = M2C_UNALIGNED32(temp_v1);
                M2C_FIELD(arg0, s32 **, 0xF4) = (s32 *) ((var_s0_2 + *var_s0_2) - 1);
                if (M2C_FIELD(arg0, s32 *, 0xF0) == 0) {
                    M2C_FIELD(arg0, s32 *, 0xF0) = var_s0_2;
                }
                func_8004E7FC(arg0, var_s0_2, (s32) var_s4);
            }
        }
    }
    if (var_s0_2 != 0) {
        var_s0 = var_s0_2 + 4;
        M2C_FIELD(arg0, s32 *, 0xFC) = (s32) (M2C_FIELD(arg0, s32 *, 0xFC) + *var_s0_2);
    } else {
        var_s0 = 0;
    }
    Afirmar((var_s0 & 3) == 0);
    return var_s0;
}
