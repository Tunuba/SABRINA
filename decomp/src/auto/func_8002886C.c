#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



static M2C_UNK (*D_8006CF88)(void *, u8 *, u32, u8) = NULL;

void func_8002886C(void *arg0) {
    s32 (*temp_v0_4)(void *);
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    u32 temp_a2;
    u8 *var_a0;
    u8 *var_a0_2;
    u8 *var_a1;
    u8 temp_a3;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 var_v0;
    u8 var_v1_3;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_a0_5;

    temp_a0 = M2C_FIELD(arg0, void **, 0x3C);
    if (!(M2C_FIELD(temp_a0, u8 *, 0) & 0xF0)) {
        M2C_FIELD(M2C_FIELD(arg0, u8 **, 0x30), u8 *, 0) = 0xFF;
        M2C_FIELD(M2C_FIELD(arg0, u8 **, 0x30), u8 *, 1) = 0U;
        M2C_FIELD(arg0, u8 *, 0xE8) = 0U;
        M2C_FIELD(arg0, u8 *, 0x35) = 0U;
        goto block_31;
    }
    if ((arg0 != M2C_FIELD(arg0, s32 *, 0x10)) && (((temp_v1 = M2C_FIELD(temp_a0, u8 *, 1), (temp_v1 != 0)) && (temp_v1 != 0x5A)) || (((u8) M2C_FIELD(temp_a0, u8 *, 0) >> 4) == 8))) {
        func_80028D40((s32) arg0);
        return;
    }
    temp_a0_2 = M2C_FIELD(arg0, void **, 0x3C);
    var_a1 = M2C_FIELD(arg0, u8 **, 0x30);
    temp_a2 = (u8) M2C_FIELD(temp_a0_2, u8 *, 0) >> 4;
    temp_a3 = M2C_FIELD(arg0, u8 *, 0xE8);
    if (M2C_FIELD(temp_a0_2, u8 *, 1) == 0x5A) {
        if (temp_a3 == 8) {
            M2C_FIELD(var_a1, u8 *, 0) = 0;
        } else if (temp_a2 != 0xF) {
            temp_a0_3 = M2C_FIELD(arg0, void **, 0x3C);
            M2C_FIELD(arg0, u8 *, 0xE8) = (u8) temp_a2;
            M2C_FIELD(var_a1, u8 *, 0) = 0;
            temp_a0_4 = temp_a0_3 + 1;
            M2C_FIELD(var_a1, u8 *, 1) = (u8) M2C_FIELD(temp_a0_3, u8 *, 0);
            var_a1 = var_a1 + 1 + 1;
            if (arg0 != M2C_FIELD(arg0, s32 *, 0x10)) {
                M2C_FIELD(arg0, u8 *, 0x35) = 8U;
                var_a0 = temp_a0_4 + 1;
                var_v1 = 2;
                do {
                    temp_v0 = *var_a0;
                    var_a0 += 1;
                    var_v1 += 1;
                    *var_a1 = temp_v0;
                    var_a1 += 1;
                } while (var_v1 < 8);
            } else {
                var_v1_2 = 2;
                if (temp_a2 == 8) {
                    M2C_FIELD(arg0, u8 *, 0x35) = 2U;
                } else {
                    M2C_FIELD(arg0, u8 *, 0x35) = (u8) M2C_FIELD(arg0, u8 *, 0x44);
                    var_a0_2 = temp_a0_4 + 1;
                    if ((s32) M2C_FIELD(arg0, u8 *, 0x35) > 2) {
                        do {
                            temp_v0_2 = *var_a0_2;
                            var_a0_2 += 1;
                            var_v1_2 += 1;
                            *var_a1 = temp_v0_2;
                            var_a1 += 1;
                        } while (var_v1_2 < (s32) M2C_FIELD(arg0, u8 *, 0x35));
                    }
                }
            }
        }
    }
    if (((M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 1) == 0) && ((M2C_FIELD(arg0, u8 *, 0x46) != 1) || (M2C_FIELD(arg0, s32 *, 0x14) != 0)) && (M2C_FIELD(arg0, u8 *, 0x50) == 0)) || (M2C_FIELD(arg0, u8 *, 0xE8) != temp_a3)) {
        D_8006CF88(arg0, var_a1, temp_a2, temp_a3);
    }
    if ((M2C_FIELD(arg0, void **, 0xC) != NULL) || (M2C_FIELD(arg0, u8 *, 0x37) == 0)) {
        M2C_FIELD(arg0, s8 *, 0x4A) = 0;
    }
    temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x46);
    if (temp_v1_2 != 0xFF) {
        if (((u32) ((temp_v1_2 - 2) & 0xFF) < 0xFCU) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u8 *, 0) != 0xF3)) {
block_31:
            D_8006CF88(arg0);
            return;
        }
        if (M2C_FIELD(arg0, u8 *, 0xE8) == 8) {
            temp_v0_3 = M2C_FIELD(arg0, u8 *, 0x46);
            if (temp_v0_3 != 0) {
                M2C_FIELD(arg0, u8 *, 0x46) = (u8) (temp_v0_3 + 1);
                return;
            }
            goto block_40;
        }
        if (M2C_FIELD(arg0, u8 *, 0x46) != 0) {
            if (arg0 == M2C_FIELD(arg0, s32 *, 0x10)) {
                var_v0 = M2C_FIELD(arg0, u8 *, 0x37);
            } else {
                var_v0 = M2C_FIELD(arg0, u8 *, 0x38);
            }
            if (var_v0 != 0) {
                goto block_40;
            }
        } else {
block_40:
            temp_v1_3 = M2C_FIELD(arg0, u8 *, 0x46);
            if (temp_v1_3 != 1) {
                if ((s32) temp_v1_3 < 2) {
                    if (temp_v1_3 != 0) {
                        goto block_57;
                    }
                    temp_a0_5 = M2C_FIELD(arg0, void **, 0xC);
                    if ((temp_a0_5 != NULL) || (M2C_FIELD(arg0, u8 *, 0x37) == 0)) {
                        if ((M2C_FIELD(arg0, u8 *, 0xE8) == 8) && (temp_a0_5 != NULL)) {
                            var_v1_3 = *M2C_FIELD(temp_a0_5, u8 **, 0x3C);
                            if (var_v1_3 == 0xFF) {
                                M2C_FIELD(arg0, s8 *, 0x49) = 2;
                                goto block_61;
                            }
                        }
                        M2C_FIELD(arg0, s8 *, 0x49) = 1;
                        goto block_55;
                    }
                } else if (temp_v1_3 != 0xFE) {
                    if (temp_v1_3 != 0xFF) {
block_57:
                        temp_v0_4 = M2C_FIELD(arg0, s32 (**)(void *), 0x18);
                        if (temp_v0_4 != NULL) {
                            var_v0_2 = temp_v0_4(arg0);
                        } else {
                            var_v0_2 = func_80026ECC((s32) arg0);
                        }
                        var_v1_3 = M2C_FIELD(arg0, u8 *, 0x46) + var_v0_2;
block_61:
                        M2C_FIELD(arg0, u8 *, 0x46) = var_v1_3;
                    }
                } else {
                    M2C_FIELD(arg0, u8 *, 0x46) = 0xFFU;
                }
            } else {
                M2C_FIELD(arg0, s8 *, 0x47) = 0;
block_55:
                M2C_FIELD(arg0, u8 *, 0x46) = (u8) (M2C_FIELD(arg0, u8 *, 0x46) + 1);
            }
        }
    }
}
