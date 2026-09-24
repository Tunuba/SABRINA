#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80063750;
extern s32 * D_80063754;
extern s32 ** D_80063758;
extern s32 * D_8006375C;
extern s32 * D_80063760;
extern s16 D_8006379C;
extern s16 D_8006379E;


s32 func_80011D9C(void *arg0, s32 *arg1) {
    s16 temp_a1;
    s16 temp_a1_2;
    s32 *var_s2;
    s32 temp_a0;
    s32 temp_s0;
    s32 temp_v1;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    u16 var_a0;
    u16 var_a0_2;

    var_s2 = arg1;
    func_800128CC();
    temp_a1 = M2C_FIELD(arg0, s16 *, 4);
    var_a0 = (u16) M2C_FIELD(arg0, s16 *, 4);
    if (temp_a1 >= 0) {
        if (D_8006379C < temp_a1) {
            var_a0 = (u16) D_8006379C;
        }
    } else {
        var_a0 = 0;
    }
    temp_a1_2 = M2C_FIELD(arg0, s16 *, 6);
    M2C_FIELD(arg0, s16 *, 4) = (s16) var_a0;
    if (temp_a1_2 >= 0) {
        var_a0_2 = (u16) M2C_FIELD(arg0, s16 *, 6);
        var_v0_2 = var_a0_2 << 0x10;
        if (D_8006379E < temp_a1_2) {
            var_a0_2 = (u16) D_8006379E;
            goto block_8;
        }
    } else {
        var_a0_2 = 0;
block_8:
        var_v0_2 = var_a0_2 << 0x10;
    }
    M2C_FIELD(arg0, s16 *, 6) = (s16) var_a0_2;
    temp_v1 = (M2C_FIELD(arg0, s16 *, 4) * (var_v0_2 >> 0x10)) + 1;
    temp_a0 = temp_v1 / 2;
    temp_s0 = temp_v1 >> 5;
    if (temp_a0 <= 0) {
        return -1;
    }
    if (!(*D_80063754 & 0x04000000)) {
loop_13:
        var_v0 = -1;
        if (func_80012900() == 0) {
            if (*D_80063754 & 0x04000000) {
                goto block_15;
            }
            goto loop_13;
        }
    } else {
block_15:
        *D_80063754 = 0x04000000;
        *D_80063750 = 0x01000000;
        *D_80063750 = 0xC0000000;
        *D_80063750 = M2C_FIELD(arg0, s32 *, 0);
        *D_80063750 = (s32) M2C_FIELD(arg0, s16 *, 4);
        if (!(*D_80063754 & 0x08000000)) {
loop_17:
            var_v0 = -1;
            if (func_80012900() == 0) {
                if (*D_80063754 & 0x08000000) {
                    goto block_19;
                }
                goto loop_17;
            }
        } else {
block_19:
            var_s0 = (temp_a0 - (temp_s0 * 0x10)) - 1;
            if (var_s0 != -1) {
                do {
                    var_s0 -= 1;
                    *var_s2 = *D_80063750;
                    var_s2 += 4;
                } while (var_s0 != -1);
            }
            if (temp_s0 != 0) {
                *D_80063754 = 0x04000003;
                *D_80063758 = var_s2;
                *D_8006375C = (temp_s0 << 0x10) | 0x10;
                *D_80063760 = 0x01000200;
            }
            var_v0 = 0;
        }
    }
    return var_v0;
}
