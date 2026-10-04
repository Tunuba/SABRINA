#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800C8558;
extern s16 D_800C855A;
extern s16 D_800C855C;
extern s8 D_800C855F;
extern s8 D_800C8562;
extern s8 D_800C8563;
extern s8 D_800C8564;
extern s8 D_800C8565;
extern s32 D_800C98B0;
extern s32 D_800C98B4;
extern s16 gemas;
extern u16 D_8007C8C4;
extern u16 D_8007C8C6;
extern s8 D_8007CA01;
extern s32 D_8007CA30;
extern s32 D_8007CA50;


void func_80056CE8(void *arg0) {
    ObjExtra *temp_s2_2;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v0_5;
    s32 temp_v0_4;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_a0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u16 *temp_s3;
    u16 temp_v0_2;
    void *temp_s1;
    void *temp_s2;

    temp_s3 = M2C_FIELD(arg0, u16 **, 0x64);
    temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s1 = arg0 + 0x74;
    if ((D_800C98B4 == 0) && (M2C_FIELD(temp_s1, s32 *, 0x38) == 0)) {
        func_800487B0((s32) arg0, (s32) p_sabrina, 0x96);
        temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
        switch (temp_v0) {                          /* switch 1 */
        case 0:                                     /* switch 1 */
            temp_v0_2 = *temp_s3;
            if (M2C_FIELD(temp_s2, u8 *, 0x51) != temp_v0_2) {
                M2C_FIELD(temp_s2, u8 *, 0x51) = (u8) temp_v0_2;
                M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
            }
            if ((D_8007CA30 & 1) && (func_8002225C((s32) arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z) < 0x28000) && (M2C_FIELD(temp_s1, s32 *, 0x34) != 0x64) && ((temp_v0_3 = p_sabrina->estado, (temp_v0_3 == 0)) || (temp_v0_3 == 1)) && (temp_s2_2 = &p_sabrina->extra, (p_sabrina->extra._1D == 0))) {
                temp_v0_4 = func_8003E060();
                if ((temp_v0_4 == 0x52) || (temp_v0_4 == 0x51) || (temp_v0_4 == 0x50) || (var_v0 = 0, (temp_v0_4 == 0x4F))) {
                    var_v0 = 1;
                }
                if (var_v0 == 0) {
                    *temp_s2_2 = arg0;
                    M2C_FIELD(temp_s1, s32 *, 0x2C) = func_80056A08();
                    if (M2C_FIELD(temp_s1, s32 *, 0x2C) != 0) {
                        M2C_FIELD(arg0, s16 *, 0x70) = 1;
                        M2C_FIELD(temp_s1, s32 *, 0x34) = 0x32;
                        func_8003DE68(1);
                        func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
                        p_sabrina->estado = 1;
                        return;
                    }
                    var_a0 = 0;
                    switch (D_8007CA01) {           /* switch 2 */
                    case 1:                         /* switch 2 */
                    case 2:                         /* switch 2 */
                    case 3:                         /* switch 2 */
                        if (D_800C8563 == 2) {
                        default:                    /* switch 2 */
block_30:
                            var_a0 = 1;
                        }
                        break;
                    case 4:                         /* switch 2 */
                    case 5:                         /* switch 2 */
                    case 6:                         /* switch 2 */
                        if (D_800C8562 == 1) {
                            goto block_30;
                        }
                        break;
                    case 7:                         /* switch 2 */
                    case 8:                         /* switch 2 */
                    case 9:                         /* switch 2 */
                        if (D_800C8565 == 4) {
                            goto block_30;
                        }
                        break;
                    case 10:                        /* switch 2 */
                    case 11:                        /* switch 2 */
                    case 12:                        /* switch 2 */
                        if (D_800C8564 == 3) {
                            goto block_30;
                        }
                        break;
                    }
                    if (var_a0 == 0) {
                        M2C_FIELD(temp_s1, s32 *, 0x34) = 0x32;
                        M2C_FIELD(arg0, s16 *, 0x70) = 4;
                        func_8003DE68(2);
                        func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
                        p_sabrina->estado = 1;
                        return;
                    }
                }
            }
            break;
        case 6:                                     /* switch 1 */
            if ((func_8002225C((s32) arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z) < 0x28000) && ((temp_v0_5 = p_sabrina->estado, (temp_v0_5 == 0)) || (temp_v0_5 == 1)) && (p_sabrina->extra._1D == 0) && (p_sabrina->estado = 1, M2C_FIELD(p_sabrina, void **, 0x74) = arg0, (D_800C98B0 != 0))) {
                if (D_800C98B0 == 1) {
                    func_8003DE68(0);
                    func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
                    D_800C98B0 = 2;
                    func_80056C18((s32) arg0, 1);
                }
                if (D_800C98B0 == 2) {
                    temp_v0_6 = func_8003E060();
                    if ((temp_v0_6 != 0x5A) || (temp_v0_6 == -1)) {
                        D_800C98B0 = 0;
                        func_8003DDA0(3, 1);
                        func_8003DD44((D_8007C8C4 * 0xF) & 0xFF);
                        M2C_FIELD(arg0, s16 *, 0x70) = 0;
                        p_sabrina->estado = 0;
                    }
                    func_80056C18((s32) arg0, 0);
                    return;
                }
            }
            break;
        case 1:                                     /* switch 1 */
            var_v0_2 = func_8003E060();
            if ((var_v0_2 != 0x5D) && (var_v0_2 != 0x5C) && (var_v0_2 != 0x5B)) {
                var_v0_2 = -1;
            }
            if ((var_v0_2 == -1) || (D_8007CA50 & 0x40)) {
                M2C_FIELD(arg0, s16 *, 0x70) = 3;
                M2C_FIELD(temp_s1, s32 *, 0x34) = 0x64;
                func_8003DDA0(3, 1);
                func_8003DD44((D_8007C8C4 * 0xF) & 0xFF);
                p_sabrina->estado = 0;
                return;
            }
            break;
        case 4:                                     /* switch 1 */
            var_v0_3 = func_8003E060();
            if ((var_v0_3 != 0x60) && (var_v0_3 != 0x5F) && (var_v0_3 != 0x5E)) {
                var_v0_3 = -1;
            }
            if ((var_v0_3 == -1) || (D_8007CA50 & 0x40)) {
                M2C_FIELD(arg0, s16 *, 0x70) = 0;
                M2C_FIELD(temp_s1, s32 *, 0x34) = 0x64;
                func_8003DDA0(3, 1);
                func_8003DD44((D_8007C8C4 * 0xF) & 0xFF);
                p_sabrina->estado = 0;
                return;
            }
            break;
        case 2:                                     /* switch 1 */
            M2C_FIELD(arg0, s16 *, 0x70) = 0;
            M2C_FIELD(temp_s1, s32 *, 0x34) = 0x1F4;
            p_sabrina->estado = 0;
            return;
        case 3:                                     /* switch 1 */
            D_800C855F += 1;
            temp_v0_7 = M2C_FIELD(temp_s1, s32 *, 0x2C);
            if (temp_v0_7 != 3) {
                if (temp_v0_7 != 4) {
                    if (temp_v0_7 != 1) {
                        if (temp_v0_7 == 2) {
                            D_800C8563 = 2;
                            gemas -= 0x64;
                        }
                    } else {
                        D_800C8562 = 1;
                        D_800C8558 -= 0x64;
                    }
                } else {
                    D_800C8565 = 4;
                    D_800C855A -= 0x64;
                }
            } else {
                D_800C8564 = 3;
                D_800C855C -= 0x64;
            }
            M2C_FIELD(arg0, s16 *, 0x70) = 5;
            M2C_FIELD(temp_s1, s32 *, 0x34) = 0x1F4;
            p_sabrina->estado = 0;
            return;
        case 5:                                     /* switch 1 */
            M2C_FIELD(temp_s1, s32 *, 0x34) = (s32) (M2C_FIELD(temp_s1, s32 *, 0x34) - 1);
            if (M2C_FIELD(temp_s1, s32 *, 0x34) < 0) {
                M2C_FIELD(arg0, s16 *, 0x70) = 0;
            }
            break;
        }
    } else {
    default:                                        /* switch 1 */
    }
}
