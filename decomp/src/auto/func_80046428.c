#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;
extern s32 D_8007CBA8;


void func_80046428(void *arg0) {
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    M2C_UNK sp54;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    M2C_UNK sp6C;
    s16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u8 temp_v1;
    u8 temp_v1_2;
    void *temp_s0;
    void *temp_s2;
    void *temp_s3;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s3 = M2C_FIELD(arg0, void **, 0x64);
    temp_s0 = arg0 + 0x74;
    switch (temp_v0) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        M2C_FIELD(temp_s0, s16 *, 0x2A) = 5;
        M2C_FIELD(arg0, s16 *, 0x70) = 1;
        return;
    case 1:                                         /* switch 1 */
        if (M2C_FIELD(temp_s2, u8 *, 0x51) != M2C_FIELD(temp_s3, u16 *, 0)) {
            M2C_FIELD(temp_s2, s16 *, 0x4C) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
            M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 0);
            M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
        }
        func_80048908((s32) arg0, (s32) (temp_s0 + 0x2A), (s32) (temp_s0 + 0x2C), (s32) M2C_FIELD(temp_s0, s8 *, 0x24));
        return;
    case 2:                                         /* switch 1 */
        func_800492B4((s32) arg0, (s32) temp_s0, (s32) temp_s3);
        return;
    case 3:                                         /* switch 1 */
    case 4:                                         /* switch 1 */
        if (func_800487B0((s32) arg0, (s32) p_sabrina, 0x64) < 0x200) {
            if (M2C_FIELD(arg0, s16 *, 0x70) != 4) {
                temp_v0_2 = M2C_FIELD(temp_s3, u16 *, 8);
                if (M2C_FIELD(temp_s2, u8 *, 0x51) != temp_v0_2) {
                    M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) temp_v0_2;
                    M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                    M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                    M2C_FIELD(arg0, s16 *, 0x70) = 4;
                }
            }
            func_80048804((s32) arg0, (s32) M2C_FIELD(temp_s0, s8 *, 0x24), (s32) temp_s2, (s32) (s8) M2C_FIELD(temp_s3, u16 *, 0));
            return;
        }
        return;
    case 7:                                         /* switch 1 */
        func_800487B0((s32) arg0, (s32) p_sabrina, 0x64);
        temp_v0_3 = M2C_FIELD(temp_s3, u16 *, 0xE);
        if (M2C_FIELD(temp_s2, u8 *, 0x51) != temp_v0_3) {
            M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) temp_v0_3;
            M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
            M2C_FIELD(temp_s0, s16 *, 0x44) = 0;
            return;
        }
        if (D_8007CBA8 == 0) {
            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
            temp_v1 = M2C_FIELD(temp_s2, u8 *, 0x50);
            if (((temp_v1 == M2C_FIELD(temp_s0, s8 *, 0x28)) || (temp_v1 == M2C_FIELD(temp_s0, s8 *, 0x27))) && (M2C_FIELD(temp_s0, s16 *, 0x44) == 0)) {
                M2C_FIELD(temp_s0, s16 *, 0x44) = 1;
                sp48 = M2C_FIELD(temp_s0, s32 *, 0xC);
                sp4C = M2C_FIELD(temp_s0, s32 *, 0x10);
                sp50 = M2C_FIELD(temp_s0, s32 *, 0x14);
                switch (nivel_actual) {             /* switch 2 */
                case 1:                             /* switch 2 */
                case 2:                             /* switch 2 */
                case 3:                             /* switch 2 */
                    func_8003C1E8((s32) arg0, (s32) &sp48, (s32) &sp54, 0x1E, /* extra? */ 0x32, /* extra? */ 5, /* extra? */ 0x200, /* extra? */ -0x8C0);
                    TocarSonido(0x38, 0, 0x2A, 0x7F);
                    break;
                case 4:                             /* switch 2 */
                case 5:                             /* switch 2 */
                case 6:                             /* switch 2 */
                    func_8003C1E8((s32) arg0, (s32) &sp48, (s32) &sp54, 0x20, /* extra? */ 0x32, /* extra? */ 5, /* extra? */ 0x200, /* extra? */ -0x8C0);
                    TocarSonido(0x36, 0, 0x2A, 0x7F);
                    break;
                case 7:                             /* switch 2 */
                case 8:                             /* switch 2 */
                case 9:                             /* switch 2 */
                    func_80048DC0((s32) arg0, (s32) &sp48, (s32) &sp54, -1, /* extra? */ 0x1000);
                    TocarSonido(0x34, 0, 0x2A, 0x7F);
                    break;
                case 10:                            /* switch 2 */
                case 11:                            /* switch 2 */
                case 12:                            /* switch 2 */
                    func_8003C678((s32) arg0, (s32) &sp48, (s32) &sp54, 0x27, /* extra? */ 0x32, /* extra? */ 5, /* extra? */ 0x200, /* extra? */ -0x8C0);
                    TocarSonido(0x37, 0, 0x2A, 0x7F);
                    break;
                case 13:                            /* switch 2 */
                case 14:                            /* switch 2 */
                    TocarSonido(0x2C, 0, 0x2A, 0x7F);
                    break;
                }
            }
            if (func_8002EFD0((s32) arg0) != 0) {
                M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 0);
                M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                M2C_FIELD(arg0, s16 *, 0x70) = (s16) M2C_FIELD(temp_s0, s8 *, 0x29);
                M2C_FIELD(temp_s0, s16 *, 0x44) = 0;
                return;
            }
        }
        break;
    case 8:                                         /* switch 1 */
        func_800487B0((s32) arg0, (s32) p_sabrina, 0x64);
        if (func_8002EFD0((s32) arg0) != 0) {
            if (M2C_FIELD(temp_s0, s8 *, 0x24) & 4) {
                M2C_FIELD(arg0, s16 *, 0x70) = 0xB;
                return;
            }
            M2C_FIELD(arg0, s16 *, 0x70) = 4;
            return;
        }
        break;
    case 10:                                        /* switch 1 */
        func_80048228((s32) arg0);
        return;
    case 11:                                        /* switch 1 */
        func_800489C4((s32) arg0);
        func_800487B0((s32) arg0, (s32) p_sabrina, 0x64);
        sp3C = M2C_FIELD(arg0, s32 *, 0x24) - p_sabrina->x;
        sp40 = 0;
        sp44 = M2C_FIELD(arg0, s32 *, 0x2C) - p_sabrina->z;
        if (((s32) M2C_FIELD(temp_s0, s32 *, 8) >> 8) >= func_8001C180((s32) &sp3C)) {
            temp_v0_4 = M2C_FIELD(temp_s3, u16 *, 0xE);
            if (M2C_FIELD(temp_s2, u8 *, 0x51) != temp_v0_4) {
                M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) temp_v0_4;
                M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                M2C_FIELD(temp_s0, s16 *, 0x44) = 0;
                return;
            }
            if (D_8007CBA8 == 0) {
                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                temp_v1_2 = M2C_FIELD(temp_s2, u8 *, 0x50);
                if (((temp_v1_2 == M2C_FIELD(temp_s0, s8 *, 0x28)) || (temp_v1_2 == M2C_FIELD(temp_s0, s8 *, 0x27))) && (M2C_FIELD(temp_s0, s16 *, 0x44) == 0)) {
                    M2C_FIELD(temp_s0, s16 *, 0x44) = 1;
                    sp60 = M2C_FIELD(temp_s0, s32 *, 0xC);
                    sp64 = M2C_FIELD(temp_s0, s32 *, 0x10);
                    sp68 = M2C_FIELD(temp_s0, s32 *, 0x14);
                    switch (nivel_actual) {         /* switch 3 */
                    case 1:                         /* switch 3 */
                    case 2:                         /* switch 3 */
                    case 3:                         /* switch 3 */
                        func_8003C1E8((s32) arg0, (s32) &sp60, (s32) &sp6C, 0x1E, /* extra? */ 0x32, /* extra? */ 5, /* extra? */ 0x200, /* extra? */ -0x8C0);
                        TocarSonido(0x38, 0, 0x2A, 0x7F);
                        break;
                    case 4:                         /* switch 3 */
                    case 5:                         /* switch 3 */
                    case 6:                         /* switch 3 */
                        func_8003C1E8((s32) arg0, (s32) &sp60, (s32) &sp6C, 0x20, /* extra? */ 0x32, /* extra? */ 5, /* extra? */ 0x200, /* extra? */ -0x8C0);
                        TocarSonido(0x36, 0, 0x2A, 0x7F);
                        break;
                    case 7:                         /* switch 3 */
                    case 8:                         /* switch 3 */
                    case 9:                         /* switch 3 */
                        func_80048DC0((s32) arg0, (s32) &sp60, (s32) &sp6C, -1, /* extra? */ 0x1000);
                        TocarSonido(0x34, 0, 0x2A, 0x7F);
                        break;
                    case 10:                        /* switch 3 */
                    case 11:                        /* switch 3 */
                    case 12:                        /* switch 3 */
                        func_8003C1E8((s32) arg0, (s32) &sp60, (s32) &sp6C, 0x27, /* extra? */ 0x32, /* extra? */ 5, /* extra? */ 0x200, /* extra? */ -0x8C0);
                        TocarSonido(0x37, 0, 0x2A, 0x7F);
                        break;
                    case 13:                        /* switch 3 */
                    case 14:                        /* switch 3 */
                        TocarSonido(0x2C, 0, 0x2A, 0x7F);
                        break;
                    }
                }
                if (func_8002EFD0((s32) arg0) != 0) {
                    M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 0);
                    M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                    M2C_FIELD(temp_s0, s16 *, 0x44) = 0;
                    return;
                }
            }
        } else if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 0);
            M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s0, s16 *, 0x44) = 0;
            return;
        }
        break;
    case 12:                                        /* switch 1 */
        func_80049A28((s32) arg0, (s32) temp_s0, (s32) temp_s3);
        return;
    case 6:                                         /* switch 1 */
        func_80049BD0((s32) arg0, (s32) temp_s0, (s32) temp_s3);
        return;
    default:                                        /* switch 1 */
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        break;
    }
}
