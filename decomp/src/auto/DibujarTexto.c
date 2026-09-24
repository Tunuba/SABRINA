#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800798BC[];
extern u8 D_80079D48[];
extern u16 D_8007C7A0;
extern u16 D_8007C7A2;
extern u16 D_8007C7A4;
extern s32 D_8007CA10;
extern void * D_8007CACC;
extern s32 D_8007CAD0;

u8 D_800798BC[0x48C];                               /* unable to generate initializer: cannot parse D_80076B0C as integer */
u8 D_80079D48[0xEC];                                /* unable to generate initializer: cannot parse D_8007C938 as integer */

void DibujarTexto(s32 arg0, s32 arg1) {
    s8 *sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s16 var_s3;
    s32 temp_a1;
    s32 temp_a1_3;
    s32 temp_s6;
    s32 temp_s7;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_v0;
    s32 var_v1;
    s8 temp_v1;
    s8 temp_v1_2;
    u16 temp_s3;
    u16 temp_s4;
    u16 temp_s5;
    u16 temp_v0_2;
    u16 var_a0;
    void *temp_a0;
    void *temp_a1_2;
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_v0;
    void *var_s1;

    sp40 = arg1 * 4;
    temp_s6 = arg0 + 8;
    do {
        var_s1 = D_800798BC[sp40];
        sp3C = D_80079D48[sp40];
        if (var_s1 != NULL) {
            temp_s3 = M2C_FIELD(var_s1, u16 *, 0);
            temp_v0 = var_s1 + 2;
            temp_v0_2 = M2C_FIELD(var_s1, u16 *, 2);
            temp_s4 = M2C_FIELD(temp_v0, u16 *, 2);
            temp_s1 = temp_v0 + 2 + 2 + 2;
            temp_s1_2 = temp_s1 + 2;
            temp_a0 = temp_s1_2 + 2;
            sp44 = (s32) M2C_FIELD(temp_s1, u16 *, 2);
            sp48 = (s32) M2C_FIELD(temp_s1_2, u16 *, 2);
            temp_s1_3 = temp_a0 + 2 + 2 + 2 + 2;
            temp_s1_4 = temp_s1_3 + 2;
            sp4C = (s32) M2C_FIELD(temp_a0, u16 *, 2);
            temp_s5 = M2C_FIELD(temp_s1_3, u16 *, 2);
            var_s1 = temp_s1_4 + 2;
            var_a0 = M2C_FIELD(temp_s1_4, u16 *, 2);
            if (var_a0 == 0) {
                var_s2 = 0;
loop_8:
                if (var_s2 != temp_s5) {
                    temp_v1 = sp3C[var_s2];
                    if (temp_v1 == 0x7E) {
                        var_v1 = var_a0 + 7;
                    } else {
                        var_v1 = var_a0 + M2C_FIELD((D_8007CA10 + (temp_v1 * 0xC)), u8 *, 5);
                    }
                    var_a0 = var_v1 & 0xFFFF;
                    var_s2 = (var_s2 + 1) & 0xFFFF;
                    goto loop_8;
                }
                var_a0 = (var_a0 >> 1) & 0xFFFF;
                M2C_FIELD(temp_s1_4, u16 *, 2) = var_a0;
            }
            var_s3 = (temp_s3 - var_a0) & 0xFFFF;
            var_s2_2 = 0;
            temp_s7 = 0x1000 - temp_s4;
loop_15:
            if (var_s2_2 != temp_s5) {
                temp_v1_2 = *sp3C;
                temp_s0 = D_8007CA10 + (temp_v1_2 * 0xC);
                if (temp_v1_2 == 0x7E) {
                    var_v0 = var_s3 + 7;
                } else {
                    temp_a1 = temp_s7 & 0xFFFF;
                    M2C_FIELD(D_8007CACC, s16 *, 8) = var_s3;
                    M2C_FIELD(D_8007CACC, s16 *, 0xA) = (s16) (temp_v0_2 - 0x10);
                    M2C_FIELD(D_8007CACC, s16 *, 0x10) = (s16) M2C_FIELD(temp_s0, u8 *, 0xA);
                    M2C_FIELD(D_8007CACC, s16 *, 0x12) = 0x20;
                    M2C_FIELD(D_8007CACC, s8 *, 0xD) = (s8) M2C_FIELD(temp_s0, s8 *, 9);
                    M2C_FIELD(D_8007CACC, s8 *, 0xC) = (s8) M2C_FIELD(temp_s0, s8 *, 8);
                    M2C_FIELD(D_8007CACC, u16 *, 0xE) = (u16) M2C_FIELD(temp_s0, u16 *, 6);
                    M2C_FIELD(D_8007CACC, s8 *, 4) = (s8) ((s32) ((sp44 * temp_a1) + (D_8007C7A0 * temp_s4)) >> 0xC);
                    M2C_FIELD(D_8007CACC, s8 *, 5) = (s8) ((s32) ((sp48 * temp_a1) + (D_8007C7A2 * temp_s4)) >> 0xC);
                    M2C_FIELD(D_8007CACC, s8 *, 6) = (s8) ((s32) ((sp4C * temp_a1) + (D_8007C7A4 * temp_s4)) >> 0xC);
                    temp_a1_2 = D_8007CACC;
                    D_8007CACC = temp_a1_2 + 0x14;
                    AddPrim(temp_s6, (s32) temp_a1_2);
                    SetDrawTPage(D_8007CAD0, 1, 0, (s32) M2C_FIELD(temp_s0, u8 *, 4));
                    temp_a1_3 = D_8007CAD0;
                    D_8007CAD0 = temp_a1_3 + 8;
                    AddPrim(temp_s6, temp_a1_3);
                    var_v0 = var_s3 + M2C_FIELD(temp_s0, u8 *, 5);
                }
                var_s3 = var_v0 & 0xFFFF;
                sp3C += 1;
                var_s2_2 = (var_s2_2 + 1) & 0xFFFF;
                goto loop_15;
            }
        }
        arg1 = (arg1 + 1) & 0xFFFF;
        sp40 += 4;
    } while (var_s1 != NULL);
}
