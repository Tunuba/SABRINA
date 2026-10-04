#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 * D_80091400;
extern s32 D_80091404;
extern void * D_80091408;
extern s32 D_8009140C;
extern s32 D_80091410;
extern s32 D_80091414;
extern s32 D_80091418;
extern s32 D_8009141C;
extern s32 D_80091424;
extern s32 D_80091428;
extern u32 D_8009142C;
extern s32 D_80091430;
extern u32 D_80091434;
extern s16 D_80091438;
extern s32 D_8009143C;
extern s32 D_80091440;
extern s32 D_80091444;
extern s32 D_80091478;
extern u16 * D_80093A34;
extern s8 * D_8006D5D0;
extern u8 * D_8006D5D4;
extern s8 * D_8006D5D8;
extern s32 * D_8006D5DC;
extern s32 * D_8006D5E0;
extern s32 * D_8006D5EC;
extern s32 * D_8006D5F0;
extern s32 D_8006D5F4;
extern extern s32 (*D_80093A30)();


void func_8002D714(void) {
    u16 sp22;
    s16 sp24;
    M2C_UNK sp28;
    u8 sp30;
    M2C_UNK temp_a1;
    s32 temp_v0_2;
    s32 var_t0;
    u16 *temp_v1;
    u16 *var_a1;
    u16 *var_v1;
    u32 temp_v0;
    u32 var_a0;
    u32 var_a0_2;
    u32 var_a0_3;
    u8 *temp_v1_2;

    if (D_80091430 != 1) {
        if ((D_8009140C != 0) && (*D_8006D5EC & 0x01000000)) {
            D_8009143C = 1;
            if (D_80091410 != 0) {
                D_80091414 += 1;
            }
            D_8006D5F4 = 1;
            return;
        }
        if (func_80029A70(1, (s32) &sp30) != 5) {
            sp22 = (u16) sp30;
            sp24 = (s16) sp31;
            if (sp30 & 4) {
                D_8006D5F4 = 3;
                return;
            }
            temp_v1 = D_80091400 + (D_80091418 << 5);
            D_80093A34 = temp_v1;
            if (*temp_v1 != 0) {
                if (D_80091410 != 0) {
                    D_80091414 += 1;
                }
                D_8006D5F4 = 4;
                return;
            }
            *D_8006D5D0 = 0;
            *D_8006D5D8 = 0;
            *D_8006D5D0 = 0;
            *D_8006D5D8 = 0x80;
            *D_8006D5DC = 0x20943;
            *D_8006D5E0 = 0x1323;
            var_a0 = 0;
            if (D_80091478 == 0) {
                do {
                    temp_v1_2 = &sp28 + var_a0;
                    var_a0 += 1;
                    *temp_v1_2 = *D_8006D5D4;
                } while (var_a0 < 4U);
                var_a0_2 = 0;
                do {
                    var_a0_2 += 1;
                } while (var_a0_2 < 8U);
            }
            if (D_80091410 != 0) {
                func_8002D540((s32) D_80093A34, D_80091410 + (D_80091414 << 0xB), 8);
            } else {
                func_8002D56C(3, (s32) D_80093A34, 0, 8, /* extra? */ 0x11000000, /* extra? */ 0, /* extra? */ 0);
            }
            if (*D_8006D5F0 & 0x01000000) {
                do {

                } while (*D_8006D5F0 & 0x01000000);
            }
            temp_a1 = M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */);
            M2C_FIELD(D_80093A34, M2C_UNK *, 0x1F) = M2C_UNALIGNED32(temp_a1);
            *D_8006D5DC = 0x20843;
            *D_8006D5E0 = 0x1325;
            if ((D_80091424 == 1) && (D_80091428 != 0)) {
                if (D_80091428 != M2C_FIELD(D_80093A34, u16 *, 8)) {
                    M2C_FIELD(D_80093A34, u16 *, 0) = 0;
                    if (D_80091410 != 0) {
                        D_80091414 += 1;
                    }
                } else {
                    D_80091424 = 0;
                    goto block_30;
                }
            } else {
block_30:
                if ((M2C_FIELD(D_80093A34, u16 *, 0) != 0x160) || ((((u16) M2C_FIELD(D_80093A34, u16 *, 2) >> 0xA) & 0x1F) != D_80091444)) {
                    if (D_80091410 != 0) {
                        D_80091414 = 0;
                    }
                    D_8006D5F4 = 5;
                    M2C_FIELD(D_80093A34, u16 *, 0) = 0;
                    return;
                }
                if ((D_80091438 != M2C_FIELD(D_80093A34, u16 *, 4)) || ((D_80091434 != 0) && (D_80091434 != M2C_FIELD(D_80093A34, u16 *, 8)))) {
                    D_80091434 = 0;
                    D_80091438 = 0;
                    init_ring_status(D_8009141C, D_80091418 - D_8009141C);
                    D_80091418 = D_8009141C;
                    M2C_FIELD(D_80093A34, u16 *, 0) = 0;
                    if (D_80091410 != 0) {
                        D_80091414 += 1;
                    }
                    D_8006D5F4 = 6;
                    return;
                }
                if (M2C_FIELD(D_80093A34, u16 *, 4) == 0) {
                    D_80091438 = 0;
                    temp_v0 = M2C_FIELD(D_80093A34, u16 *, 8) & 0xFFFF;
                    D_80091434 = temp_v0;
                    if ((D_8009142C != 0) && (temp_v0 >= (u32) D_8009142C)) {
                        D_80091434 = 0;
                        D_80091438 = 0;
                        init_ring_status(D_8009141C, D_80091418 - D_8009141C);
                        D_80091418 = D_8009141C;
                        M2C_FIELD(D_80093A34, u16 *, 0) = 0;
                        D_80091424 = 1;
                        if (D_80093A30 != NULL) {
                            D_80093A30();
                        }
                        if (D_80091410 != 0) {
                            D_80091414 += 1;
                        }
                        D_8006D5F4 = 7;
                        return;
                    }
                    if ((u32) ((D_80091404 - D_80091418) - 1) < (u16) M2C_FIELD(D_80093A34, u16 *, 6)) {
                        if (D_8009142C == 0) {
                            M2C_FIELD(D_80093A34, u16 *, 0) = 1;
                            D_80091424 = 1;
                            if (D_80093A30 != NULL) {
                                D_80093A30(D_80093A34, temp_a1);
                            }
                            if (D_80091410 != 0) {
                                D_80091414 += 1;
                            }
                            D_8006D5F4 = 8;
                            return;
                        }
                        if ((s16) *D_80091400 != 0) {
                            M2C_FIELD(D_80093A34, u16 *, 0) = 0;
                            if (D_80091410 != 0) {
                                D_80091414 += 1;
                            }
                            D_8006D5F4 = 9;
                            return;
                        }
                        M2C_FIELD(D_80093A34, u16 *, 0) = 1;
                        var_a1 = D_80091400;
                        var_v1 = D_80093A34;
                        var_a0_3 = 0;
                        D_80091418 = 0;
                        do {
                            temp_v0_2 = *var_v1;
                            var_v1 += 4;
                            var_a0_3 += 1;
                            *var_a1 = temp_v0_2;
                            var_a1 += 4;
                        } while (var_a0_3 < 8U);
                        D_80093A34 = D_80091400;
                        goto block_64;
                    }
block_64:
                    D_8009141C = D_80091418;
                    goto block_65;
                }
block_65:
                D_8006D5F4 = 0xA;
                D_80091438 = (u16) D_80091438 + 1;
                D_80091408 = D_80091400 + (D_80091404 << 5) + (D_80091418 * 0x7E0);
                var_t0 = 0x11000000;
                if (D_8009140C != 0) {
                    *D_8006D5DC = 0x20943;
                    *D_8006D5E0 = 0x1323;
                } else {
                    var_t0 = 0x11400100;
                    *D_8006D5DC = 0x21020843;
                }
                if ((M2C_FIELD(D_80093A34, u16 *, 6) - 1) == M2C_FIELD(D_80093A34, u16 *, 4)) {
                    D_80091430 = 1;
                    if (D_80091410 != 0) {
                        func_8002D540((s32) D_80091408, D_80091410 + (D_80091414 << 0xB) + 0x20, 0x1F8);
                        D_80091414 += 1;
                    } else {
                        func_8002D56C(3, (s32) D_80091408, 0, 0x1F8, /* extra? */ var_t0, /* extra? */ 1, /* extra? */ 0);
                    }
                    D_80091438 = 0;
                    D_80091434 = 0;
                    D_80091444 = D_80091440;
                } else if (D_80091410 != 0) {
                    func_8002D540((s32) D_80091408, D_80091410 + (D_80091414 << 0xB) + 0x20, 0x1F8);
                    D_80091414 += 1;
                } else {
                    func_8002D56C(3, (s32) D_80091408, 0, 0x1F8, /* extra? */ var_t0, /* extra? */ 0, /* extra? */ 0);
                }
                *D_8006D5E0 = 0x1325;
                M2C_FIELD(D_80093A34, u16 *, 0) = 3;
                D_80091418 += 1;
                if ((D_80091410 != 0) && (D_80091430 != 0)) {
                    data_ready_callback();
                }
            }
        }
    }
}
