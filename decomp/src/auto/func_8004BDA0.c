#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C8538[];
extern u8 D_800C86C6[];
extern s32 D_800C98A4;
extern u8 partida[];
extern s32 D_800757DC[];
extern s8 nivel_actual;
extern s8 D_8007CB28;
extern s8 D_8007CB3A;
extern u32 D_8007CB3C;
extern s32 D_8007CB40;


void func_8004BDA0(void) {
    s8 *sp0;
    s8 *sp4;
    s8 *sp8;
    s8 *spC;
    s8 *sp10;
    s8 *sp14;
    s8 *sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 *var_t7;
    s32 *var_t8;
    s32 temp_v1;
    s32 var_a2;
    s32 var_t9;
    u32 var_a1;
    void *temp_t6;
    void *temp_t6_2;
    void *temp_t6_3;
    void *temp_t6_4;
    void *temp_t6_5;
    void *temp_t6_6;
    void *temp_t6_7;
    void *temp_v0;

    var_t8 = D_800757DC;
    var_t7 = &sp1C;
    var_t9 = 7;
    do {
        var_t9 -= 1;
        *var_t7 = *var_t8;
        var_t8 += 4;
        var_t7 += 4;
    } while (var_t9 > 0);
    D_800C98A4 = (s32) nivel_actual;
    temp_v1 = nivel_actual * 0x141;
    D_8007CB3A = 0;
    D_8007CB28 = 0;
    *(D_800C86C6 + temp_v1) = 1;
    temp_v0 = partida + temp_v1;
    sp0 = temp_v0 + 0x6E;
    sp4 = temp_v0 + 0xB6;
    sp8 = temp_v0 + 0xFE;
    spC = temp_v0 + 0x146;
    sp10 = temp_v0 + 0x19E;
    sp14 = temp_v0 + 0x1A6;
    sp18 = temp_v0 + 0x18E;
    var_a2 = 0;
    M2C_FIELD(temp_v0, s8 *, 0x6E) = 0;
    *sp4 = 0;
    *sp8 = 0;
    *spC = 0;
    *sp10 = 0;
    *sp14 = 0;
    *sp18 = 0;
    var_a1 = 0;
loop_18:
    if (var_a1 < (u32) D_8007CB3C) {
        temp_t6 = var_a2 + D_8007CB40;
        if (M2C_FIELD(temp_t6, s16 *, 0xC) == 4) {
            M2C_FIELD(temp_t6, s32 *, 0x1C) = sp1C;
            sp1C += 1;
            *sp0 += 1;
        }
        temp_t6_2 = var_a2 + D_8007CB40;
        if (M2C_FIELD(temp_t6_2, s16 *, 0xC) == 0x12) {
            M2C_FIELD(temp_t6_2, s32 *, 0x1C) = sp20;
            sp20 += 1;
            *sp4 += 1;
        }
        temp_t6_3 = var_a2 + D_8007CB40;
        if (M2C_FIELD(temp_t6_3, s16 *, 0xC) == 0x13) {
            M2C_FIELD(temp_t6_3, s32 *, 0x1C) = sp24;
            sp24 += 1;
            *sp8 += 1;
        }
        temp_t6_4 = var_a2 + D_8007CB40;
        if (M2C_FIELD(temp_t6_4, s16 *, 0xC) == 0x17) {
            M2C_FIELD(temp_t6_4, s32 *, 0x1C) = sp28;
            sp28 += 1;
            *spC += 1;
        }
        temp_t6_5 = var_a2 + D_8007CB40;
        if (M2C_FIELD(temp_t6_5, s16 *, 0xC) == 0x28) {
            M2C_FIELD(temp_t6_5, s32 *, 0x1C) = sp2C;
            sp2C += 1;
            *sp10 += 1;
        }
        temp_t6_6 = var_a2 + D_8007CB40;
        if (M2C_FIELD(temp_t6_6, s16 *, 0xC) == 0x29) {
            M2C_FIELD(temp_t6_6, s32 *, 0x1C) = sp30;
            sp30 += 1;
            *sp14 += 1;
        }
        temp_t6_7 = var_a2 + D_8007CB40;
        if (M2C_FIELD(temp_t6_7, s16 *, 0xC) == 0x2D) {
            M2C_FIELD(temp_t6_7, s32 *, 0x1C) = sp34;
            sp34 += 1;
            *sp18 += 1;
        }
        var_a1 += 1;
        var_a2 += 0x9C;
        goto loop_18;
    }
    D_8007CB3A = *sp0;
    D_8007CB3A = (u8) D_8007CB3A + (*sp4 & 0xFF);
    D_8007CB3A = (u8) D_8007CB3A + (*sp8 & 0xFF);
    D_8007CB3A = (u8) D_8007CB3A + (*spC & 0xFF);
    *(D_800C8538 + (nivel_actual * 2)) = (s16) (u8) D_8007CB3A;
}
