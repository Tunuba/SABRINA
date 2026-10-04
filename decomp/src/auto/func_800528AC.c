#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8008AF88[];
extern u8 D_8008AFD8[];
extern s8 D_800C8566;
extern s8 nivel_actual;
extern void * D_8007CAFC;
extern void * D_8007CB8C;
extern s32 D_8007CC5C;
extern s32 D_8007CC60;
extern s32 func_80025064();
extern s32 func_80030208();
extern s32 func_80033AD8();
extern s32 func_80055CA4();
extern s32 func_80055CAC();


void func_800528AC(void *arg0) {
    s16 temp_v1;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    u8 *var_a2;
    u8 *var_v1;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    if (M2C_FIELD(temp_s1, u8 *, 0x24) != 0) {
        switch (nivel_actual) {                     /* switch 1 */
        case 1:                                     /* switch 1 */
        case 2:                                     /* switch 1 */
        case 3:                                     /* switch 1 */
            if (D_800C8566 != 1) {
                M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
                return;
            }
        default:                                    /* switch 1 */
block_11:
            if (D_8007CC5C != 0) {
                var_v1 = D_8008AFD8;
                var_a0 = 0;
                var_a2 = D_8008AFD8 + 0x74;
loop_20:
                if (var_a0 < 0x50) {
                    if (((s8) D_8008AF88[var_a0] != 0) && (M2C_FIELD(var_v1, u16 *, 0x22) == 0x1D)) {
                        if (M2C_FIELD(var_a2, s32 *, 0x18) == 6) {
                            M2C_FIELD(var_v1, u8 *, 0x20) = (u8) (M2C_FIELD(var_v1, u8 *, 0x20) | 0x80);
                        }
                        if (M2C_FIELD(var_a2, s32 *, 0x18) == 7) {
                            M2C_FIELD(var_v1, u8 *, 0x20) = (u8) (M2C_FIELD(var_v1, u8 *, 0x20) | 0x80);
                        }
                    }
                    var_a0 += 1;
                    var_v1 += 0x120;
                    var_a2 += 0x120;
                    goto loop_20;
                }
                D_8007CC5C = 0;
            }
            temp_v0 = func_800221FC(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0x28), M2C_FIELD(arg0, s32 *, 0x2C), p_sabrina->x, /* extra? */ p_sabrina->y, /* extra? */ p_sabrina->z);
            temp_v1 = M2C_FIELD(arg0, s16 *, 0x70);
            switch (temp_v1) {                      /* switch 2 */
            case 0:                                 /* switch 2 */
                if (temp_v0 < M2C_FIELD(temp_s1, s32 *, 8)) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 1;
                    return;
                }
                break;
            case 1:                                 /* switch 2 */
                M2C_FIELD(p_sabrina, s32 (**)(), 0x14) = func_80025064;
                M2C_FIELD(D_8007CB8C, s32 (**)(), 0x14) = func_80025064;
                p_sabrina->actualizar = (void (*)(Objeto *)) func_80025064;
                M2C_FIELD(D_8007CB8C, s32 (**)(), 0) = func_80025064;
                M2C_FIELD(p_sabrina->datos, s16 *, 0x1A) = 2;
                M2C_FIELD(M2C_FIELD(D_8007CB8C, void **, 0x6C), s16 *, 0x1A) = 2;
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
                temp_a1 = p_sabrina->x;
                p_sabrina->x = temp_a1 - ((s32) (temp_a1 - M2C_FIELD(temp_s1, s32 *, 0x18)) >> 3);
                p_sabrina->y -= (s32) (p_sabrina->y - M2C_FIELD(temp_s1, s32 *, 0x1C)) >> 3;
                p_sabrina->z -= (s32) (p_sabrina->z - M2C_FIELD(temp_s1, s32 *, 0x20)) >> 3;
                p_sabrina->escala[0] -= 0x8C;
                p_sabrina->escala[1] -= 0x8C;
                p_sabrina->escala[2] -= 0x8C;
                if (p_sabrina->escala[0] < 5) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 2;
                    p_sabrina->escala[0] = 5;
                    p_sabrina->escala[1] = 5;
                    p_sabrina->escala[2] = 5;
                    M2C_FIELD(p_sabrina, s32 (**)(), 0x14) = (s32 (*)()) func_80033AD8;
                    M2C_FIELD(D_8007CB8C, s32 (**)(), 0x14) = (s32 (*)()) func_80055CAC;
                    p_sabrina->actualizar = (void (*)(Objeto *)) func_80030208;
                    M2C_FIELD(D_8007CB8C, s32 (**)(), 0) = func_80055CA4;
                    if (D_8007CC60 == 0) {
                        D_8007CC60 = 0x640000;
                    } else {
                        D_8007CC60 = 0;
                    }
                }
                M2C_FIELD(D_8007CB8C, s32 *, 0x24) = (s32) p_sabrina->x;
                M2C_FIELD(D_8007CB8C, s32 *, 0x28) = (s32) p_sabrina->y;
                M2C_FIELD(D_8007CB8C, s32 *, 0x2C) = (s32) p_sabrina->z;
                M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
                M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
                M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
                func_80033AD8((s32) p_sabrina);
                func_80055CAC((s32) D_8007CB8C);
                return;
            case 2:                                 /* switch 2 */
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
                p_sabrina->x = M2C_FIELD(temp_s1, s32 *, 0xC);
                p_sabrina->y = M2C_FIELD(temp_s1, s32 *, 0x10);
                p_sabrina->z = M2C_FIELD(temp_s1, s32 *, 0x14);
                M2C_FIELD(D_8007CAFC, s32 *, 0x24) = (s32) M2C_FIELD(temp_s1, s32 *, 0xC);
                M2C_FIELD(D_8007CAFC, s32 *, 0x28) = (s32) M2C_FIELD(temp_s1, s32 *, 0x10);
                M2C_FIELD(D_8007CAFC, s32 *, 0x2C) = (s32) M2C_FIELD(temp_s1, s32 *, 0x14);
                M2C_FIELD(D_8007CB8C, s32 *, 0x24) = (s32) M2C_FIELD(temp_s1, s32 *, 0xC);
                M2C_FIELD(D_8007CB8C, s32 *, 0x28) = (s32) M2C_FIELD(temp_s1, s32 *, 0x10);
                M2C_FIELD(D_8007CB8C, s32 *, 0x2C) = (s32) M2C_FIELD(temp_s1, s32 *, 0x14);
                M2C_FIELD(D_8007CAFC, s32 *, 0x28) = (s32) (M2C_FIELD(D_8007CAFC, s32 *, 0x28) + 0xFFFC0000);
                M2C_FIELD(arg0, s16 *, 0x70) = 3;
                func_800350A4((s32) &p_sabrina->x);
                func_80037278((s32) D_8007CAFC, (s32) p_sabrina);
                return;
            case 3:                                 /* switch 2 */
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
                temp_v0_2 = p_sabrina->escala[0];
                if (temp_v0_2 < 0x1000) {
                    p_sabrina->escala[0] = temp_v0_2 + 0x9B;
                    p_sabrina->escala[1] += 0x9B;
                    p_sabrina->escala[2] += 0x9B;
                    return;
                }
                M2C_FIELD(arg0, s16 *, 0x70) = 0;
                p_sabrina->escala[0] = 0x1666;
                p_sabrina->escala[1] = 0x1000;
                p_sabrina->escala[2] = 0x1666;
                break;
            }
            break;
        case 4:                                     /* switch 1 */
        case 5:                                     /* switch 1 */
        case 6:                                     /* switch 1 */
            if (D_800C8566 != 4) {
                M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
                return;
            }
            goto block_11;
        case 7:                                     /* switch 1 */
        case 8:                                     /* switch 1 */
        case 9:                                     /* switch 1 */
            if (D_800C8566 != 3) {
                M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
                return;
            }
            goto block_11;
        case 10:                                    /* switch 1 */
        case 11:                                    /* switch 1 */
        case 12:                                    /* switch 1 */
            if (D_800C8566 != 2) {
                M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
                return;
            }
            goto block_11;
        }
    } else {
    default:                                        /* switch 2 */
    }
}
