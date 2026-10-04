#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D5290;
extern s32 D_800D5294;
extern u8 D_800D52C0[];
extern u8 D_800D52CC[];
extern u8 D_800D52D0[];
extern u8 D_800621E4[];
extern u32 D_80075B28;


s32 func_8004FD34(s32 *arg0) {
    s32 *temp_v1_3;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    u32 *temp_v0;
    u32 temp_v1_2;
    u8 *temp_s0;

    temp_v1 = *arg0;
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        D_800D5294 = 0;
        D_800D5290 = 0;
        *arg0 = 0xA;
        /* fallthrough */
    case 10:                                        /* switch 1 */
        temp_v0 = (((s32) M2C_FIELD(D_800D52D0, s32 *, 0) >> 4) * 4) + (D_800D52D0 + 0x40);
        temp_v1_2 = *temp_v0;
        *temp_v0 = 0;
        D_80075B28 = temp_v1_2;
        func_80051D14();
        _card_info();
        *arg0 += 1;
block_30:
        return 0;
    case 11:                                        /* switch 1 */
        if (func_80051FCC() != 0) {
            temp_v0_2 = func_80051E1C();
            D_800D5294 = temp_v0_2;
            switch (temp_v0_2) {                    /* switch 2; irregular */
            case 4:                                 /* switch 2 */
                temp_v1_3 = (((s32) M2C_FIELD(D_800D52D0, s32 *, 0) >> 4) * 4) + (D_800D52D0 + 0x38);
                if ((*temp_v1_3 == 0) && ((u32) D_80075B28 < 0x80U)) {
                    *temp_v1_3 = 0;
                    func_80051D14();
                    _card_clear(M2C_FIELD(D_800D52D0, s32 *, 0));
                    *arg0 = 0x15;
                    goto block_30;
                }
            default:                                /* switch 2 */
block_26:
                M2C_FIELD(D_800D52C0, s32 *, 4) = func_800507D4(D_800D5294);
                return 1;
            case 0:                                 /* switch 2 */
                if (!(M2C_FIELD(D_800D52CC, s32 *, 0) & (1 << M2C_FIELD(D_800D52CC, s32 *, 4)))) {
                    D_800D5294 = 4;
                }
                M2C_FIELD((D_800D52CC - 0xC), s32 *, 4) = func_800507D4(D_800D5294);
                M2C_FIELD((D_800D52CC + (((s32) M2C_FIELD(D_800D52CC, s32 *, 4) >> 4) * 4)), s32 *, 0x3C) = 0;
                return 1;
            case 2:                                 /* switch 2 */
                temp_v0_3 = D_800D5290 + 1;
                D_800D5290 = temp_v0_3;
                if (temp_v0_3 >= 4) {
                    temp_s0 = D_800D52D0 - 0x10;
                    M2C_FIELD((D_800D52D0 + (((s32) M2C_FIELD(D_800D52D0, s32 *, 0) >> 4) * 4)), s32 *, 0x38) = 1;
                    M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (M2C_FIELD(D_800D52D0, s32 *, -4) & ~(1 << M2C_FIELD(D_800D52D0, s32 *, 0)));
                    M2C_FIELD(temp_s0, s32 *, 4) = func_800507D4(2);
                    return 1;
                }
block_25:
                *arg0 = 0xA;
                goto block_30;
            case 1:                                 /* switch 2 */
                temp_v0_4 = D_800D5290 + 1;
                D_800D5290 = temp_v0_4;
                if (temp_v0_4 < 9) {
                    goto block_25;
                }
                goto block_26;
            }
        } else {
            /* Duplicate return node #31. Try simplifying control flow for better match */
            return 0;
        }
        break;
    case 21:                                        /* switch 1 */
        if (func_80052008() != 0) {
            func_80051EF4();
            *((((s32) M2C_FIELD(D_800D52D0, s32 *, 0) >> 4) * 4) + (D_800D52D0 + 0x40)) = 0;
            *arg0 = 0;
        }
        /* Duplicate return node #31. Try simplifying control flow for better match */
        return 0;
    default:                                        /* switch 1 */
        printf((s32) "error");
        goto block_30;
    }
}
