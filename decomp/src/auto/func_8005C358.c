#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA20;
extern s32 D_8007CA30;
extern s32 D_8007CA50;
extern s32 D_8007CB7C;
extern s32 D_8007CC78;


void func_8005C358(void *arg0) {
    s32 sp2C;
    s32 sp34;
    s16 temp_v0_2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_v0;
    s32 temp_v0_3;
    void *temp_s0;
    void *temp_s2;
    void *temp_s3;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;

    temp_s3 = M2C_FIELD(arg0, void **, 0x64);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s0 = arg0 + 0x74;
    D_8007CB7C = 0;
    if (p_sabrina != NULL) {
        func_80021D44((s32) (arg0 + 0x32), (s32) func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z), 0xAA);
        if (D_8007CA30 & 1) {
            if (func_8002225C((s32) arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z) < 0x28000) {
                if (M2C_FIELD(arg0, s16 *, 0x70) == 0) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 1;
                    func_8005BA10((s32) arg0);
                    M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                    M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0);
                    goto block_7;
                }
            } else if (M2C_FIELD(arg0, s16 *, 0x70) != 0) {
                M2C_FIELD(arg0, s16 *, 0x70) = 2;
                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 2);
block_7:
                M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
            }
        }
        if (M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x1C) * 4) + temp_s0), s32 *, 0x3C) != 0) {
            func_8002205C((s32) &sp2C, 0, (s32) M2C_FIELD(arg0, s16 *, 0x32));
            sp2C = ((s32) ((sp2C >> 4) * 0x66) >> 8) << 8;
            sp34 = ((s32) ((sp34 >> 4) * 0x66) >> 8) << 8;
            M2C_FIELD(M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x1C) * 4) + temp_s0), void **, 0x3C), s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + sp2C);
            M2C_FIELD(M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x1C) * 4) + temp_s0), void **, 0x3C), s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + sp34);
            M2C_FIELD(M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x1C) * 4) + temp_s0), void **, 0x3C), s16 *, 0x32) = (s16) M2C_FIELD(arg0, s16 *, 0x32);
            temp_v1 = M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x1C) * 4) + temp_s0), void **, 0x3C);
            temp_v0 = M2C_FIELD(temp_v1, s32 *, 0x54);
            if (temp_v0 < 0x1130) {
                M2C_FIELD(temp_v1, s32 *, 0x54) = (s32) (temp_v0 + 0x12C);
                temp_v1_2 = M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x1C) * 4) + temp_s0), void **, 0x3C);
                M2C_FIELD(temp_v1_2, s32 *, 0x58) = (s32) M2C_FIELD(temp_v1_2, s32 *, 0x54);
                temp_v1_3 = M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x1C) * 4) + temp_s0), void **, 0x3C);
                M2C_FIELD(temp_v1_3, s32 *, 0x5C) = (s32) M2C_FIELD(temp_v1_3, s32 *, 0x54);
            } else {
                M2C_FIELD(temp_v1, s32 *, 0x54) = 0x1130;
                M2C_FIELD(M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x1C) * 4) + temp_s0), void **, 0x3C), s32 *, 0x58) = 0x1130;
                M2C_FIELD(M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x1C) * 4) + temp_s0), void **, 0x3C), s32 *, 0x5C) = 0x1130;
            }
        }
    }
    if ((M2C_FIELD(temp_s2, s16 *, 0x4E) != 0) && (func_8002EFD0((s32) arg0) != 0)) {
        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x4C) = 0;
    }
    if (D_8007CC78 > 0) {
        D_8007CC78 -= 1;
        D_8007CA20 = 0x11A;
    } else if (D_8007CC78 == 0) {
        D_8007CC78 -= 1;
        D_8007CA20 = 0;
    }
    temp_v0_2 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0_2) {                            /* switch 1 */
    case 1:                                         /* switch 1 */
        M2C_FIELD(arg0, s16 *, 0x70) = 3;
        D_8007CB7C = 1;
        D_8007CC78 = 0x96;
        return;
    case 2:                                         /* switch 1 */
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        func_8005B994((s32) arg0);
        return;
    case 3:                                         /* switch 1 */
        D_8007CB7C = 1;
        if (D_8007CA50 & 0xC) {
            if (D_8007CA50 & 8) {
                M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x1C) - 1);
                if (M2C_FIELD(temp_s0, s32 *, 0x1C) < 0) {
                    M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x34) - 1);
                    if (M2C_FIELD(temp_s0, s32 *, 0x1C) < 0) {
                        M2C_FIELD(temp_s0, s32 *, 0x1C) = 0;
                    }
                }
            }
            if (D_8007CA50 & 4) {
                M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x1C) + 1);
                if (M2C_FIELD(temp_s0, s32 *, 0x1C) >= M2C_FIELD(temp_s0, s32 *, 0x34)) {
                    M2C_FIELD(temp_s0, s32 *, 0x1C) = 0;
                }
            }
            temp_s2_2 = M2C_FIELD(temp_s0, s32 *, 0x1C);
            func_8005B994((s32) arg0);
            func_8005BA10((s32) arg0);
            M2C_FIELD(temp_s0, s32 *, 0x1C) = temp_s2_2;
            M2C_FIELD(temp_s0, s32 *, 0x38) = 0xA;
            M2C_FIELD(arg0, s16 *, 0x70) = 5;
        }
        if (D_8007CA50 & 0x40) {
            M2C_FIELD(temp_s0, s32 *, 0x38) = 0x64;
            temp_v0_3 = *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x1C) * 4));
            switch (temp_v0_3) {                    /* switch 2 */
            case 21:                                /* switch 2 */
                func_80030F18(2);
                break;
            case 22:                                /* switch 2 */
                func_80030F18(4);
                break;
            case 24:                                /* switch 2 */
                func_80030F18(8);
                break;
            case 23:                                /* switch 2 */
                func_80030F18(6);
                break;
            case 25:                                /* switch 2 */
                func_80030F18(0xA);
                break;
            }
            temp_s2_3 = M2C_FIELD(temp_s0, s32 *, 0x1C);
            func_8005B994((s32) arg0);
            func_8005BA10((s32) arg0);
            M2C_FIELD(temp_s0, s32 *, 0x1C) = temp_s2_3;
            M2C_FIELD(temp_s0, s32 *, 0x38) = 0xA;
            M2C_FIELD(arg0, s16 *, 0x70) = 5;
            return;
        }
    default:                                        /* switch 1 */
        return;
    case 4:                                         /* switch 1 */
        M2C_FIELD(arg0, s16 *, 0x70) = 3;
        return;
    case 5:                                         /* switch 1 */
        D_8007CB7C = 1;
        M2C_FIELD(temp_s0, s32 *, 0x38) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x38) - 1);
        if (M2C_FIELD(temp_s0, s32 *, 0x38) < 0) {
            M2C_FIELD(arg0, s16 *, 0x70) = 3;
        }
        break;
    }
}
