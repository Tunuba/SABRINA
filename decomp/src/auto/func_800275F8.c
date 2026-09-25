#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006CFB8;
extern s32 D_8006CFC4;
extern s32 D_8006CFDC[];
extern s32 D_8006CFE4;
extern void * D_8006CFE8;
extern s32 D_8006CFF0;

static M2C_UNK (*D_8006CF84)(M2C_UNK) = NULL;
static s32 (*D_8006CF8C)(void *, s32) = NULL;
static M2C_UNK (*D_8006CF90)(s32) = NULL;
static M2C_UNK (*D_8006CFA4)(s32) = NULL;
static M2C_UNK (*D_8006CFA8)(s32) = NULL;

s32 func_800275F8(void *arg0) {
    s32 *temp_s2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    u8 temp_v1_2;

    if (D_8006CFF0 != 0) {
        D_8006CF90();
    }
    temp_s4 = D_8006CFF0;
    var_s0 = -1;
    if (temp_s4 != 0) {
        var_s2 = -0xF0;
loop_4:
        temp_v0 = D_8006CFE4 - 1;
        D_8006CFE4 = temp_v0;
        if (temp_v0 > 0) {
            if (var_s0 >= 0) {
                D_8006CF90(M2C_FIELD(arg0, s32 *, 0xC) + var_s2);
            }
            var_v0 = func_8002643C((s32) arg0, D_8006CF8C(arg0, 1) & 0xFF);
            if (var_v0 >= 0) {
                func_8002908C(0x3C);
                var_s0 += 1;
                if (func_800266B4() != 0) {
                    var_s2 += 0xF0;
                    if (var_s0 >= 4) {
                        goto block_10;
                    }
                    goto loop_4;
                }
                goto block_27;
            }
            /* Duplicate return node #36. Try simplifying control flow for better match */
            return var_v0;
        }
        goto block_10;
    }
block_10:
    var_s0_2 = 0;
    temp_a0 = D_8006CFC4 == 0;
    if (D_8006CFE4 >= 2) {
        temp_s2 = &D_8006CFDC[temp_a0];
        temp_s3 = temp_a0 * 0xF0;
loop_12:
        temp_a0_2 = *temp_s2;
        if (temp_a0_2 >= 0) {
            if (temp_a0_2 > 0) {
                var_s0_2 = (M2C_FIELD((temp_s3 + D_8006CFB8), s32 *, 0xC) + (temp_a0_2 * 0xF0)) - 0xF0;
                D_8006CFA4(var_s0_2);
            }
            temp_v1 = *temp_s2;
            if (temp_v1 != 3) {
                if (temp_v1 < 4) {
                    if ((temp_v1 < 2) && (temp_v1 >= 0)) {
                        var_s0_2 = D_8006CFB8 + temp_s3;
                        D_8006CFA4(var_s0_2);
                        D_8006CFA8(var_s0_2);
                        var_v0_2 = -1;
                        goto block_24;
                    }
                } else if (temp_v1 == 4) {
                    *temp_s2 = 3;
                }
            } else {
                D_8006CFA4(var_s0_2 - 0xF0);
                var_v0_2 = 1;
block_24:
                *temp_s2 = var_v0_2;
            }
            var_v0 = func_8002622C((s32) arg0, D_8006CF8C(arg0, temp_s4) & 0xFF);
            if (var_v0 >= 0) {
                func_8002908C(0x3C);
                if (func_800266B4() == 0) {
block_27:
                    return -3;
                }
                temp_v0_2 = D_8006CFE4 - 1;
                D_8006CFE4 = temp_v0_2;
                if (temp_v0_2 < 2) {
                    goto block_29;
                }
                goto loop_12;
            }
            /* Duplicate return node #36. Try simplifying control flow for better match */
            return var_v0;
        }
        goto block_29;
    }
block_29:
    temp_v0_3 = D_8006CFE4 - 1;
    D_8006CFE4 = temp_v0_3;
    if (temp_v0_3 > 0) {
loop_31:
        var_v0 = func_8002622C((s32) arg0, D_8006CF8C(arg0, temp_s4) & 0xFF);
        if ((var_v0 >= 0) && ((M2C_FIELD(D_8006CFE8, u16 *, 0xE) == 0x22) || (func_8002908C(0x3C), var_v0 = -3, (func_800266B4() != 0)))) {
            temp_v0_4 = D_8006CFE4 - 1;
            D_8006CFE4 = temp_v0_4;
            if (temp_v0_4 <= 0) {
                goto block_35;
            }
            goto loop_31;
        }
    } else {
block_35:
        func_80026744();
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x44);
        M2C_FIELD(arg0, u8 *, 0x44) = (u8) (temp_v1_2 + 1);
        *(temp_v1_2 + M2C_FIELD(arg0, s32 *, 0x3C)) = M2C_FIELD(D_8006CFE8, u8 *, 0);
        D_8006CF84(0);
        var_v0 = 0;
    }
    return var_v0;
}
