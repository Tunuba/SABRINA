#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80083300[];
extern u8 D_80083304[];
extern u8 D_80083308[];
extern u8 D_8008330C[];
extern s32 * D_80063754;
extern s32 * D_80063760;
extern s32 D_80063774;
extern u8 D_80063798[];
extern s32 D_80063818;
extern s32 D_8006381C[];


s32 func_80012130(M2C_UNK (*arg0)(s32 *, s32), s32 *arg1, s32 arg2, s32 arg3) {
    s32 *var_a3;
    s32 temp_a0;
    s32 temp_a1;
    s32 var_a2;
    s32 var_v0;

    func_800128CC();
loop_3:
    if (((D_80063818 + 1) & 0x3F) != *D_8006381C) {
        D_80063774 = func_80016A14(0);
        M2C_FIELD(D_80063798, s32 *, 8) = 1;
        if ((D_80063798[1] == 0) || ((D_80063818 == *D_8006381C) && !(*D_80063760 & 0x01000000) && (M2C_FIELD(D_80063798, s32 *, 0xC) == 0))) {
            do {

            } while (!(*D_80063754 & 0x04000000));
            arg0(arg1, arg3);
            func_80016A14(D_80063774);
            return 0;
        }
        func_80016970();
        var_a2 = 0;
        if (arg2 != 0) {
            var_a3 = arg1;
loop_13:
            temp_a0 = var_a2 * 4;
            if (var_a2 < (arg2 / 4)) {
                temp_a1 = *var_a3;
                var_a3 += 4;
                var_a2 += 1;
                *(temp_a0 + ((D_80063818 * 0x60) + D_8008330C)) = temp_a1;
                goto loop_13;
            }
            *(D_80083304 + (D_80063818 * 0x60)) = (D_80063818 * 0x60) + D_8008330C;
        } else {
            *(D_80083304 + (D_80063818 * 0x60)) = arg1;
        }
        *(D_80083308 + (D_80063818 * 0x60)) = arg3;
        *(D_80083300 + (D_80063818 * 0x60)) = arg0;
        D_80063818 = (D_80063818 + 1) & 0x3F;
        func_80016A14(D_80063774);
        func_800123E0();
        var_v0 = (D_80063818 - *D_8006381C) & 0x3F;
        /* Duplicate return node #18. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = -1;
    if (func_80012900() == 0) {
        func_800123E0();
        goto loop_3;
    }
    return var_v0;
}
