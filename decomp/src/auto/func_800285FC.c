#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006CFC4;
extern s32 D_8006D018[];

static M2C_UNK (*D_8006CF88)(s32, s32) = NULL;

void func_800285FC(s32 arg0) {
    M2C_UNK (*var_v0)(s32, s32);
    s32 temp_v1;
    s32 var_v1;
    s32 var_v1_2;
    u8 temp_a0;
    u8 temp_v1_2;
    void *var_a0;
    void *var_a0_2;

    if (M2C_FIELD(arg0, void **, 0xC) == NULL) {
        temp_a0 = M2C_FIELD(arg0, u8 *, 0x38);
        temp_v1 = temp_a0 & 0xFF;
        if (temp_v1 != 0) {
            if (D_8006D018[D_8006CFC4] != 0) {
                if (temp_v1 != 0x43) {
                    M2C_FIELD(arg0, u8 *, 0x37) = temp_a0;
                    M2C_FIELD(arg0, u8 *, 0x38) = 0U;
                }
            }
        } else {
            var_v1 = 0;
            var_a0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0xC) + 0x2C;
loop_6:
            if (((M2C_FIELD(var_a0, u8 *, 0xB) != 0x43) && (M2C_FIELD(var_a0, u8 *, 0xC) != 0x43)) || (*M2C_FIELD(var_a0, u8 **, 0) != 1)) {
                var_v1 += 1;
                var_a0 += 0xF0;
                if (var_v1 >= 4) {
                    goto block_10;
                }
                goto loop_6;
            }
        }
    } else {
block_10:
        if (*M2C_FIELD(arg0, u8 **, 0x3C) == 0xF3) {
            if ((M2C_FIELD(arg0, u8 *, 0xE8) != 0) && ((M2C_FIELD(arg0, u8 *, 0x46) != 0xFF) || (M2C_FIELD(arg0, u8 *, 0x49) == 2))) {
                if ((*M2C_FIELD(arg0, u8 **, 0x3C) == 0xF3) && (M2C_FIELD(arg0, u8 *, 0x49) == 2) && (M2C_FIELD(arg0, u8 *, 0xE8) != 8)) {
                    var_v0 = D_8006CF88;
                    goto block_36;
                }
                goto block_18;
            }
            goto block_33;
        }
block_18:
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x46);
        switch (temp_v1_2) {                        /* irregular */
        case 0x1:
            func_80027348(arg0, 1);
            return;
        case 0xFF:
            if (M2C_FIELD(arg0, u8 *, 0xE8) == 8) {
                var_a0_2 = M2C_FIELD(arg0, void **, 0xC);
                var_v1_2 = 0;
                if (var_a0_2 != NULL) {
loop_29:
                    var_v1_2 += 1;
                    if (M2C_FIELD(var_a0_2, u8 *, 0x46) != 1) {
                        var_a0_2 += 0xF0;
                        if (var_v1_2 >= 4) {
                            return;
                        }
                        goto loop_29;
                    }
                    func_800285FC((s32) var_a0_2);
                    return;
                }
            }
        case 0x0:
            return;
        case 0xFE:
            if (M2C_FIELD(arg0, u8 *, 0x49) != 2) {
block_33:
                func_80027348(arg0, 0);
                return;
            }
            M2C_FIELD(arg0, u8 *, 0x37) = 0U;
            break;
        default:
            var_v0 = M2C_FIELD(arg0, M2C_UNK (**)(s32, s32), 0x14);
            if (var_v0 != NULL) {
block_36:
                var_v0(arg0, arg0);
                return;
            }
            func_80026E48(arg0);
            break;
        }
    }
}
