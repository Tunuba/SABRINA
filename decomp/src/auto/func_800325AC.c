#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;
extern s16 D_8007CB38;
extern s16 D_8007CB70;
extern void * D_8007CB8C;
extern s32 D_8007CB9C;
extern s32 D_8007CBA0;


void func_800325AC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s5;
    s32 temp_v0_2;
    s8 temp_v0;
    s8 var_v0;
    u16 var_v0_2;
    u16 var_v0_3;
    u16 var_v0_4;
    u8 temp_v0_3;
    u8 temp_v0_4;
    void *temp_s1;
    void *temp_s3;
    void *temp_s4;

    temp_s3 = M2C_FIELD(D_8007CB8C, void **, 0x64);
    temp_s1 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
    temp_s4 = M2C_FIELD(arg0, void **, 0x64);
    temp_s5 = M2C_FIELD(arg1, s32 *, 8);
    if (nivel_actual == 0xE) {
        func_80033B1C(arg0, arg1, arg2);
    }
    temp_v0 = M2C_FIELD(arg1, s8 *, 0x1D);
    switch (temp_v0) {
    case 17:
        p_sabrina->escala[0] -= 0x64;
        if (p_sabrina->escala[0] < 3) {
            p_sabrina->escala[0] = 2;
        }
        p_sabrina->escala[1] = p_sabrina->escala[0];
        p_sabrina->escala[2] = p_sabrina->escala[0];
        M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
        M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
        M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
        if ((p_sabrina->escala[0] < 0xB) || ((u8) M2C_FIELD(arg2, u8 *, 0x50) >= 0x1EU)) {
            func_80030F18(D_8007CBA0);
            if ((D_8007CBA0 == 0x18) || (D_8007CBA0 == 0x1C) || (D_8007CBA0 == 0x1A)) {
                D_8007CB9C = 1;
            } else {
                D_8007CB38 = 0;
            }
            var_v0 = 0x13;
block_45:
            M2C_FIELD(arg1, s8 *, 0x1D) = var_v0;
        }
    default:
        return;
    case 19:
        p_sabrina->escala[0] += 0xFA;
        if ((func_8002EFD0(arg0) != 0) || (temp_v0_2 = p_sabrina->escala[0], ((temp_v0_2 < 0x1000) == 0))) {
            p_sabrina->escala[0] = 0x1666;
            p_sabrina->escala[2] = 0x1666;
            p_sabrina->escala[1] = 0x1000;
            M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
            M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
            M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
            M2C_FIELD(arg1, s8 *, 0x1D) = 0;
            M2C_FIELD(arg2, s8 *, 0x53) = (s8) M2C_FIELD(temp_s4, u16 *, 0);
            M2C_FIELD(arg2, u8 *, 0x52) = (u8) M2C_FIELD(arg2, u8 *, 0x50);
            M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0);
            M2C_FIELD(arg2, u8 *, 0x50) = 0U;
            M2C_FIELD(arg2, s16 *, 0x4C) = 0;
            M2C_FIELD(arg2, s16 *, 0x4E) = 0x800;
            M2C_FIELD(temp_s1, s8 *, 0x53) = (s8) M2C_FIELD(temp_s3, u16 *, 0);
            M2C_FIELD(temp_s1, u8 *, 0x52) = (u8) M2C_FIELD(temp_s1, u8 *, 0x50);
            M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0);
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4C) = 0;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
            D_8007CB70 = 0;
            return;
        }
        p_sabrina->escala[1] = temp_v0_2;
        p_sabrina->escala[2] = p_sabrina->escala[0];
        M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
        M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
        M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
        return;
    case 0:
        if (temp_s5 & 0x10) {
            M2C_FIELD(arg1, s8 *, 0x1D) = 0xD;
        }
        /* fallthrough */
    case 1:
    case 2:
    case 3:
        if (temp_s5 & 0x40) {
            if (temp_s5 & 0xF000) {
                temp_v0_3 = M2C_FIELD(arg2, u8 *, 0x50);
                if ((temp_v0_3 < 5U) || (temp_v0_3 >= 0xDU)) {
                    M2C_FIELD(arg1, s8 *, 0x21) = 0;
                    M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0x10);
                    var_v0_2 = M2C_FIELD(temp_s3, u16 *, 0x10);
                } else {
                    M2C_FIELD(arg1, s8 *, 0x21) = 1;
                    M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0x12);
                    var_v0_2 = M2C_FIELD(temp_s3, u16 *, 0x12);
                }
                M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) var_v0_2;
                M2C_FIELD(arg2, u8 *, 0x50) = 0U;
                M2C_FIELD(arg2, s16 *, 0x4E) = 0x800;
                M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
                M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
                M2C_FIELD(arg1, s8 *, 0x1D) = 8;
                M2C_FIELD(arg0, s32 *, 0x3C) = -0x2AAA;
            } else {
                M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0xA);
                M2C_FIELD(arg2, u8 *, 0x50) = 0U;
                M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0xA);
                M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
                M2C_FIELD(arg2, s16 *, 0x4E) = 0x800;
                M2C_FIELD(arg1, s8 *, 0x1D) = 7;
            }
        }
        if (M2C_FIELD(arg1, s16 *, 0x18) & 2) {
            M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0xC);
            M2C_FIELD(arg2, u8 *, 0x50) = 0U;
            M2C_FIELD(arg2, s16 *, 0x4E) = 0x800;
            M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0xC);
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
            M2C_FIELD(arg1, u8 *, 0x1A) = (u8) M2C_FIELD(arg2, u8 *, 0x50);
            M2C_FIELD(arg1, u8 *, 0x1B) = (u8) M2C_FIELD(arg2, u8 *, 0x50);
            M2C_FIELD(arg1, s32 *, 4) = 0x13A0;
            var_v0 = 9;
            goto block_45;
        }
        break;
    case 4:
    case 5:
    case 6:
        if (temp_s5 & 0x40) {
            if (temp_s5 & 0xF000) {
                temp_v0_4 = M2C_FIELD(arg2, u8 *, 0x50);
                if ((temp_v0_4 < 5U) || (temp_v0_4 >= 0xDU)) {
                    M2C_FIELD(arg1, s8 *, 0x21) = 0;
                    M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0x10);
                    var_v0_3 = M2C_FIELD(temp_s3, u16 *, 0x10);
                } else {
                    M2C_FIELD(arg1, s8 *, 0x21) = 1;
                    M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0x12);
                    var_v0_3 = M2C_FIELD(temp_s3, u16 *, 0x12);
                }
                M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) var_v0_3;
                M2C_FIELD(arg2, u8 *, 0x50) = 0U;
                M2C_FIELD(arg2, s16 *, 0x4E) = 0x800;
                M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
                M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
                M2C_FIELD(arg1, s8 *, 0x1D) = 8;
                M2C_FIELD(arg0, s32 *, 0x3C) = -0x2AAA;
            } else {
                M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0xA);
                M2C_FIELD(arg2, u8 *, 0x50) = 0U;
                M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0xA);
                M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
                M2C_FIELD(arg2, s16 *, 0x4E) = 0x800;
                M2C_FIELD(arg1, s8 *, 0x1D) = 7;
            }
        }
        if (M2C_FIELD(arg1, s16 *, 0x18) & 2) {
            if ((u8) M2C_FIELD(arg2, u8 *, 0x50) < 7U) {
                M2C_FIELD(arg1, s8 *, 0x21) = 0;
                M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0x14);
                var_v0_4 = M2C_FIELD(temp_s3, u16 *, 0x14);
            } else {
                M2C_FIELD(arg1, s8 *, 0x21) = 1;
                M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0x16);
                var_v0_4 = M2C_FIELD(temp_s3, u16 *, 0x16);
            }
            M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) var_v0_4;
            M2C_FIELD(arg2, u8 *, 0x50) = 0U;
            M2C_FIELD(arg2, s16 *, 0x4E) = 0x1000;
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x1000;
            M2C_FIELD(arg1, s32 *, 4) = 0x13A0;
            var_v0 = 0xB;
            goto block_45;
        }
        break;
    case 8:
    case 11:
    case 12:
    case 14:
    case 15:
        if (M2C_FIELD(arg1, s16 *, 0x18) & 8) {
            M2C_FIELD(arg2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0xC);
            M2C_FIELD(arg2, u8 *, 0x50) = 0U;
            M2C_FIELD(arg2, s16 *, 0x4E) = 0x800;
            M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0xC);
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
            M2C_FIELD(arg1, u8 *, 0x1A) = (u8) M2C_FIELD(arg2, u8 *, 0x50);
            M2C_FIELD(arg1, u8 *, 0x1B) = (u8) M2C_FIELD(arg2, u8 *, 0x50);
            M2C_FIELD(arg1, s32 *, 4) = 0x13A0;
            var_v0 = 9;
            goto block_45;
        }
        break;
    }
}
