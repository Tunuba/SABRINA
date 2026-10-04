#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086324[];
extern s8 D_800C8566;
extern s8 D_800C8582;
extern s8 D_800C8583;
extern s8 D_800C8584;
extern s8 D_800C8585;
extern u16 D_8007C8C6;
extern s8 nivel_actual;
extern s16 D_8007CA20;
extern void * D_8007CAFC;
extern s32 D_8007CB30;
extern void * D_8007CBAC;
extern void * D_8007CBB0;
extern s32 D_8007CC64;
extern s32 D_8007CC68;


void func_80054068(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_v0_5;
    s32 temp_v0_7;
    s32 temp_v0_9;
    u8 var_v0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s0;
    void *temp_v0_2;
    void *temp_v0_4;
    void *temp_v0_6;
    void *temp_v0_8;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s0 = arg0 + 0x74;
    if (temp_v0 != 7) {
        if (temp_v0 != 4) {
            if (temp_v0 != 3) {
                if (temp_v0 == 5) {
                    if (nivel_actual != 0xC) {
                        if (nivel_actual != 9) {
                            if (nivel_actual != 6) {
                                if ((nivel_actual == 3) && (D_800C8582 == 2)) {
                                    M2C_FIELD(arg0, s16 *, 0x70) = 0;
                                    var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
                                    goto block_16;
                                }
                            } else if (D_800C8583 == 2) {
                                M2C_FIELD(arg0, s16 *, 0x70) = 0;
                                var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
                                goto block_16;
                            }
                        } else if (D_800C8584 == 2) {
                            M2C_FIELD(arg0, s16 *, 0x70) = 0;
                            var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
                            goto block_16;
                        }
                    } else if (D_800C8585 == 2) {
                        M2C_FIELD(arg0, s16 *, 0x70) = 0;
                        var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
block_16:
                        M2C_FIELD(arg0, u8 *, 0x20) = var_v0;
                    }
                    func_800486B8((s32) arg0, 0x2D0000);
                    if (M2C_FIELD(temp_s0, s32 *, 0x20) == 0) {
                        if (func_80053B98((s32) temp_s0, p_sabrina->x, p_sabrina->y, p_sabrina->z, /* extra? */ 1) == 1) {
                            D_8007CBAC = arg0;
                        }
                    } else if (D_8007CBAC != NULL) {
                        D_8007CBB0 = arg0;
                    }
                }
            } else if (D_8007CC64 == 4) {
                D_800C8584 = 1;
            }
        } else {
            func_800486B8((s32) arg0, 0x1E0000);
            if (M2C_FIELD(temp_s0, void **, 0x30) == NULL) {
                temp_v0_2 = *(D_80086324 + (M2C_FIELD(temp_s0, s32 *, 0x28) * 4));
                if (temp_v0_2 != NULL) {
                    M2C_FIELD(temp_s0, void **, 0x30) = temp_v0_2;
                    M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x30), void **, 0x8C) = arg0;
                }
            }
        }
    } else if ((M2C_FIELD(temp_s0, s32 *, 0x20) == 0) && (func_80053B98((s32) temp_s0, p_sabrina->x, p_sabrina->y, p_sabrina->z, /* extra? */ 1) == 1)) {
        func_8003DDA0(M2C_FIELD(temp_s0, s32 *, 0x1C), 0);
        func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
        M2C_FIELD(temp_s0, s32 *, 0x20) = 1;
    }
    temp_v0_3 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0_3) {                            /* switch 1 */
    case 5:                                         /* switch 1 */
        if ((M2C_FIELD(temp_s0, s32 *, 0x20) == 0) && (func_80053B98((s32) temp_s0, p_sabrina->x, p_sabrina->y, p_sabrina->z, /* extra? */ 1) == 1)) {
            M2C_FIELD(D_8007CAFC, s16 *, 0x70) = 4;
            M2C_FIELD(arg0, s16 *, 0x70) = 0;
            D_8007CB30 = 1;
            return;
        }
    default:                                        /* switch 1 */
        return;
    case 4:                                         /* switch 1 */
        if ((M2C_FIELD(temp_s0, s32 *, 0x2C) != 0) && (M2C_FIELD(temp_s0, void **, 0x30) != NULL) && (func_80053B98((s32) temp_s0, p_sabrina->x, p_sabrina->y, p_sabrina->z, /* extra? */ 1) == 1)) {
            temp_v0_4 = M2C_FIELD(temp_s0, void **, 0x30);
            M2C_FIELD(temp_s0, s32 *, 0x2C) = 0;
            M2C_FIELD((temp_v0_4 + 0x74), s32 *, 8) = (s32) M2C_FIELD(temp_v0_4, s32 *, 0x74);
        }
        if ((M2C_FIELD(temp_s0, s32 *, 0x2C) == 0) && (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x30), s16 *, 0x70) == 0)) {
            M2C_FIELD(temp_s0, s32 *, 0x2C) = 1;
            return;
        }
        break;
    case 8:                                         /* switch 1 */
        if ((M2C_FIELD(temp_s0, s32 *, 0x20) != 0) && (M2C_FIELD(temp_s0, s32 *, 0x24) == 0)) {
            M2C_FIELD(temp_s0, s32 *, 0x24) = 0xC8;
            D_8007CA20 = 0x3B;
            func_80053F74(M2C_FIELD(temp_s0, s32 *, 0x34));
            D_8007CC68 = 0xC8;
            return;
        }
        temp_v0_5 = M2C_FIELD(temp_s0, s32 *, 0x24);
        if (temp_v0_5 == 0) {
            if (func_80053B98((s32) temp_s0, p_sabrina->x, p_sabrina->y, p_sabrina->z, /* extra? */ 1) == 1) {
                M2C_FIELD(temp_s0, s32 *, 0x20) = 1;
                return;
            }
        } else {
            M2C_FIELD(temp_s0, s32 *, 0x24) = (s32) (temp_v0_5 - 1);
            if (M2C_FIELD(temp_s0, s32 *, 0x24) == 0) {
                M2C_FIELD(temp_s0, s32 *, 0x20) = 0;
                temp_v0_6 = M2C_FIELD(arg0, void **, 0x6C);
                temp_a0 = temp_v0_6 + 0x1C;
                M2C_FIELD(temp_v0_6, s32 *, 0x1C) = 0;
                M2C_FIELD(temp_a0, s32 *, 8) = 0;
                M2C_FIELD(temp_a0, s32 *, 4) = 0x640000;
                M2C_FIELD(temp_a0, s32 *, 0xC) = 0;
                M2C_FIELD(temp_a0, s32 *, 0x14) = 0;
                M2C_FIELD(temp_a0, s32 *, 0x10) = 0x640000;
                M2C_FIELD(arg0, s32 *, 0x74) = 0;
                M2C_FIELD(temp_s0, s32 *, 8) = 0;
                M2C_FIELD(temp_s0, s32 *, 4) = 0x640000;
                M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
                M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
                M2C_FIELD(temp_s0, s32 *, 0x10) = 0x640000;
                M2C_FIELD(arg0, s16 *, 0x70) = 0;
                return;
            }
        }
        break;
    case 6:                                         /* switch 1 */
        if (M2C_FIELD(temp_s0, s32 *, 0x28) == 1) {
            switch (nivel_actual) {                 /* switch 2 */
            case 1:                                 /* switch 2 */
            case 2:                                 /* switch 2 */
            case 3:                                 /* switch 2 */
                if (D_800C8566 == 1) {
                    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
                    return;
                }
                goto block_61;
            case 4:                                 /* switch 2 */
            case 5:                                 /* switch 2 */
            case 6:                                 /* switch 2 */
                if (D_800C8566 == 4) {
                    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
                    return;
                }
                goto block_61;
            case 7:                                 /* switch 2 */
            case 8:                                 /* switch 2 */
            case 9:                                 /* switch 2 */
                if (D_800C8566 == 3) {
                    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
                    return;
                }
                goto block_61;
            case 10:                                /* switch 2 */
            case 11:                                /* switch 2 */
            case 12:                                /* switch 2 */
                if (D_800C8566 == 2) {
                    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
                    return;
                }
                goto block_61;
            }
        } else {
        default:                                    /* switch 2 */
block_61:
            if ((M2C_FIELD(temp_s0, s32 *, 0x20) != 0) && (M2C_FIELD(temp_s0, s32 *, 0x24) == 0)) {
                M2C_FIELD(temp_s0, s32 *, 0x24) = 0xC8;
                D_8007CA20 = 0x3B;
                func_80053F74(M2C_FIELD(temp_s0, s32 *, 0x34));
                D_8007CC68 = 0xC8;
                return;
            }
            temp_v0_7 = M2C_FIELD(temp_s0, s32 *, 0x24);
            if (temp_v0_7 == 0) {
                if (func_80053B98((s32) temp_s0, p_sabrina->x, p_sabrina->y, p_sabrina->z, /* extra? */ 1) == 1) {
                    M2C_FIELD(temp_s0, s32 *, 0x20) = 1;
                    return;
                }
            } else {
                M2C_FIELD(temp_s0, s32 *, 0x24) = (s32) (temp_v0_7 - 1);
                if (M2C_FIELD(temp_s0, s32 *, 0x24) == 0) {
                    M2C_FIELD(temp_s0, s32 *, 0x20) = 0;
                    temp_v0_8 = M2C_FIELD(arg0, void **, 0x6C);
                    temp_a0_2 = temp_v0_8 + 0x1C;
                    M2C_FIELD(temp_v0_8, s32 *, 0x1C) = 0;
                    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
                    M2C_FIELD(temp_a0_2, s32 *, 4) = 0x640000;
                    M2C_FIELD(temp_a0_2, s32 *, 0xC) = 0;
                    M2C_FIELD(temp_a0_2, s32 *, 0x14) = 0;
                    M2C_FIELD(temp_a0_2, s32 *, 0x10) = 0x640000;
                    M2C_FIELD(arg0, s32 *, 0x74) = 0;
                    M2C_FIELD(temp_s0, s32 *, 8) = 0;
                    M2C_FIELD(temp_s0, s32 *, 4) = 0x640000;
                    M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
                    M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
                    M2C_FIELD(temp_s0, s32 *, 0x10) = 0x640000;
                    M2C_FIELD(arg0, s16 *, 0x70) = 0;
                    return;
                }
            }
        }
        break;
    case 7:                                         /* switch 1 */
        if ((M2C_FIELD(temp_s0, s32 *, 0x20) != 0) && ((temp_v0_9 = func_8003E060(), (temp_v0_9 != M2C_FIELD(temp_s0, s32 *, 0x1C))) || (temp_v0_9 == -1))) {
            func_8003DDFC();
            M2C_FIELD(arg0, s16 *, 0x70) = 0;
        }
        break;
    }
}
