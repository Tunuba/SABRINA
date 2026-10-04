#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D52C4[];
extern s32 D_80075B38;
extern s32 func_8004FD34();
extern s32 func_80050418();


s32 func_80050694(u32 *arg0) {
    s32 temp_v0;
    s32 var_v0;
    u32 temp_v1;
    u32 var_v0_2;

    temp_v1 = *arg0;
    switch (temp_v1) {
    case 0:
        D_80075B38 = 0;
        UserFuncOpen((s32) func_8004FD34);
        var_v0_2 = 0xA;
block_12:
        *arg0 = var_v0_2;
    default:
        var_v0 = 0;
        return var_v0;
    case 10:
        var_v0 = 1;
        if (M2C_FIELD(D_800D52C4, s32 *, 0) == 0) {
            temp_v0 = open();
            M2C_FIELD(D_800D52C4, s32 *, 0x10) = temp_v0;
            if (temp_v0 < 0) {
                M2C_FIELD((D_800D52C4 - 4), s32 *, 4) = 5;
                return 1;
            }
        case 11:
            *arg0 = 0x14;
            UserFuncOpen((s32) func_80050418);
            return 0;
        }
        /* Duplicate return node #14. Try simplifying control flow for better match */
        return var_v0;
    case 20:
        if (M2C_FIELD(D_800D52C4, s32 *, 0) == 3) {
            func_80051D14();
            _card_clear(M2C_FIELD(D_800D52C4, s32 *, 0xC));
            var_v0_2 = 0x16;
            goto block_12;
        }
        close();
        M2C_FIELD(D_800D52C4, s32 *, 0x10) = -1;
        return 1;
    case 22:
        var_v0 = 0;
        if (func_80052008() != 0) {
            func_80051EF4();
            var_v0_2 = 0xB;
            goto block_12;
        }
        /* Duplicate return node #14. Try simplifying control flow for better match */
        return var_v0;
    }
}
