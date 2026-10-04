#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C855E;
extern u8 D_800C8567[];
extern s8 D_800C8582;
extern s8 D_800C8583;
extern s8 D_800C8584;
extern s8 D_800C8585;
extern s32 D_800C98B8;
extern s8 D_8007C890;
extern s8 D_8007C891;
extern s8 D_8007C892;
extern s8 nivel_actual;


void func_80054C5C(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 var_v0_2;
    s32 temp_a0;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    u8 var_v0;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    if ((s8) D_800C8567[M2C_FIELD(temp_s1, s32 *, 4)] != 0) {
        var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
        goto block_69;
    }
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x64);
    temp_v0 = M2C_FIELD(arg0, s16 *, 0x32);
    if (temp_v0 >= 0x1000) {
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (temp_v0 - 0x1000);
    }
    temp_v0_2 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0_2) {                            /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if (M2C_FIELD(temp_s1, s32 *, 8) != 0) {
            switch (nivel_actual) {                 /* switch 2; irregular */
            case 3:                                 /* switch 2 */
                if (D_800C8582 != 0) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 1;
                    return;
                }
                break;
            case 6:                                 /* switch 2 */
                if (D_800C8583 != 0) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 1;
                    return;
                }
                break;
            case 9:                                 /* switch 2 */
                if (D_800C8584 != 0) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 1;
                    return;
                }
                break;
            case 12:                                /* switch 2 */
                if (D_800C8585 != 0) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 1;
                    return;
                }
                break;
            }
        } else {
            return;
        }
        break;
    case 1:                                         /* switch 1 */
        if (M2C_FIELD(temp_s1, s32 *, 8) != 0) {
            switch (nivel_actual) {                 /* switch 3; irregular */
            case 3:                                 /* switch 3 */
                if (D_800C8582 == 2) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 4;
                    return;
                }
                goto block_34;
            case 6:                                 /* switch 3 */
                if (D_800C8583 == 2) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 4;
                    return;
                }
                goto block_34;
            case 9:                                 /* switch 3 */
                if (D_800C8584 == 2) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 4;
                    return;
                }
                goto block_34;
            case 12:                                /* switch 3 */
                if (D_800C8585 == 2) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 4;
                    return;
                }
                goto block_34;
            }
        } else {
block_34:
            temp_a0 = M2C_FIELD(arg0, s32 *, 0x54);
            if (temp_a0 < 0x1000) {
                M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_a0 + ((s32) (0x1000 - temp_a0) >> 2));
                if (M2C_FIELD(arg0, s32 *, 0x54) >= 0x1000) {
                    M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
                }
                temp_v0_3 = M2C_FIELD(arg0, s32 *, 0x54);
                M2C_FIELD(arg0, s32 *, 0x5C) = temp_v0_3;
                M2C_FIELD(arg0, s32 *, 0x58) = temp_v0_3;
            }
            if (p_sabrina != NULL) {
                temp_v0_4 = func_8002225C((s32) arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z);
                if (temp_v0_4 >= 0x140001) {
                    var_v0_2 = 1;
                    goto block_43;
                }
                if (temp_v0_4 < 0x20000) {
                    var_v0_2 = 2;
block_43:
                    M2C_FIELD(arg0, s16 *, 0x70) = var_v0_2;
                }
            }
            temp_s2 = func_80021CE4(0x1000);
            temp_s3 = func_80021CE4(0x1000);
            temp_s1_2 = (s32) (rsin(temp_s2) * 0xC000) >> 0xC;
            temp_v1 = (s32) (rcos(temp_s2) * 0xC000) >> 0xC;
            CrearParticula(0xE, (s32) arg0, (s32) (s16) temp_s3, 0, /* extra? */ (temp_s1_2 - 0x5999), /* extra? */ temp_v1, /* extra? */ 0, /* extra? */ ((s32) -temp_s1_2 >> 5), /* extra? */ ((s32) -temp_v1 >> 5), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0);
            return;
        }
        break;
    case 2:                                         /* switch 1 */
        switch (nivel_actual) {                     /* switch 4 */
        case 1:                                     /* switch 4 */
            D_8007C890 = 1;
            break;
        case 2:                                     /* switch 4 */
            D_8007C891 = 1;
            break;
        case 3:                                     /* switch 4 */
            D_8007C892 = 1;
            break;
        case 4:                                     /* switch 4 */
            D_8007C890 = 1;
            break;
        case 5:                                     /* switch 4 */
            D_8007C891 = 1;
            break;
        case 6:                                     /* switch 4 */
            D_8007C892 = 1;
            break;
        case 7:                                     /* switch 4 */
            D_8007C890 = 1;
            break;
        case 8:                                     /* switch 4 */
            D_8007C891 = 1;
            break;
        case 9:                                     /* switch 4 */
            D_8007C892 = 1;
            break;
        case 10:                                    /* switch 4 */
            D_8007C890 = 1;
            break;
        case 11:                                    /* switch 4 */
            D_8007C891 = 1;
            break;
        case 12:                                    /* switch 4 */
            D_8007C892 = 1;
            break;
        }
        TocarSonido(0x20, 0, 0x2A, 0x7F);
        TocarSonido(0x12, 0, 0x2A, 0x7F);
        D_800C855E += 1;
        D_800C8567[M2C_FIELD(temp_s1, s32 *, 4)] = 1;
        D_800C98B8 = 1;
        M2C_FIELD(arg0, s16 *, 0x70) = 4;
        if (M2C_FIELD(temp_s1, s32 *, 8) != 0) {
            switch (nivel_actual) {                 /* switch 5; irregular */
            case 3:                                 /* switch 5 */
                D_800C8582 = 2;
                return;
            case 6:                                 /* switch 5 */
                D_800C8583 = 2;
                return;
            case 9:                                 /* switch 5 */
                D_800C8584 = 2;
                return;
            case 12:                                /* switch 5 */
                D_800C8585 = 2;
                return;
            }
        }
        break;
    case 4:                                         /* switch 1 */
        var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
block_69:
        M2C_FIELD(arg0, u8 *, 0x20) = var_v0;
        break;
    }
}
