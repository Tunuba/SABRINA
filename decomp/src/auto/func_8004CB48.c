#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C8560;
extern u8 D_800C98C4[];
extern u8 D_800D588C[];
extern u8 D_800D5890[];
extern u8 D_800D5894[];
extern s8 nivel_actual;
extern s32 D_8007CC1C;


void func_8004CB48(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    void *temp_s0;

    *(D_800C98C4 + (D_8007CC1C * 4)) = arg0;
    temp_s0 = arg0 + 0x74;
    D_8007CC1C += 1;
    if (M2C_FIELD(arg0, s32 *, 0x74) < 0) {
        M2C_FIELD(arg0, s32 *, 0x74) = 0;
    }
    M2C_FIELD(temp_s0, s32 *, 0x1C) = 0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 4);
    switch (temp_v0) {                              /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        func_800249CC((s32) arg0, 0xE);
        M2C_FIELD(temp_s0, s32 *, 4) = 1;
        M2C_FIELD(arg0, s16 *, 0x70) = 1;
        M2C_FIELD(temp_s0, s32 *, 8) = 0x50000;
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) M2C_FIELD(temp_s0, s32 *, 8) >> 8);
        temp_v0_2 = M2C_FIELD(temp_s0, s32 *, 8);
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) (temp_v0_2 * temp_v0_2) >> 8);
        break;
    case 2:                                         /* switch 1 */
        func_800249CC((s32) arg0, 0xF);
        M2C_FIELD(temp_s0, s32 *, 4) = 4;
        M2C_FIELD(temp_s0, s32 *, 8) = 0x50000;
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) M2C_FIELD(temp_s0, s32 *, 8) >> 8);
        temp_v0_3 = M2C_FIELD(temp_s0, s32 *, 8);
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) (temp_v0_3 * temp_v0_3) >> 8);
        if (D_800C8560 >= 2) {
            M2C_FIELD(arg0, s16 *, 0x70) = 1;
        }
        break;
    case 3:                                         /* switch 1 */
        func_800249CC((s32) arg0, 0x10);
        M2C_FIELD(temp_s0, s32 *, 4) = 7;
        M2C_FIELD(temp_s0, s32 *, 8) = 0x50000;
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) M2C_FIELD(temp_s0, s32 *, 8) >> 8);
        temp_v0_4 = M2C_FIELD(temp_s0, s32 *, 8);
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) (temp_v0_4 * temp_v0_4) >> 8);
        if (D_800C8560 >= 3) {
            M2C_FIELD(arg0, s16 *, 0x70) = 1;
        }
        break;
    case 4:                                         /* switch 1 */
        func_800249CC((s32) arg0, 0x11);
        M2C_FIELD(temp_s0, s32 *, 4) = 0xA;
        M2C_FIELD(temp_s0, s32 *, 8) = 0x50000;
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) M2C_FIELD(temp_s0, s32 *, 8) >> 8);
        temp_v0_5 = M2C_FIELD(temp_s0, s32 *, 8);
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) (temp_v0_5 * temp_v0_5) >> 8);
        if (D_800C8560 >= 4) {
            M2C_FIELD(arg0, s16 *, 0x70) = 1;
        }
        break;
    case 0:                                         /* switch 1 */
    case 14:                                        /* switch 1 */
        M2C_FIELD(temp_s0, s32 *, 8) = 0x20000;
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) M2C_FIELD(temp_s0, s32 *, 8) >> 8);
        temp_v0_6 = M2C_FIELD(temp_s0, s32 *, 8);
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) ((s32) (temp_v0_6 * temp_v0_6) >> 8);
        func_800249CC((s32) arg0, -1);
        M2C_FIELD(arg0, s16 *, 0x70) = 2;
        switch (nivel_actual) {                     /* switch 2 */
        case 0:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 0xD;
            break;
        case 4:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 5;
            break;
        case 5:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 6;
            break;
        case 6:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 0xD;
            if (D_800C8560 < 3) {
                D_800C8560 = 3;
            }
            M2C_FIELD(temp_s0, s32 *, 0x1C) = 1;
            break;
        case 1:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 2;
            break;
        case 2:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 3;
            break;
        case 3:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 0xD;
            if (D_800C8560 < 2) {
                D_800C8560 = 2;
            }
            M2C_FIELD(temp_s0, s32 *, 0x1C) = 1;
            break;
        case 7:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 8;
            break;
        case 8:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 9;
            break;
        case 9:                                     /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 0xD;
            if (D_800C8560 < 4) {
                D_800C8560 = 4;
            }
            M2C_FIELD(temp_s0, s32 *, 0x1C) = 1;
            break;
        case 10:                                    /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 0xB;
            break;
        case 11:                                    /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 0xC;
            break;
        case 12:                                    /* switch 2 */
            M2C_FIELD(temp_s0, s32 *, 4) = 0xD;
            if (D_800C8560 < 5) {
                D_800C8560 = 5;
            }
            M2C_FIELD(temp_s0, s32 *, 0x1C) = 1;
            break;
        }
        break;
    default:                                        /* switch 1 */
        M2C_FIELD(temp_s0, s32 *, 4) = 0;
        break;
    }
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) -M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) -M2C_FIELD(arg0, s32 *, 0x2C);
    func_8001C45C((s32) (arg0 + 0x38));
    M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) M2C_FIELD(arg0, s32 *, 0x38);
    M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) M2C_FIELD(arg0, s32 *, 0x3C);
    M2C_FIELD(temp_s0, s32 *, 0x18) = (s32) M2C_FIELD(arg0, s32 *, 0x40);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) * 2);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) * 2);
    M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) ((s32) M2C_FIELD(temp_s0, s32 *, 0x10) >> 4);
    M2C_FIELD(temp_s0, s32 *, 0x18) = (s32) ((s32) M2C_FIELD(temp_s0, s32 *, 0x18) >> 4);
    M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (((s32) (M2C_FIELD(temp_s0, s32 *, 0x10) * 0x3CC) >> 8) << 8);
    M2C_FIELD(temp_s0, s32 *, 0x18) = (s32) (((s32) (M2C_FIELD(temp_s0, s32 *, 0x18) * 0x3CC) >> 8) << 8);
    M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    temp_v0_7 = M2C_FIELD(arg0, s32 *, 0x74);
    if (temp_v0_7 != 0) {
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) (D_800D588C + (temp_v0_7 * 0x18));
        M2C_FIELD(temp_s0, s32 *, 0x20) = (s32) *(D_800D588C + (M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s16 *, 0xE) * 0x18));
        M2C_FIELD(temp_s0, s32 *, 0x24) = (s32) *(D_800D5890 + (M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s16 *, 0xE) * 0x18));
        M2C_FIELD(temp_s0, s32 *, 0x28) = (s32) *(D_800D5894 + (M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s16 *, 0xE) * 0x18));
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
}
