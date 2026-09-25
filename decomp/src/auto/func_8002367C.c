#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_8006CE10[];
extern u16 D_8006CE30[];
extern u16 D_8006CE40[];
extern u16 D_8006CE90[];
extern u16 D_8006CEB0[];
extern u8 D_8006CED0[];
extern u8 D_8006CEE0[];
extern u8 D_8006CEF0[];
extern s8 nivel_actual;
extern u8 D_8007CA38;
extern void * D_8007CACC;
extern s32 D_8007CAD0;
extern void * D_8007CAD4;
extern s32 D_8007CADC;
extern s16 D_8007CB1E;
extern s32 D_8007CB24;
extern s32 D_8007CB30;
extern s32 D_8007CB34;


void func_8002367C(s32 arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a1_2;
    s32 temp_a1_5;
    s32 temp_v0;
    u32 var_s1;
    u32 var_s1_2;
    u8 *temp_a0_4;
    void *temp_a1;
    void *temp_a1_3;
    void *temp_a1_4;
    void *temp_s0;
    void *temp_s0_2;

    if (D_8007CA38 == 0) {
        var_s1 = 0;
loop_10:
        if (var_s1 != 7) {
            if ((nivel_actual == 0xE) || (nivel_actual == 0xD)) {
                switch (var_s1) {                   /* switch 1 */
                case 0:                             /* switch 1 */
                case 1:                             /* switch 1 */
                case 3:                             /* switch 1 */
                    break;
                }
            } else {
            default:                                /* switch 1 */
            case 2:                                 /* switch 1 */
            case 4:                                 /* switch 1 */
            case 5:                                 /* switch 1 */
            case 6:                                 /* switch 1 */
                if ((D_8007CB30 == 0) || (var_s1 >= 2U)) {
                    temp_s0 = D_8006CE10[var_s1];
                    M2C_FIELD(D_8007CACC, u16 *, 8) = (u16) D_8006CE30[var_s1];
                    M2C_FIELD(D_8007CACC, u16 *, 0xA) = (u16) D_8006CE40[var_s1];
                    M2C_FIELD(D_8007CACC, s16 *, 0x10) = (s16) M2C_FIELD(temp_s0, s16 *, 8);
                    M2C_FIELD(D_8007CACC, s16 *, 0x12) = (s16) M2C_FIELD(temp_s0, s16 *, 0xA);
                    M2C_FIELD(D_8007CACC, u8 *, 4) = 0xFFU;
                    M2C_FIELD(D_8007CACC, u8 *, 5) = 0xFFU;
                    M2C_FIELD(D_8007CACC, u8 *, 6) = 0xFFU;
                    temp_a0 = arg0 + 0xC;
                    M2C_FIELD(D_8007CACC, u8 *, 0xD) = (u8) M2C_FIELD(temp_s0, u8 *, 0x11);
                    M2C_FIELD(D_8007CACC, u8 *, 0xC) = (u8) M2C_FIELD(temp_s0, u8 *, 0x10);
                    M2C_FIELD(D_8007CACC, u16 *, 0xE) = (u16) M2C_FIELD(temp_s0, u16 *, 0xE);
                    temp_a1 = D_8007CACC;
                    D_8007CACC = temp_a1 + 0x14;
                    AddPrim(temp_a0, (s32) temp_a1);
                    SetDrawTPage(D_8007CAD0, 1, 0, (s32) M2C_FIELD(temp_s0, u16 *, 0xC));
                    temp_a1_2 = D_8007CAD0;
                    D_8007CAD0 = temp_a1_2 + 8;
                    AddPrim(temp_a0, temp_a1_2);
                }
            }
            var_s1 = (var_s1 + 1) & 0xFFFF;
            goto loop_10;
        }
        temp_a0_2 = D_8007CB1E & 0xFFFF;
        temp_v0 = temp_a0_2 << 7;
        M2C_FIELD(D_8007CAD4, s8 *, 4) = (s8) ((s32) ((((0x100 - temp_a0_2) & 0xFFFF) << 7) + temp_v0) >> 8);
        temp_a0_3 = arg0 + 8;
        M2C_FIELD(D_8007CAD4, s8 *, 5) = (s8) (temp_v0 >> 8);
        M2C_FIELD(D_8007CAD4, s8 *, 6) = 0;
        M2C_FIELD(D_8007CAD4, s16 *, 8) = 0x20;
        M2C_FIELD(D_8007CAD4, s16 *, 0xA) = 0x16;
        M2C_FIELD(D_8007CAD4, s16 *, 0xC) = (s16) D_8007CB1E;
        M2C_FIELD(D_8007CAD4, s16 *, 0xE) = 0xC;
        M2C_FIELD(D_8007CAD4, u8 *, 7) = (u8) (M2C_FIELD(D_8007CAD4, u8 *, 7) | 2);
        temp_a1_3 = D_8007CAD4;
        D_8007CAD4 = temp_a1_3 + 0x10;
        AddPrim(temp_a0_3, (s32) temp_a1_3);
        AddPrim(temp_a0_3, D_8007CADC);
        return;
    }
    var_s1_2 = 0;
loop_20:
    if (var_s1_2 != 0x10) {
        if (D_8007CB34 == 0) {
            if ((nivel_actual == 0xE) || (nivel_actual == 0xD)) {
                switch (var_s1_2) {                 /* switch 2 */
                case 0:                             /* switch 2 */
                case 1:                             /* switch 2 */
                case 2:                             /* switch 2 */
                case 3:                             /* switch 2 */
                case 4:                             /* switch 2 */
                case 5:                             /* switch 2 */
                case 6:                             /* switch 2 */
                case 7:                             /* switch 2 */
                case 8:                             /* switch 2 */
                case 9:                             /* switch 2 */
                case 10:                            /* switch 2 */
                case 11:                            /* switch 2 */
                case 12:                            /* switch 2 */
                    break;
                }
            } else {
            default:                                /* switch 2 */
            case 13:                                /* switch 2 */
            case 14:                                /* switch 2 */
            case 15:                                /* switch 2 */
                temp_s0_2 = D_8007CB24 + (D_8006CEF0[var_s1_2] << 5);
                M2C_FIELD(D_8007CACC, u16 *, 8) = (u16) D_8006CE90[var_s1_2];
                M2C_FIELD(D_8007CACC, u16 *, 0xA) = (u16) D_8006CEB0[var_s1_2];
                M2C_FIELD(D_8007CACC, s16 *, 0x10) = (s16) M2C_FIELD(temp_s0_2, s16 *, 8);
                M2C_FIELD(D_8007CACC, s16 *, 0x12) = (s16) M2C_FIELD(temp_s0_2, s16 *, 0xA);
                temp_a0_4 = &D_8006CED0[var_s1_2];
                M2C_FIELD(D_8007CACC, u8 *, 4) = (u8) *temp_a0_4;
                M2C_FIELD(D_8007CACC, u8 *, 5) = (u8) *temp_a0_4;
                M2C_FIELD(D_8007CACC, u8 *, 6) = (u8) *temp_a0_4;
                M2C_FIELD(D_8007CACC, u8 *, 0xD) = (u8) M2C_FIELD(temp_s0_2, u8 *, 0x11);
                M2C_FIELD(D_8007CACC, u8 *, 0xC) = (u8) M2C_FIELD(temp_s0_2, u8 *, 0x10);
                M2C_FIELD(D_8007CACC, u16 *, 0xE) = (u16) M2C_FIELD(temp_s0_2, u16 *, 0xE);
                temp_a1_4 = D_8007CACC;
                D_8007CACC = temp_a1_4 + 0x14;
                AddPrim(arg0 + (D_8006CEE0[var_s1_2] * 4), (s32) temp_a1_4);
                SetDrawTPage(D_8007CAD0, 1, 0, (s32) M2C_FIELD(temp_s0_2, u16 *, 0xC));
                temp_a1_5 = D_8007CAD0;
                D_8007CAD0 = temp_a1_5 + 8;
                AddPrim(arg0 + (D_8006CEE0[var_s1_2] * 4), temp_a1_5);
            }
            var_s1_2 = (var_s1_2 + 1) & 0xFFFF;
            goto loop_20;
        }
    }
}
