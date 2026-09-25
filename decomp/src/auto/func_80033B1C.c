#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007C8A8;
extern u16 D_8007C92C;
extern s16 D_8007CB38;
extern s16 D_8007CB70;
extern void * D_8007CB8C;
extern s32 D_8007CB90;
extern s32 D_8007CB98;
extern s32 D_8007CB9C;
extern s32 D_8007CBA0;


void func_80033B1C(s32 arg0, s32 arg1, s32 arg2) {
    s16 var_v0;
    s32 temp_s6;
    s32 var_v1;
    u16 *temp_s4;
    u16 *temp_s5;
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;
    void *temp_s0;
    void *temp_s2;

    temp_s5 = M2C_FIELD(D_8007CB8C, u16 **, 0x64);
    temp_s0 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
    temp_s4 = M2C_FIELD(arg0, u16 **, 0x64);
    temp_s6 = M2C_FIELD(arg1, s32 *, 8);
    temp_s2 = D_8007CB90 + 0x74;
    if ((D_8007CB90 != 0) || (D_8007CB90 = func_8002506C(arg0 + 0x24, 0x1C, arg0), (D_8007CB90 != 0))) {
        temp_v0 = M2C_FIELD(temp_s2, u16 *, 0x3C);
        if (((temp_v0 == 3) || (temp_v0 == 4)) && (D_8007C8A8 < 6)) {
            D_8007CB98 -= 1;
            if (D_8007CB98 <= 0) {
                if (D_8007C8A8 != 4) {
                    D_8007C8A8 += 1;
                }
                D_8007CB98 = D_8007C8A8;
                D_8007C92C += 1;
                if ((u16) D_8007C92C >= 3U) {
                    D_8007C92C = 0;
                }
                if (D_8007C8A8 >= 5) {
                    D_8007C8A8 = 5;
                }
            }
            switch (D_8007C92C) {                   /* switch 1; irregular */
            case 0:                                 /* switch 1 */
                var_v0 = 2;
block_18:
                D_8007CB38 = var_v0;
                break;
            case 1:                                 /* switch 1 */
                var_v0 = 1;
                goto block_18;
            case 2:                                 /* switch 1 */
                var_v0 = 3;
                goto block_18;
            }
            if (D_8007C8A8 >= 5) {
                var_v1 = 0;
                switch (D_8007C92C) {               /* switch 2; irregular */
                case 2:                             /* switch 2 */
                    break;
                case 0:                             /* switch 2 */
                    var_v1 = 1;
                    break;
                case 1:                             /* switch 2 */
                    var_v1 = 2;
                    break;
                }
                if (var_v1 != M2C_FIELD(temp_s2, u16 *, 0x3A)) {
                    switch (D_8007C92C) {           /* switch 3; irregular */
                    case 0:                         /* switch 3 */
                        D_8007CB38 = 2;
                        D_8007CBA0 = 0x1A;
                        D_8007C92C = 1;
                        break;
                    case 1:                         /* switch 3 */
                        D_8007CB38 = 1;
                        D_8007CBA0 = 0x1C;
                        D_8007C92C = 2;
                        break;
                    case 2:                         /* switch 3 */
                        D_8007CB38 = 3;
                        D_8007CBA0 = 0x18;
                        D_8007C92C = 0;
                        break;
                    default:                        /* switch 3 */
                        D_8007CB38 = 3;
                        break;
                    }
                    M2C_FIELD(arg1, s8 *, 0x1D) = 0x11;
                    D_8007C8A8 = 0x64;
                    M2C_FIELD(arg2, u8 *, 0x53) = (u8) M2C_FIELD(arg2, u8 *, 0x51);
                    M2C_FIELD(arg2, u8 *, 0x52) = (u8) M2C_FIELD(arg2, u8 *, 0x50);
                    M2C_FIELD(arg2, u8 *, 0x51) = (u8) *temp_s4;
                    M2C_FIELD(arg2, u8 *, 0x50) = 0U;
                    M2C_FIELD(arg2, s16 *, 0x4C) = 0;
                    M2C_FIELD(arg2, s16 *, 0x4E) = 0x800;
                    M2C_FIELD(temp_s0, u8 *, 0x53) = (u8) M2C_FIELD(temp_s0, u8 *, 0x51);
                    M2C_FIELD(temp_s0, u8 *, 0x52) = (u8) M2C_FIELD(temp_s0, u8 *, 0x50);
                    M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) *temp_s5;
                    M2C_FIELD(temp_s0, u8 *, 0x50) = 0U;
                    M2C_FIELD(temp_s0, s16 *, 0x4C) = 0;
                    M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                    D_8007CB70 = 0;
                }
            }
            if ((temp_s6 & 0x40) && (D_8007C8A8 == 4)) {
                D_8007C8A8 = 5;
                TocarSonido(0x2F, 0, 0x2A, 0x7F);
            }
        }
        temp_v0_2 = M2C_FIELD(temp_s2, u16 *, 0x3C);
        if ((temp_v0_2 == 4) || (temp_v0_2 == 4)) {
            D_8007CBA0 = 2;
            D_8007CB9C = 0;
            M2C_FIELD(arg1, s8 *, 0x1D) = 0x11;
            temp_v1 = M2C_FIELD(arg2, u8 *, 0x51);
            if (temp_v1 != *temp_s4) {
                M2C_FIELD(arg2, u8 *, 0x53) = temp_v1;
                M2C_FIELD(arg2, u8 *, 0x52) = (u8) M2C_FIELD(arg2, u8 *, 0x50);
                M2C_FIELD(arg2, u8 *, 0x51) = (u8) *temp_s4;
                M2C_FIELD(arg2, u8 *, 0x50) = 0U;
                M2C_FIELD(arg2, s16 *, 0x4C) = 0;
                M2C_FIELD(arg2, s16 *, 0x4E) = 0x800;
                M2C_FIELD(temp_s0, u8 *, 0x53) = (u8) M2C_FIELD(temp_s0, u8 *, 0x51);
                M2C_FIELD(temp_s0, u8 *, 0x52) = (u8) M2C_FIELD(temp_s0, u8 *, 0x50);
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) *temp_s5;
                M2C_FIELD(temp_s0, u8 *, 0x50) = 0U;
                M2C_FIELD(temp_s0, s16 *, 0x4C) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
                D_8007CB70 = 0;
            }
        }
    }
}
