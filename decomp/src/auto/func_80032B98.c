#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80074BC4[];
extern u8 D_80074BC8[];
extern u8 D_80074BD1[];
extern u8 hechizos[];
extern s8 D_8007C8B8[];
extern s8 nivel_actual;
extern s32 D_8007CA58;
extern s32 D_8007CB7C;
extern void * D_8007CB8C;
extern s32 func_80038E50();

u8 D_80074BC4[4];                                   /* unable to generate initializer: cannot parse func_80038E50 as integer */

void func_80032B98(s32 arg0, s32 arg1) {
    M2C_UNK (*temp_v0_7)(s32, s8, s32);
    s32 temp_s1;
    s32 temp_v1_5;
    s8 temp_v0;
    s8 temp_v0_2;
    s8 temp_v0_3;
    s8 temp_v0_4;
    s8 temp_v0_5;
    s8 temp_v0_6;
    s8 temp_v1;
    s8 temp_v1_2;
    s8 temp_v1_3;
    u8 *temp_v1_4;
    void *temp_s2;

    temp_s2 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
    temp_s1 = M2C_FIELD(arg1, s32 *, 8);
    if (D_8007CB7C == 0) {
        if (D_8007CA58 & 4) {
            temp_v0 = func_80022EF4(0xFF);
            if (temp_v0 >= 0) {
                M2C_FIELD(arg1, s8 *, 0x24) = temp_v0;
            }
        }
        if (D_8007CA58 & 8) {
            temp_v0_2 = func_80022EF4(1);
            if (temp_v0_2 >= 0) {
                M2C_FIELD(arg1, s8 *, 0x24) = temp_v0_2;
            }
        }
    }
    temp_v0_3 = M2C_FIELD(arg1, s8 *, 0x1E);
    switch (temp_v0_3) {
    case 0:
        if (temp_s1 & 0xA0) {
            if (temp_s1 & 0x20) {
                M2C_FIELD(arg1, s8 *, 0x22) = -1;
                if (nivel_actual != 0xD) {
                    temp_v1 = M2C_FIELD(arg1, s8 *, 0x24);
                    if ((s8) hechizos[temp_v1] != 0) {
                        M2C_FIELD(arg1, s8 *, 0x22) = temp_v1;
                        goto block_15;
                    }
                } else {
                    goto block_15;
                }
            } else {
                M2C_FIELD(arg1, s8 *, 0x22) = 8;
block_15:
                temp_v0_4 = M2C_FIELD(arg1, s8 *, 0x22);
                if ((temp_v0_4 >= 0) && ((s8) hechizos[temp_v0_4] != 0)) {
                    M2C_FIELD(arg1, s8 *, 0x1E) = 1;
                    func_8003012C();
                }
                goto block_18;
            }
        } else {
block_18:
            if (*D_8007C8B8 < 0x63) {
                temp_v1_2 = M2C_FIELD(arg1, s8 *, 0x25);
                M2C_FIELD(arg1, s8 *, 0x25) = (s8) (temp_v1_2 - 1);
                if (temp_v1_2 <= 0) {
                    temp_v1_3 = *D_8007C8B8;
                    *D_8007C8B8 = temp_v1_3 + 1;
                    M2C_FIELD(arg1, s8 *, 0x25) = (s8) (temp_v1_3 >> 2);
                    return;
                }
            }
        default:
            return;
        }
        break;
    case 1:
        if (func_8003015C() == 1) {
            M2C_FIELD(arg1, s8 *, 0x1E) = 2;
            return;
        }
        break;
    case 4:
        M2C_FIELD(arg1, s8 *, 0x1E) = 3;
        temp_v0_5 = M2C_FIELD(arg1, s8 *, 0x22);
        if ((temp_v0_5 >= 0) && ((s8) hechizos[temp_v0_5] != 0)) {
            M2C_FIELD(arg1, s8 *, 0x1E) = 2;
            return;
        }
        break;
    case 2:
        M2C_FIELD(arg1, s8 *, 0x1E) = 3;
        if (M2C_FIELD(arg1, s8 *, 0x23) <= 0) {
            temp_v1_4 = &hechizos[M2C_FIELD(arg1, s8 *, 0x22)];
            *temp_v1_4 = (s8) *temp_v1_4 - 1;
            temp_v0_6 = M2C_FIELD(arg1, s8 *, 0x22);
            temp_v1_5 = temp_v0_6 * 0x10;
            if (*(D_80074BC8 + temp_v1_5) > 0) {
                if (temp_v0_6 == 8) {
                    TocarSonido(2, 0, 0x2A, 0x7F);
                } else {
                    TocarSonido(3, 0, 0x2A, 0x7F);
                }
                func_800252A0(6, arg0, 0x4000, -0x10000, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 1, /* extra? */ (s32) M2C_FIELD(arg1, s8 *, 0x22), /* extra? */ 0);
            } else {
                temp_v0_7 = *(D_80074BC4 + temp_v1_5);
                if (temp_v0_7 != NULL) {
                    temp_v0_7(arg0, temp_v0_6, temp_v1_5);
                }
            }
            M2C_FIELD(arg1, s8 *, 0x23) = (s8) *(D_80074BD1 + (M2C_FIELD(arg1, s8 *, 0x22) * 0x10));
        }
        if (temp_s1 & 0xA0) {
            if (temp_s1 & 0x20) {
                M2C_FIELD(arg1, s8 *, 0x22) = (s8) M2C_FIELD(arg1, s8 *, 0x24);
                return;
            }
            M2C_FIELD(arg1, s8 *, 0x22) = 8;
            return;
        }
        M2C_FIELD(arg1, s8 *, 0x1E) = 3;
        return;
    case 3:
        if (func_8002EFD0((s32) D_8007CB8C) != 0) {
            M2C_FIELD(arg1, s8 *, 0x1E) = 0;
            M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) *M2C_FIELD(D_8007CB8C, u16 **, 0x64);
            M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
        }
        break;
    }
}
