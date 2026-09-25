#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_8006CF6C;
extern void * D_8006CF70;
extern s32 D_8006CFC4;
extern s32 D_8006CFDC[];

static M2C_UNK (*D_8006CFA4)(s32, s32 *) = NULL;
static M2C_UNK (*D_8006CFA8)(s32) = NULL;

s32 func_80025EF8(s32 arg0) {
    s32 *temp_a1;
    s32 *temp_v1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_v0;
    u16 var_v1;

    M2C_FIELD(D_8006CF70, u16 *, 0xA) = 0x40U;
    M2C_FIELD(D_8006CF70, u16 *, 0xA) = 0U;
    M2C_FIELD(D_8006CF70, s16 *, 8) = 0xD;
    M2C_FIELD(D_8006CF70, s16 *, 0xE) = 0x88;
    var_a0 = 0x91;
    if (M2C_FIELD(arg0, u8 *, 0xE8) == 8) {
        var_a0 = 0x50;
    }
    func_8002908C(var_a0);
    var_v1 = 0x1003;
    if (D_8006CFC4 != 0) {
        var_v1 = 0x3003;
    }
    M2C_FIELD(D_8006CF70, u16 *, 0xA) = var_v1;
    temp_v0 = D_8006CFDC[D_8006CFC4];
    if (temp_v0 >= 0) {
        if (temp_v0 > 0) {
            do {
                temp_v1 = &D_8006CFDC[D_8006CFC4];
                temp_v0_2 = *temp_v1 - 1;
                *temp_v1 = temp_v0_2;
                D_8006CFA4(M2C_FIELD(arg0, s32 *, 0xC) + (temp_v0_2 * 0xF0));
            } while (D_8006CFDC[D_8006CFC4] > 0);
        }
        temp_a1 = &D_8006CFDC[D_8006CFC4];
        if (*temp_a1 == 0) {
            *temp_a1 = -1;
            D_8006CFA4(arg0, temp_a1);
            D_8006CFA8(arg0);
        }
    }
    if (M2C_FIELD(D_8006CF70, u16 *, 4) & 0x200) {
        M2C_FIELD(D_8006CF70, u16 *, 0xA) = (u16) (M2C_FIELD(D_8006CF70, u16 *, 0xA) | 0x10);
        if (M2C_FIELD(D_8006CF70, u16 *, 4) & 0x200) {
            do {

            } while (func_800290AC() == 0);
            M2C_FIELD(D_8006CF70, u8 *, 0) = 1U;
            func_8002908C(0x7D0);
            var_v0 = 0;
            if (func_800266B4() != 0) {
                func_80026744();
                func_8002908C(0x1AE);
loop_16:
                if (*D_8006CF6C & 0x80) {
                    M2C_FIELD(D_8006CF70, u8 *, 0) = 0x42U;
                    func_8002908C(0x3C);
                    var_v0 = 0;
                    if (func_800266B4() != 0) {
                        func_80026744();
                        func_8002908C(0x1AE);
loop_20:
                        if (*D_8006CF6C & 0x80) {
                            M2C_FIELD(D_8006CF70, u8 *, 0) = 1U;
                            func_8002908C(0x3C);
                            var_v0 = 0;
                            if (func_800266B4() != 0) {
                                func_80026744();
                                return 0;
                            }
                            /* Duplicate return node #27. Try simplifying control flow for better match */
                            return var_v0;
                        }
                        var_v0 = 0;
                        if (func_800290AC() == 0) {
                            goto loop_20;
                        }
                        /* Duplicate return node #27. Try simplifying control flow for better match */
                        return var_v0;
                    }
                    /* Duplicate return node #27. Try simplifying control flow for better match */
                    return var_v0;
                }
                var_v0 = 0;
                if (func_800290AC() == 0) {
                    goto loop_16;
                }
                /* Duplicate return node #27. Try simplifying control flow for better match */
                return var_v0;
            }
            /* Duplicate return node #27. Try simplifying control flow for better match */
            return var_v0;
        }
        *D_8006CF6C = -0x81;
        goto block_24;
    }
block_24:
    var_v0 = 1;
    if (M2C_FIELD(arg0, u8 *, 0x50) != 0) {
        var_v0 = 0;
        if (M2C_FIELD(arg0, u8 *, 0x37) == 0) {
            var_v0 = 1;
        }
    }
    return var_v0;
}
