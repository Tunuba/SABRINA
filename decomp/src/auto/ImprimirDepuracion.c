#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80062AF8;
extern s32 D_80062AFC;
extern s32 D_80063504;
extern u8 D_80063508[];
extern u8 D_8006352C[];


void ImprimirDepuracion(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *sp210;
    s32 **var_s0;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a1;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0;
    s8 var_a0;
    s8 var_a2;
    u8 temp_a0;
    void *temp_s1;

    var_a1 = arg1;
    sp210 = &arg1;
    if ((arg0 < 0) || (arg0 >= D_80062AF8)) {
        var_s3 = arg0;
        arg0 = D_80062AFC;
        if (*(D_8006352C + (D_80062AFC * 0x30)) == 0) {

        } else {
            goto block_5;
        }
    } else {
        var_s3 = arg1;
        sp210 = &arg2;
block_5:
        temp_s1 = (arg0 * 0x30) + D_80063508;
        if (M2C_FIELD(temp_s1, s32 *, 0x1C) >= M2C_FIELD(temp_s1, s32 *, 0x28)) {
            var_a0 = *var_s3;
            if (var_a0 != 0) {
loop_8:
                if ((var_a0 != 0x25) || (var_s3 += 1, var_a0 = *var_s3, var_s2 = 0, (var_a0 == 0x25))) {
                    temp_v0 = M2C_FIELD(temp_s1, s32 *, 0x28);
                    *(M2C_FIELD(temp_s1, s32 *, 0x24) + temp_v0) = var_a0;
                    temp_v0_2 = temp_v0 + 1;
                    M2C_FIELD(temp_s1, s32 *, 0x28) = temp_v0_2;
                    if (M2C_FIELD(temp_s1, s32 *, 0x1C) < temp_v0_2) {
                        return;
                    }
                    goto block_45;
                }
                temp_a2 = var_a0 == 0x30;
loop_14:
                if ((u32) (var_a0 - 0x30) < 0xAU) {
                    var_s2 = (var_s2 * 0xA) - 0x30 + var_a0;
                    var_s3 += 1;
                    var_a0 = *var_s3;
                    goto loop_14;
                }
                if (var_s2 <= 0) {
                    var_s2 = 1;
                }
                var_s0 = &sp210;
                switch (var_a0) {
                case 0x64:
                    var_a0_2 = *sp210;
                    sp210 += 4;
                    if (var_a0_2 < 0) {
                        var_a0_2 = -var_a0_2;
                        var_a2 = 0x2D;
                    } else {
                        var_a2 = 0;
                    }
                    var_a1 = 0;
                    do {
loop_23:
                        var_s0 -= 1;
                        var_a1 += 1;
                        *var_s0 = (s8) ((var_a0_2 % 10) + 0x30);
                        var_a0_2 /= 0xA;
                        if (var_a1 == 0) {
                            goto loop_23;
                        }
                    } while (var_a0_2 != 0);
                    var_v0 = var_a1 < var_s2;
                    if (var_a2 != 0) {
                        var_s0 -= 1;
                        *var_s0 = var_a2;
                        var_a1 += 1;
                    default:
block_37:
                        var_v0 = var_a1 < var_s2;
                    }
block_38:
                    if (var_v0 != 0) {
loop_39:
                        temp_v0_3 = M2C_FIELD(temp_s1, s32 *, 0x28);
                        *(M2C_FIELD(temp_s1, s32 *, 0x24) + temp_v0_3) = 0x20;
                        temp_v0_4 = temp_v0_3 + 1;
                        M2C_FIELD(temp_s1, s32 *, 0x28) = temp_v0_4;
                        if (M2C_FIELD(temp_s1, s32 *, 0x1C) >= temp_v0_4) {
                            var_s2 -= 1;
                            if (var_a1 >= var_s2) {
                                goto block_41;
                            }
                            goto loop_39;
                        }
                    } else {
block_41:
                        var_a1 -= 1;
                        if (var_a1 != -1) {
loop_43:
                            temp_v1 = M2C_FIELD(temp_s1, s32 *, 0x28);
                            temp_a0 = *var_s0;
                            var_s0 += 1;
                            *(M2C_FIELD(temp_s1, s32 *, 0x24) + temp_v1) = temp_a0;
                            temp_v1_2 = temp_v1 + 1;
                            M2C_FIELD(temp_s1, s32 *, 0x28) = temp_v1_2;
                            if (M2C_FIELD(temp_s1, s32 *, 0x1C) >= temp_v1_2) {
                                var_a1 -= 1;
                                if (var_a1 == -1) {
                                    goto block_45;
                                }
                                goto loop_43;
                            }
                        } else {
block_45:
                            var_s3 += 1;
                            var_a0 = *var_s3;
                            if (var_a0 == 0) {
                                goto block_46;
                            }
                            goto loop_8;
                        }
                    }
                    break;
                case 0x58:
                case 0x78:
                    var_a1 = 0;
                    var_a0_3 = *sp210;
                    sp210 += 4;
loop_28:
                    var_s0 -= 1;
                    do {
                        temp_v0_5 = var_a0_3 & 0xF;
                        var_a0_3 = (s32) ((u32) var_a0_3 >> 4);
                        var_a1 += 1;
                        *var_s0 = (u8) *(D_80063504 + temp_v0_5);
                        if (var_a1 == 0) {
                            goto loop_28;
                        }
                        var_s0 -= 1;
                    } while (var_a0_3 != 0);
                    var_s0 += 1;
                    if (temp_a2 != 0) {
                        if (var_a1 < var_s2) {
                            do {
                                var_s0 -= 1;
                                var_a1 += 1;
                                var_v0 = var_a1 < var_s2;
                                *var_s0 = 0x30;
                            } while (var_v0 != 0);
                            goto block_38;
                        }
                        goto block_41;
                    }
                    goto block_37;
                case 0x63:
                    var_s0 -= 1;
                    var_a1 = 1;
                    *var_s0 = (u8) *sp210;
                    sp210 += 4;
                    goto block_37;
                case 0x73:
                    var_s0 = (s32 **) *sp210;
                    sp210 += 4;
                    var_a1 = func_800150F0((s32) var_s0);
                    goto block_37;
                }
            } else {
block_46:
                *(M2C_FIELD(temp_s1, s32 *, 0x24) + M2C_FIELD(temp_s1, s32 *, 0x28)) = 0;
            }
        }
    }
}
