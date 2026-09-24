#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8001EDE4(void *arg0) {
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_v0;
    u16 temp_a0;

    temp_a0 = M2C_FIELD(arg0, u16 *, 0x42);
    temp_v0 = temp_a0 & 0x38;
    switch (temp_v0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        break;
    case 16:                                        /* switch 1 */
        if ((M2C_FIELD(arg0, s32 *, 0x30) * 2) < M2C_FIELD(arg0, s32 *, 0x14)) {
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x10) >> 1);
            M2C_FIELD(arg0, s32 *, 0x18) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x18) >> 1);
            M2C_FIELD(arg0, s32 *, 0x14) = (s32) ((s32) -M2C_FIELD(arg0, s32 *, 0x14) >> 1);
        } else {
            M2C_FIELD(arg0, u16 *, 0x42) = (u16) (temp_a0 & 0xFFEF);
        case 32:                                    /* switch 1 */
            M2C_FIELD(arg0, s32 *, 0x10) = 0;
            M2C_FIELD(arg0, s32 *, 0x14) = 0;
            M2C_FIELD(arg0, s32 *, 0x18) = 0;
            M2C_FIELD(arg0, s32 *, 0x2C) = 0;
            M2C_FIELD(arg0, s32 *, 0x30) = 0;
            M2C_FIELD(arg0, s32 *, 0x34) = 0;
            M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (M2C_FIELD(arg0, s32 *, 0x3C) * 2);
            M2C_FIELD(arg0, s16 *, 0x40) = (s16) ((s16) M2C_FIELD(arg0, s16 *, 0x40) >> 1);
            M2C_FIELD(arg0, u16 *, 0x42) = (u16) (M2C_FIELD(arg0, u16 *, 0x42) & 0xFE5F);
        }
        break;
    default:                                        /* switch 1 */
    case 8:                                         /* switch 1 */
        M2C_FIELD(arg0, s16 *, 0x40) = -1;
        break;
    }
    if (!(M2C_FIELD(arg0, u16 *, 0x42) & 0x400)) {
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x42) & 0x1C0;
        switch (temp_v0_2) {                        /* switch 2; irregular */
        case 0x80:                                  /* switch 2 */
            M2C_FIELD(arg0, s32 *, 0x2C) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x18) >> 3);
            M2C_FIELD(arg0, s32 *, 0x34) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x10) >> 3);
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) + M2C_FIELD(arg0, s32 *, 0x2C));
            M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) - M2C_FIELD(arg0, s32 *, 0x34));
            temp_v1 = M2C_FIELD(arg0, s32 *, 0x10);
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (temp_v1 - (temp_v1 >> 8));
            temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x18);
            var_v0 = temp_v1_2 - (temp_v1_2 >> 8);
block_22:
            M2C_FIELD(arg0, s32 *, 0x18) = var_v0;
            break;
        case 0x40:                                  /* switch 2 */
            temp_v1_3 = M2C_FIELD(arg0, s32 *, 0x10);
            temp_a1 = M2C_FIELD(arg0, s32 *, 0x18);
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (temp_v1_3 + M2C_FIELD(arg0, s32 *, 0x2C));
            M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) + M2C_FIELD(arg0, s32 *, 0x34));
            if ((M2C_FIELD(arg0, s32 *, 0x10) ^ temp_v1_3) < 0) {
                M2C_FIELD(arg0, s32 *, 0x10) = 0;
                M2C_FIELD(arg0, s32 *, 0x2C) = 0;
            }
            if ((M2C_FIELD(arg0, s32 *, 0x18) ^ temp_a1) < 0) {
                M2C_FIELD(arg0, s32 *, 0x18) = 0;
                M2C_FIELD(arg0, s32 *, 0x34) = 0;
            }
            if ((M2C_FIELD(arg0, s32 *, 0x2C) | M2C_FIELD(arg0, s32 *, 0x34)) == 0) {
                M2C_FIELD(arg0, u16 *, 0x42) = (u16) (M2C_FIELD(arg0, u16 *, 0x42) & 0xFFBF);
            }
            break;
        case 0x100:                                 /* switch 2 */
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) + ((s32) (M2C_FIELD(arg0, s32 *, 0x2C) - M2C_FIELD(arg0, s32 *, 4)) >> 3));
            var_v0 = M2C_FIELD(arg0, s32 *, 0x18) + ((s32) (M2C_FIELD(arg0, s32 *, 0x34) - M2C_FIELD(arg0, s32 *, 0xC)) >> 3);
            goto block_22;
        default:                                    /* switch 2 */
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) + M2C_FIELD(arg0, s32 *, 0x2C));
            var_v0 = M2C_FIELD(arg0, s32 *, 0x18) + M2C_FIELD(arg0, s32 *, 0x34);
            goto block_22;
        }
        M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x10));
        M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) + M2C_FIELD(arg0, s32 *, 0x18));
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) + M2C_FIELD(arg0, s32 *, 0x30));
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x14));
    }
    if (M2C_FIELD(arg0, u16 *, 0x42) & 0x200) {
        temp_v1_4 = M2C_FIELD(arg0, s32 *, 0x10);
        M2C_FIELD(arg0, s32 *, 0x10) = (s32) (temp_v1_4 - (temp_v1_4 >> 4));
        temp_v1_5 = M2C_FIELD(arg0, s32 *, 0x14);
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (temp_v1_5 - (temp_v1_5 >> 4));
        temp_v1_6 = M2C_FIELD(arg0, s32 *, 0x18);
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) (temp_v1_6 - (temp_v1_6 >> 4));
    }
    if (M2C_FIELD(arg0, u16 *, 0x42) & 4) {
        temp_s2 = func_80014AEC(M2C_FIELD(arg0, s32 *, 0x10));
        temp_s2_2 = temp_s2 + func_80014AEC(M2C_FIELD(arg0, s32 *, 0x14));
        if ((func_80014AEC(M2C_FIELD(arg0, s32 *, 0x18)) + temp_s2_2) < 0x28F) {
            M2C_FIELD(arg0, s16 *, 0x40) = -1;
        }
    }
    if (M2C_FIELD(arg0, u16 *, 0x42) & 0x1000) {
        M2C_FIELD(arg0, s16 *, 0x44) = (s16) ((M2C_FIELD(arg0, s16 *, 0x44) + 0x40) & 0xFFF);
    }
    if ((M2C_FIELD(arg0, u16 *, 0x42) & 2) && ((M2C_FIELD(arg0, u8 *, 0x1E) + (M2C_FIELD(arg0, u8 *, 0x1C) + M2C_FIELD(arg0, u8 *, 0x1D))) < 0xF)) {
        M2C_FIELD(arg0, s16 *, 0x40) = -1;
    }
    temp_v0_3 = M2C_FIELD(arg0, s32 *, 0x3C);
    if (temp_v0_3 != 0) {
        temp_a0_2 = M2C_FIELD(arg0, s32 *, 0x24) + temp_v0_3;
        if (temp_a0_2 < 0x10) {
            M2C_FIELD(arg0, s32 *, 0x24) = 1;
            M2C_FIELD(arg0, s32 *, 0x3C) = 0;
            M2C_FIELD(arg0, s16 *, 0x40) = -1;
            return;
        }
        M2C_FIELD(arg0, s32 *, 0x24) = temp_a0_2;
    }
}
