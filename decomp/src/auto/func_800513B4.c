#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D52B4;
extern u8 D_800D52C0[];
extern s32 D_800D52C8;
extern s32 D_800D52D0;
extern s32 D_800D5318;
extern u8 D_800621BC[];
extern u8 D_80062360[];
extern s32 func_80050034();


s32 func_800513B4(s32 arg0, s32 arg1, s32 arg2) {
    M2C_UNK sp10;
    s32 sp30;
    s32 var_s2;

    var_s2 = 0;
    if (M2C_FIELD(D_800D52C0, s32 *, 0) != 0) {
        printf((s32) D_80062360);
        return -1;
    }
    func_800508D4(arg0, (s32) &sp10);
    strcat((s32) &sp10, arg1);
    M2C_FIELD(D_800D52C0, s32 *, 0xC) = (s32) (M2C_FIELD(D_800D52C0, s32 *, 0xC) | (1 << M2C_FIELD(D_800D52C0, s32 *, 0x10)));
    if (open() >= 0) {
        close();
        return 6;
    }
loop_6:
loop_7:
    if (open() < 0) {
        D_800D5318 = func_80051284(0);
        if (M2C_FIELD(D_800D52C0, s32 *, 0) > 0) {
            printf((s32) D_800621BC);
        } else {
            M2C_FIELD(D_800D52C0, s32 *, 0) = 2;
            M2C_FIELD(D_800D52C0, s32 *, 4) = 0;
            M2C_FIELD(D_800D52C0, s32 *, 8) = 0;
            D_800D52D0 = arg0;
            UserFuncOpen((s32) func_80050034);
        }
        if ((M2C_FIELD(D_800D52C0, s32 *, 0) != 0) || (M2C_FIELD(D_800D52C0, s32 *, 8) != 0)) {
            if (M2C_FIELD(D_800D52C0, s32 *, 8) == 0) {
                do {

                } while (D_800D52C8 == 0);
            }
            M2C_FIELD(D_800D52C0, s32 *, 8) = 0;
            sp30 = D_800D52B4;
        }
        func_80051284(D_800D5318);
        if (sp30 != 0) {
            if (sp30 != 3) {
                if ((sp30 != 2) || (var_s2 += 1, ((var_s2 < 4) == 0))) {
                    if (sp30 == 0) {
                        sp30 = 5;
                    }
                    return sp30;
                }
                goto loop_6;
            }
            goto loop_7;
        }
        return 7;
    }
    close();
    return 0;
}
