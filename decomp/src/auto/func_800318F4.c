#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007C8A4;
extern s16 D_8007CB70;
extern void * D_8007CB8C;


void func_800318F4(s32 arg0) {
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_3;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_s2_4;
    s32 temp_s2_5;
    s32 temp_s2_6;
    s32 temp_s2_7;
    s32 temp_v0_11;
    s32 temp_v0_13;
    s32 temp_v0_2;
    s32 var_v1_3;
    s8 temp_v0;
    s8 temp_v0_14;
    s8 temp_v0_6;
    s8 temp_v0_7;
    s8 temp_v0_8;
    s8 temp_v0_9;
    s8 var_v1;
    s8 var_v1_2;
    u8 temp_v0_10;
    u8 temp_v0_12;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 temp_v0_5;
    void *temp_a0;
    void *temp_s0;
    void *temp_s1;
    void *temp_s4;

    temp_s1 = arg0 + 0x74;
    temp_a0 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
    temp_s0 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s4 = M2C_FIELD(arg0, void **, 0x64);
    temp_s2 = M2C_FIELD(temp_s1, s32 *, 8) & 0xFFFF;
    if (M2C_FIELD(temp_s1, s8 *, 0x1D) != 0) {
        D_8007C8A4 = 0x96;
    }
    if (D_8007C8A4 >= 0) {
        D_8007C8A4 -= 1;
    }
    temp_v0 = M2C_FIELD(temp_s1, s8 *, 0x1D);
    switch (temp_v0) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        if (temp_s2 & 0xF000) {
            M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 2);
            M2C_FIELD(temp_s0, s8 *, 0x50) = (s8) M2C_FIELD(temp_s1, s8 *, 0x1C);
            M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            D_8007CB70 = 1;
            M2C_FIELD(temp_s1, s32 *, 4) = 0;
            M2C_FIELD(temp_s1, s8 *, 0x1D) = 1;
        } else {
            if ((M2C_FIELD(temp_s0, u8 *, 0x51) == M2C_FIELD(temp_s4, u16 *, 6)) && (func_8002EFD0(arg0) != 0)) {
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0);
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
                D_8007CB70 = 0;
            }
            if ((D_8007C8A4 < 0) && (func_8002EFD0(arg0) != 0)) {
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                temp_v0_2 = func_80021CE4(4);
                switch (temp_v0_2) {                /* switch 2; irregular */
                case 0:                             /* switch 2 */
                    M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x2A);
                    D_8007CB70 = 0x15;
                    break;
                case 1:                             /* switch 2 */
                    M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x2C);
                    D_8007CB70 = 0x16;
                    break;
                case 2:                             /* switch 2 */
                    M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x2E);
                    D_8007CB70 = 0x17;
                    break;
                case 3:                             /* switch 2 */
                    M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x30);
                    D_8007CB70 = 0x18;
                    break;
                default:                            /* switch 2 */
                    M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x2C);
                    D_8007CB70 = 0x16;
                    break;
                }
            }
        }
        break;
    case 1:                                         /* switch 1 */
        M2C_FIELD(temp_s0, s16 *, 0x4E) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x4E) + 0x800);
        M2C_FIELD(temp_a0, s16 *, 0x4E) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x4E) + 0x800);
        M2C_FIELD(temp_s1, s32 *, 4) = (s32) ((s32) (M2C_FIELD(temp_s0, s16 *, 0x4E) * 0x5F9) >> 0xC);
        if (M2C_FIELD(temp_s0, u8 *, 0x51) == M2C_FIELD(temp_s0, u8 *, 0x53)) {
            M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            M2C_FIELD(temp_s1, s32 *, 4) = 0x5F9;
            M2C_FIELD(temp_s1, u8 *, 0x1A) = 5U;
            M2C_FIELD(temp_s1, u8 *, 0x1B) = 0x13U;
            M2C_FIELD(temp_s1, s8 *, 0x1D) = 2;
        }
        func_80032F90(arg0, temp_s2 & 0xF000 & 0xFFFF);
        M2C_FIELD(temp_s1, s16 *, 0xE) = (s16) (M2C_FIELD(temp_s1, s16 *, 0xE) + 1);
        break;
    case 2:                                         /* switch 1 */
        temp_s2_2 = temp_s2 & 0xF000 & 0xFFFF;
        if (temp_s2_2 != 0) {
            func_80032F90(arg0, temp_s2_2);
            M2C_FIELD(temp_s1, s16 *, 0xE) = (s16) (M2C_FIELD(temp_s1, s16 *, 0xE) + 1);
            if (M2C_FIELD(temp_s1, s16 *, 0xE) >= 3) {
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 4);
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                D_8007CB70 = 2;
                M2C_FIELD(temp_s1, u8 *, 0x1A) = 3U;
                M2C_FIELD(temp_s1, u8 *, 0x1B) = 9U;
                M2C_FIELD(temp_s1, s8 *, 0x1D) = 4;
            }
        } else {
            M2C_FIELD(temp_s1, s8 *, 0x1D) = 3;
        }
        break;
    case 3:                                         /* switch 1 */
        if (M2C_FIELD(temp_s0, u8 *, 0x51) == M2C_FIELD(temp_s4, u16 *, 2)) {
            temp_v0_3 = M2C_FIELD(temp_s0, u8 *, 0x52);
            if ((temp_v0_3 == 6) || (temp_v0_3 == 0x12)) {
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0);
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                D_8007CB70 = 0;
                M2C_FIELD(temp_s1, s32 *, 4) = 0;
            } else {
                func_80032F90(arg0, 0);
            }
        } else if (M2C_FIELD(temp_s0, u8 *, 0x53) == M2C_FIELD(temp_s4, u16 *, 0)) {
            M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            M2C_FIELD(temp_s1, s8 *, 0x1D) = 0;
            M2C_FIELD(temp_s1, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s1, s8 *, 0x1C) = (s8) (M2C_FIELD(temp_s1, s8 *, 0x1C) ^ 0xC);
        }
        break;
    case 4:                                         /* switch 1 */
        temp_s2_3 = temp_s2 & 0xF000 & 0xFFFF;
        if (temp_s2_3 != 0) {
            M2C_FIELD(temp_s1, s32 *, 4) = (s32) ((s32) ((M2C_FIELD(temp_s0, s16 *, 0x4E) * 0xDA7) + 0x5F9) >> 0xC);
            if (M2C_FIELD(temp_s0, u8 *, 0x51) == M2C_FIELD(temp_s0, u8 *, 0x53)) {
                temp_v0_4 = (u8) M2C_FIELD(temp_s0, s8 *, 0x50);
                if (temp_v0_4 == temp_v0_4) {
                    M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
                    M2C_FIELD(temp_s1, s32 *, 4) = 0x13A0;
                    M2C_FIELD(temp_s1, u8 *, 0x1A) = 3U;
                    M2C_FIELD(temp_s1, u8 *, 0x1B) = 9U;
                    M2C_FIELD(temp_s1, s8 *, 0x1D) = 5;
                    M2C_FIELD(temp_s1, s16 *, 0xE) = 0;
                }
            }
            func_80032F90(arg0, temp_s2_3);
        } else {
            M2C_FIELD(temp_s1, s8 *, 0x1D) = 6;
        }
        break;
    case 5:                                         /* switch 1 */
        temp_s2_4 = temp_s2 & 0xF000 & 0xFFFF;
        if (temp_s2_4 != 0) {
            M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            func_80032F90(arg0, temp_s2_4);
            M2C_FIELD(temp_s1, s16 *, 0x10) = (s16) (M2C_FIELD(temp_s1, s16 *, 0x10) + 1);
        } else {
            M2C_FIELD(temp_s1, s8 *, 0x1D) = 6;
        }
        break;
    case 6:                                         /* switch 1 */
        if (M2C_FIELD(temp_s0, u8 *, 0x51) == M2C_FIELD(temp_s4, u16 *, 4)) {
            temp_v0_5 = M2C_FIELD(temp_s0, u8 *, 0x52);
            if ((temp_v0_5 == 4) || (temp_v0_5 == 0xC)) {
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0);
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                D_8007CB70 = 0;
                M2C_FIELD(temp_s1, s32 *, 4) = 0;
            } else {
                func_80032F90(arg0, 0);
            }
        } else if (M2C_FIELD(temp_s0, u8 *, 0x53) == M2C_FIELD(temp_s4, u16 *, 0)) {
            M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            M2C_FIELD(temp_s1, s8 *, 0x1D) = 0;
            M2C_FIELD(temp_s1, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s1, s8 *, 0x1C) = (s8) (M2C_FIELD(temp_s1, s8 *, 0x1C) ^ 0xC);
        }
        break;
    case 13:                                        /* switch 1 */
        if (temp_s2 & 0x10) {
            if (temp_s2 & 0x4000) {
                temp_v0_6 = M2C_FIELD(temp_s1, s8 *, 0x1F);
                if (temp_v0_6 < 0xF) {
                    M2C_FIELD(temp_s1, s8 *, 0x1F) = (s8) (temp_v0_6 + 2);
                }
            }
            if (temp_s2 & 0x1000) {
                temp_v0_7 = M2C_FIELD(temp_s1, s8 *, 0x1F);
                if (temp_v0_7 >= -0xE) {
                    M2C_FIELD(temp_s1, s8 *, 0x1F) = (s8) (temp_v0_7 - 2);
                }
            }
            if (temp_s2 & 0x8000) {
                temp_v0_8 = M2C_FIELD(temp_s1, s8 *, 0x20);
                if (temp_v0_8 < 0x20) {
                    M2C_FIELD(temp_s1, s8 *, 0x20) = (s8) (temp_v0_8 + 3);
                }
            }
            if (temp_s2 & 0x2000) {
                temp_v0_9 = M2C_FIELD(temp_s1, s8 *, 0x20);
                if (temp_v0_9 >= -0x1F) {
                    M2C_FIELD(temp_s1, s8 *, 0x20) = (s8) (temp_v0_9 - 3);
                }
            }
        } else {
            M2C_FIELD(temp_s1, s8 *, 0x1D) = 0;
        }
        break;
    case 14:                                        /* switch 1 */
        if (M2C_FIELD(temp_s0, u8 *, 0x53) == M2C_FIELD(temp_s4, u16 *, 0x24)) {
            if (func_8002EFD0(arg0) != 0) {
                M2C_FIELD(arg0, s32 *, 0x38) = 0;
                M2C_FIELD(arg0, u32 *, 0x3C) = -0x2AAAU;
                M2C_FIELD(arg0, s32 *, 0x40) = 0;
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x26);
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                D_8007CB70 = 0x13;
                M2C_FIELD(temp_s1, u8 *, 0x1A) = (u8) M2C_FIELD(temp_s0, s8 *, 0x50);
                M2C_FIELD(temp_s1, u8 *, 0x1B) = (u8) M2C_FIELD(temp_s0, s8 *, 0x50);
                M2C_FIELD(temp_s1, s8 *, 0x1D) = 0xF;
                M2C_FIELD(temp_s1, s32 *, 4) = 0x2147;
            } else {
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            }
        }
        break;
    case 15:                                        /* switch 1 */
        temp_s2_5 = temp_s2 & 0xF000 & 0xFFFF;
        if ((temp_s2_5 != 0) && (M2C_FIELD(temp_s1, s8 *, 0x26) == 0)) {
            func_80032F90(arg0, temp_s2_5);
        }
        M2C_FIELD(temp_s1, u8 *, 0x1A) = -1U;
        M2C_FIELD(temp_s1, u8 *, 0x1B) = -1U;
        var_v1 = (M2C_FIELD(arg0, u32 *, 0x3C) / 1638) + ((u32) M2C_FIELD(arg0, u32 *, 0x3C) >> 0x1F) + 7;
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        if (var_v1 >= 0xF) {
            var_v1 = 0xE;
        }
        temp_v0_10 = (u8) M2C_FIELD(temp_s0, s8 *, 0x50);
        if (var_v1 == temp_v0_10) {
            if (temp_v0_10 == M2C_FIELD(temp_s0, u8 *, 0x52)) {
                var_v0 = 0x1000;
                goto block_81;
            }
        } else {
            M2C_FIELD(temp_s0, s8 *, 0x50) = var_v1;
            var_v0 = 0x800;
block_81:
            M2C_FIELD(temp_s0, s16 *, 0x4E) = var_v0;
        }
        if ((s32) M2C_FIELD(arg0, u32 *, 0x3C) >= 0) {
            temp_v0_11 = M2C_FIELD(arg0, s32 *, 0x50);
            if ((M2C_FIELD(arg0, s32 *, 0x28) >= temp_v0_11) && (M2C_FIELD(temp_s1, s16 *, 0x18) & 0x10)) {
                M2C_FIELD(arg0, s32 *, 0x28) = temp_v0_11;
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x28);
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                D_8007CB70 = 0x14;
                M2C_FIELD(temp_s1, s8 *, 0x1D) = 0x10;
                M2C_FIELD(temp_s1, u8 *, 0x1A) = 0U;
                M2C_FIELD(temp_s1, u8 *, 0x1B) = 0U;
                TocarSonido(1, 0, 0x2A, 0x7F);
            }
        }
        break;
    case 16:                                        /* switch 1 */
        if (M2C_FIELD(temp_s0, u8 *, 0x53) == M2C_FIELD(temp_s4, u16 *, 0x28)) {
            if (func_8002EFD0(arg0) != 0) {
                M2C_FIELD(arg0, s32 *, 0x38) = 0;
                M2C_FIELD(arg0, u32 *, 0x3C) = 0U;
                M2C_FIELD(arg0, s32 *, 0x40) = 0;
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0);
                D_8007CB70 = 0;
                M2C_FIELD(temp_s1, u8 *, 0x1A) = -1U;
                M2C_FIELD(temp_s1, u8 *, 0x1B) = -1U;
                M2C_FIELD(temp_s1, s8 *, 0x1D) = 0;
            } else {
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            }
        }
        break;
    case 7:                                         /* switch 1 */
        if (M2C_FIELD(temp_s0, u8 *, 0x53) == M2C_FIELD(temp_s4, u16 *, 0xA)) {
            if (func_8002EFD0(arg0) != 0) {
                M2C_FIELD(arg0, s32 *, 0x38) = 0;
                M2C_FIELD(arg0, u32 *, 0x3C) = -0x2AAAU;
                M2C_FIELD(arg0, s32 *, 0x40) = 0;
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0xC);
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                D_8007CB70 = 6;
                M2C_FIELD(temp_s1, u8 *, 0x1A) = (u8) M2C_FIELD(temp_s0, s8 *, 0x50);
                M2C_FIELD(temp_s1, u8 *, 0x1B) = (u8) M2C_FIELD(temp_s0, s8 *, 0x50);
                M2C_FIELD(temp_s1, s8 *, 0x1D) = 9;
                M2C_FIELD(temp_s1, s32 *, 4) = 0x13A0;
            } else {
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            }
        }
        break;
    case 9:                                         /* switch 1 */
        temp_s2_6 = temp_s2 & 0xF000 & 0xFFFF;
        if ((temp_s2_6 != 0) && (M2C_FIELD(temp_s1, s8 *, 0x26) == 0)) {
            func_80032F90(arg0, temp_s2_6);
        }
        M2C_FIELD(temp_s1, u8 *, 0x1A) = -1U;
        M2C_FIELD(temp_s1, u8 *, 0x1B) = -1U;
        var_v1_2 = (M2C_FIELD(arg0, u32 *, 0x3C) / 1638) + ((u32) M2C_FIELD(arg0, u32 *, 0x3C) >> 0x1F) + 7;
        if (var_v1_2 < 0) {
            var_v1_2 = 0;
        }
        if (var_v1_2 >= 0xF) {
            var_v1_2 = 0xE;
        }
        temp_v0_12 = (u8) M2C_FIELD(temp_s0, s8 *, 0x50);
        if (var_v1_2 == temp_v0_12) {
            if (temp_v0_12 == M2C_FIELD(temp_s0, u8 *, 0x52)) {
                var_v0_2 = 0x1000;
                goto block_105;
            }
        } else {
            M2C_FIELD(temp_s0, s8 *, 0x50) = var_v1_2;
            var_v0_2 = 0x800;
block_105:
            M2C_FIELD(temp_s0, s16 *, 0x4E) = var_v0_2;
        }
        if ((s32) M2C_FIELD(arg0, u32 *, 0x3C) >= 0) {
            temp_v0_13 = M2C_FIELD(arg0, s32 *, 0x50);
            if ((M2C_FIELD(arg0, s32 *, 0x28) >= temp_v0_13) && (M2C_FIELD(temp_s1, s16 *, 0x18) & 0x10)) {
                M2C_FIELD(arg0, s32 *, 0x28) = temp_v0_13;
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0xE);
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                D_8007CB70 = 7;
                M2C_FIELD(temp_s1, s8 *, 0x1D) = 0xA;
                M2C_FIELD(temp_s1, u8 *, 0x1A) = 0U;
                M2C_FIELD(temp_s1, u8 *, 0x1B) = 0U;
                TocarSonido(1, 0, 0x2A, 0x7F);
            }
        }
        break;
    case 10:                                        /* switch 1 */
        if (M2C_FIELD(temp_s0, u8 *, 0x53) == M2C_FIELD(temp_s4, u16 *, 0xE)) {
            if (func_8002EFD0(arg0) != 0) {
                M2C_FIELD(arg0, s32 *, 0x38) = 0;
                M2C_FIELD(arg0, u32 *, 0x3C) = 0U;
                M2C_FIELD(arg0, s32 *, 0x40) = 0;
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0);
                D_8007CB70 = 0;
                M2C_FIELD(temp_s1, u8 *, 0x1A) = -1U;
                M2C_FIELD(temp_s1, u8 *, 0x1B) = -1U;
                M2C_FIELD(temp_s1, s8 *, 0x1D) = 0;
            } else {
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            }
        }
        break;
    case 8:                                         /* switch 1 */
        if (M2C_FIELD(temp_s1, s8 *, 0x21) == 0) {
            var_v1_3 = M2C_FIELD(temp_s4, u16 *, 0x10) << 0x18;
        } else {
            var_v1_3 = M2C_FIELD(temp_s4, u16 *, 0x12) << 0x18;
        }
        if (M2C_FIELD(temp_s0, u8 *, 0x53) == (var_v1_3 >> 0x18)) {
            if (func_8002EFD0(arg0) != 0) {
                if (M2C_FIELD(temp_s1, s8 *, 0x21) == 0) {
                    M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x14);
                    var_v0_3 = 0xA;
                } else {
                    M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x16);
                    var_v0_3 = 0xB;
                }
                D_8007CB70 = var_v0_3;
                M2C_FIELD(temp_s1, u8 *, 0x1A) = -1U;
                M2C_FIELD(temp_s1, u8 *, 0x1B) = -1U;
                M2C_FIELD(temp_s1, s8 *, 0x1D) = 0xB;
                M2C_FIELD(temp_s1, s32 *, 4) = 0x13A0;
            } else {
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            }
        }
        func_80032F90(arg0, temp_s2 & 0xF000 & 0xFFFF);
        M2C_FIELD(temp_s1, s16 *, 0x10) = (s16) (M2C_FIELD(temp_s1, s16 *, 0x10) + 1);
        break;
    case 11:                                        /* switch 1 */
        temp_s2_7 = temp_s2 & 0xF000 & 0xFFFF;
        if (temp_s2_7 != 0) {
            func_80032F90(arg0, temp_s2_7);
        }
        if (((M2C_FIELD(arg0, s32 *, 0x50) - 0x3333) < M2C_FIELD(arg0, s32 *, 0x28)) && ((s32) M2C_FIELD(arg0, u32 *, 0x3C) <= 0)) {
            M2C_FIELD(temp_s1, s8 *, 0x1D) = 0xC;
            M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 0x18);
            M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
            TocarSonido(1, 0, 0x2A, 0x7F);
            D_8007CB70 = 0xC;
        }
        break;
    case 12:                                        /* switch 1 */
        M2C_FIELD(arg0, u32 *, 0x3C) = 0U;
        if (M2C_FIELD(temp_s0, u8 *, 0x53) == M2C_FIELD(temp_s4, u16 *, 0x18)) {
            if (func_8002EFD0(arg0) != 0) {
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(temp_s4, u16 *, 4);
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                D_8007CB70 = 2;
                M2C_FIELD(temp_s1, s32 *, 4) = 0x13A0;
                M2C_FIELD(temp_s1, u8 *, 0x1A) = 3U;
                M2C_FIELD(temp_s1, u8 *, 0x1B) = 9U;
                M2C_FIELD(temp_s1, s8 *, 0x1D) = 5;
            } else {
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
            }
        }
        func_80032F90(arg0, temp_s2 & 0xF000 & 0xFFFF);
        M2C_FIELD(temp_s1, s16 *, 0x10) = (s16) (M2C_FIELD(temp_s1, s16 *, 0x10) + 1);
        break;
    default:                                        /* switch 1 */
        M2C_FIELD(arg0, s32 *, 0x38) = 0;
        M2C_FIELD(arg0, u32 *, 0x3C) = 0U;
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
        break;
    }
    temp_v0_14 = M2C_FIELD(temp_s1, s8 *, 0x1D);
    if ((temp_v0_14 != 0xD) && (temp_v0_14 != 0)) {
        func_80032F50(arg0);
    }
    M2C_FIELD(temp_s1, s16 *, 0x18) = 0;
    FisicaObjeto(arg0, 1);
}
