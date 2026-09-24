#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80060CE0[];
extern u8 D_80063688[];
extern u8 D_800636C8[];
extern u8 D_80063720[];
extern u8 D_80063722[];
extern u8 D_80063748[];
extern u8 D_8006379A[];
extern u8 D_8006379B;
extern u8 D_80063804[];
extern u8 D_8006380C[];

u8 D_800636C8[4];                                   /* unable to generate initializer: cannot parse D_80063688 as integer */

void func_8001321C(s32 arg0) {
    s16 temp_a0_2;
    s16 temp_a1;
    s16 temp_v0_3;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s32 temp_a0_3;
    s32 temp_v0_4;
    s32 temp_v1_5;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_a1_5;
    s32 var_a1_6;
    s32 var_a1_7;
    s32 var_a2;
    s32 var_a3;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v1;
    u16 temp_v1_4;
    u8 *temp_a0;
    u8 temp_v0;
    u8 temp_v0_2;

    var_s0 = 0x08000000;
    if ((u8) M2C_FIELD(D_8006379A, u8 *, 0) >= 2U) {
        D_80063794("PutDispEnv(%08x)...\n", arg0);
    }
    M2C_FIELD(*D_800636C8, M2C_UNK (**)(s32, void *, s32, s32), 0x10)(((M2C_FIELD(arg0, u16 *, 2) & 0x3FF) << 0xA) | ((M2C_FIELD(arg0, u16 *, 0) & 0x3FF) | 0x05000000), *D_800636C8);
    temp_a0 = D_8006379A + 0x6A;
    if ((M2C_FIELD(D_8006379A, s32 *, 0x7A) != M2C_FIELD(arg0, s32 *, 0x10)) || ((s16) M2C_FIELD(D_8006379A, u16 *, 0x6A) != (s16) M2C_FIELD(arg0, u16 *, 0)) || ((s16) M2C_FIELD(temp_a0, u16 *, 2) != (s16) M2C_FIELD(arg0, u16 *, 2)) || ((s16) M2C_FIELD(temp_a0, u16 *, 4) != M2C_FIELD(arg0, s16 *, 4)) || ((s16) M2C_FIELD(temp_a0, u16 *, 6) != M2C_FIELD(arg0, s16 *, 6))) {
        temp_v0 = func_80016E00();
        M2C_FIELD(arg0, u8 *, 0x12) = temp_v0;
        if ((temp_v0 & 0xFF) == 1) {
            var_s0 = 0x08000008;
        }
        if (M2C_FIELD(arg0, u8 *, 0x11) != 0) {
            var_s0 |= 0x10;
        }
        if ((u8) M2C_FIELD(arg0, s32 *, 0x10) != 0) {
            var_s0 |= 0x20;
        }
        if (D_8006379B != 0) {
            var_s0 |= 0x80;
        }
        temp_v1 = M2C_FIELD(arg0, s16 *, 4);
        if (temp_v1 >= 0x119) {
            if (temp_v1 < 0x161) {
                var_s0 |= 1;
            } else if (temp_v1 < 0x191) {
                var_s0 |= 0x40;
            } else if (temp_v1 < 0x231) {
                var_s0 |= 2;
            } else {
                var_s0 |= 3;
            }
        }
        temp_v1_2 = M2C_FIELD(arg0, s16 *, 6);
        var_v0 = temp_v1_2 < 0x121;
        if (M2C_FIELD(arg0, u8 *, 0x12) == 0) {
            var_v0 = temp_v1_2 < 0x101;
        }
        if (var_v0 == 0) {
            var_s0 |= 0x24;
        }
        M2C_FIELD(*D_800636C8, M2C_UNK (**)(s32, void *, s32, s32), 0x10)(var_s0);
        M2C_FIELD(arg0, u8 *, 0x12) = 8U;
    }
    if (((s16) M2C_FIELD(D_8006380C, u16 *, 0) != M2C_FIELD(arg0, s16 *, 8)) || ((s16) M2C_FIELD(D_8006380C, u16 *, 2) != M2C_FIELD(arg0, s16 *, 0xA)) || ((s16) M2C_FIELD(D_8006380C, u16 *, 4) != M2C_FIELD(arg0, s16 *, 0xC)) || ((s16) M2C_FIELD(D_8006380C, u16 *, 6) != M2C_FIELD(arg0, s16 *, 0xE)) || (M2C_FIELD(arg0, u8 *, 0x12) == 8)) {
        temp_v0_2 = func_80016E00();
        M2C_FIELD(arg0, u8 *, 0x12) = temp_v0_2;
        temp_a0_2 = M2C_FIELD(arg0, s16 *, 0xA);
        var_s0_2 = temp_a0_2 + 0x13;
        if (!(temp_v0_2 & 0xFF)) {
            var_s0_2 = temp_a0_2 + 0x10;
        }
        temp_v0_3 = M2C_FIELD(arg0, s16 *, 0xE);
        var_s2 = var_s0_2 + temp_v0_3;
        if (temp_v0_3 == 0) {
            var_s2 = var_s0_2 + 0xF0;
        }
        temp_v1_3 = M2C_FIELD(arg0, s16 *, 4);
        var_a2 = 0;
        if (temp_v1_3 >= 0x119) {
            var_a2 = 1;
            if (temp_v1_3 >= 0x161) {
                var_a2 = 2;
                if (temp_v1_3 >= 0x191) {
                    var_a2 = 4;
                    if (temp_v1_3 < 0x231) {
                        var_a2 = 3;
                    }
                }
            }
        }
        temp_v0_4 = ((M2C_FIELD(arg0, u8 *, 0x12) * 5) + var_a2) * 4;
        temp_v1_4 = *(D_80063720 + temp_v0_4);
        temp_a1 = M2C_FIELD(arg0, s16 *, 0xC);
        var_v0_2 = *(D_80063722 + temp_v0_4) - temp_v1_4;
        var_a3 = M2C_FIELD(arg0, s16 *, 8) * D_80063748[var_a2];
        temp_a0_3 = temp_v1_4 + var_a3;
        if (temp_a1 != 0) {
            var_a3 = var_v0_2 * temp_a1;
            var_v0_2 = var_a3 >> 8;
        }
        temp_v1_5 = temp_a0_3 + var_v0_2;
        if (M2C_FIELD(arg0, u8 *, 0x12) != 0) {
            var_a1 = 0x21C;
            if (temp_a0_3 >= 0x21C) {
                var_a1 = 0xC94;
                if (temp_a0_3 < 0xC95) {
                    var_a1 = temp_a0_3;
                }
            }
            var_a0 = var_a1;
            var_a1_2 = var_a0 + (D_80063748[var_a2] * 4);
            var_v0_3 = var_s0_2 < 0x13;
            if (temp_v1_5 >= var_a1_2) {
                var_a1_2 = 0xCBC;
                if (temp_v1_5 < 0xCBD) {
                    var_a1_2 = temp_v1_5;
                }
                var_v0_3 = var_s0_2 < 0x13;
            }
            var_v1 = var_a1_2;
            if (var_v0_3 == 0) {
                var_a1_3 = 0x12F;
                if (var_s0_2 < 0x130) {
                    var_a1_3 = var_s0_2;
                }
            } else {
                var_a1_3 = 0x13;
            }
            var_s0_3 = var_a1_3;
            var_a1_4 = var_s0_3 + 2;
            var_v0_4 = var_s2 < 0x132;
            if (var_s2 >= var_a1_4) {
                var_a1_4 = 0x131;
                goto block_71;
            }
        } else {
            var_a1_5 = 0x1F4;
            if (temp_a0_3 >= 0x1F4) {
                var_a1_5 = 0xCB2;
                if (temp_a0_3 < 0xCB3) {
                    var_a1_5 = temp_a0_3;
                }
            }
            var_a0 = var_a1_5;
            var_a1_6 = var_a0 + (D_80063748[var_a2] * 4);
            var_v0_5 = var_s0_2 < 0x10;
            if (temp_v1_5 >= var_a1_6) {
                var_a1_6 = 0xCDA;
                if (temp_v1_5 < 0xCDB) {
                    var_a1_6 = temp_v1_5;
                }
                var_v0_5 = var_s0_2 < 0x10;
            }
            var_v1 = var_a1_6;
            if (var_v0_5 == 0) {
                var_a1_7 = 0x101;
                if (var_s0_2 < 0x102) {
                    var_a1_7 = var_s0_2;
                }
            } else {
                var_a1_7 = 0x10;
            }
            var_s0_3 = var_a1_7;
            var_a1_4 = var_s0_3 + 2;
            var_v0_4 = var_s2 < 0x103;
            if (var_s2 >= var_a1_4) {
                var_a1_4 = 0x102;
block_71:
                if (var_v0_4 != 0) {
                    var_a1_4 = var_s2;
                }
            }
        }
        M2C_FIELD(*D_800636C8, M2C_UNK (**)(s32, void *, s32, s32), 0x10)(((var_v1 & 0xFFF) << 0xC) | ((var_a0 & 0xFFF) | 0x06000000), *D_800636C8, var_a2, var_a3);
        M2C_FIELD(*D_800636C8, M2C_UNK (**)(s32, void *, s32, s32), 0x10)(((var_a1_4 & 0x3FF) << 0xA) | ((var_s0_3 & 0x3FF) | 0x07000000), *D_800636C8);
    }
    memcpy((s32) D_80063804, arg0, 0x14);
}
