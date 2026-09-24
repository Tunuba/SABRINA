#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086498[];
extern u8 D_8008649C[];
extern u8 D_800864A0[];
extern u8 D_800864A4[];
extern u8 D_800864A8[];
extern u8 D_800864B0[];
extern u8 D_800864B8[];
extern u8 D_800864BA[];
extern u8 D_800864BB[];
extern u8 D_800864BC[];
extern u8 D_800864BD[];
extern u8 D_800864BE[];
extern u8 D_800864BF[];
extern u8 D_800864C0[];
extern u8 D_800864C1[];
extern u8 D_800864D4[];
extern u8 D_8007C7E8[];
extern s32 D_8007C7F4[];
extern s32 * D_8007CA70;
extern s32 D_8007CA7C;


void func_8001D8EC(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1_5;
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_v0;
    u8 *temp_a1;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    u8 *temp_v1_6;
    u8 var_v1;

    if (*arg1 != 0) {
        D_8007C7F4[arg0] = -1;
        func_8001D5C0(arg0);
        return;
    }
    var_s4 = 4;
    if (arg0 == 0) {
        var_s4 = 0;
        var_v0 = func_800279B8(0);
    } else {
        var_v0 = func_800279B8(0x10);
    }
    D_8007C7F4[arg0] = var_v0;
    var_v0_2 = 1;
    if (D_8007C7F4[arg0] == 1) {
        var_v0_2 = 4;
        var_s1 = 2;
    } else {
        var_s1 = 0;
    }
    var_s3 = var_s4;
    var_s0 = var_s4 << 6;
loop_43:
    if (var_s3 < (var_v0_2 + var_s4)) {
        temp_v0 = func_80027A04();
        switch (temp_v0) {
        case 0:
        case 4:
            break;
        case 1:
            temp_a1 = &D_800864A0[var_s0];
            *temp_a1 = 1;
            temp_v1 = &D_80086498[var_s0];
            if (M2C_FIELD(temp_v1, s32 *, 0) != 0) {
                M2C_FIELD(temp_v1, s32 *, 0) = 0;
                *temp_a1 = 0;
                D_8008649C[var_s0] = 0;
                D_800864B0[var_s0] = 6;
                temp_v1_2 = &D_800864A4[var_s0];
                if (*temp_v1_2 != 0) {
                    *temp_v1_2 = 0;
                    D_8007CA7C -= 0xA;
                }
                temp_v1_3 = &(D_800864A4 + 1)[var_s0];
                if (*temp_v1_3 != 0) {
                    *temp_v1_3 = 0;
                    D_8007CA7C -= 0x14;
                }
            }
            break;
        case 2:
            temp_v1_4 = &D_800864A0[var_s0];
            if (*temp_v1_4 != 6) {
                *temp_v1_4 = 6;
                D_800864D4[var_s0] = func_80027AD0(M2C_FIELD(&D_80086498[var_s0], s32 *, 0x1C), 1, 0);
            } else {
                M2C_FIELD(&D_80086498[var_s0], s32 *, 0) = 1;
            default:
            case 3:
            case 5:
block_30:
                temp_a0 = M2C_FIELD(&D_80086498[var_s0], s32 *, 0);
                if (temp_a0 != 0) {
                    if (temp_a0 != 2) {
                        if (temp_a0 == 1) {
                            temp_v0_2 = (var_s3 - var_s4) * 8;
                            D_800864B8[var_s0] = (s16) ~((*(arg1 + (var_s1 + (temp_v0_2 + 2))) << 8) | *(arg1 + (var_s1 + (temp_v0_2 + 3))));
                            temp_v1_5 = D_8008649C[var_s0];
                            if (temp_v1_5 == 0) {
                                D_800864BC[var_s0] = D_800864BE[var_s0];
                                D_800864BD[var_s0] = D_800864BF[var_s0];
                                D_800864BA[var_s0] = D_800864C0[var_s0];
                                var_v1 = D_800864C1[var_s0];
                                goto block_37;
                            }
                            if (temp_v1_5 == 1) {
                                D_800864BC[var_s0] = *(arg1 + (var_s1 + (temp_v0_2 + 4)));
                                D_800864BD[var_s0] = *(arg1 + (var_s1 + (temp_v0_2 + 5)));
                                D_800864BA[var_s0] = *(arg1 + (var_s1 + (temp_v0_2 + 6)));
                                var_v1 = *(arg1 + (var_s1 + (temp_v0_2 + 7)));
block_37:
                                D_800864BB[var_s0] = var_v1;
                            }
                            if (D_8007CA70 == NULL) {
                                goto block_41;
                            }
                        }
                    } else {
                        temp_a2 = (var_s3 - var_s4) * 8;
                        D_800864B8[var_s0] = (s16) ~((*(arg1 + (var_s1 + (temp_a2 + 2))) << 8) | *(arg1 + (var_s1 + (temp_a2 + 3))));
                        D_800864BC[var_s0] = D_800864BE[var_s0];
                        D_800864BD[var_s0] = D_800864BF[var_s0];
                        D_800864BA[var_s0] = D_800864C0[var_s0];
                        D_800864BB[var_s0] = D_800864C1[var_s0];
                        if (D_8007CA70 == NULL) {
block_41:
                            D_8007CA70 = (s32 *) &D_80086498[var_s0];
                        }
                    }
                }
            }
            break;
        case 6:
            if (D_800864A0[var_s0] != 6) {
                if (func_80027AD0(M2C_FIELD(&D_80086498[var_s0], s32 *, 0x1C), 4, 1) == 7) {
                    temp_v1_6 = &D_800864B0[var_s0];
                    temp_v0_3 = *temp_v1_6;
                    if (temp_v0_3 == 6) {
                        if (func_80027D44(M2C_FIELD(&D_80086498[var_s0], s32 *, 0x1C), (s32) D_8007C7E8) == 0) {
                            D_800864B0[var_s0] = 0;
                        } else {
                            temp_v0_4 = func_80027AD0(M2C_FIELD(&D_80086498[var_s0], s32 *, 0x1C), 2, 0);
                            M2C_FIELD(&D_80086498[var_s0], s32 *, 0) = 1;
                            if (temp_v0_4 == 4) {
                                D_8008649C[var_s0] = 0;
                            } else if (temp_v0_4 == 7) {
                                D_8008649C[var_s0] = 1;
                            }
                            goto block_29;
                        }
                    } else {
                        *temp_v1_6 = (s32) (temp_v0_3 + 1);
                    }
                } else {
block_29:
                    D_800864A0[var_s0] = 6;
                    D_800864A8[var_s0] = 0;
                    D_800864A4[var_s0] = 0;
                    (D_800864A4 + 1)[var_s0] = 0;
                }
            } else {
                goto block_30;
            }
            break;
        }
        var_s3 += 1;
        var_s0 += 0x40;
        goto loop_43;
    }
}
