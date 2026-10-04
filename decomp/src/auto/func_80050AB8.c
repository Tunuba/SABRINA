#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D52D0;
extern u8 D_800D52D4[];
extern s32 D_800D5318;
extern u8 D_800621BC[];
extern u8 D_800622B8[];
extern s32 func_80050034();


s32 func_80050AB8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp10;
    s32 var_s2;
    u8 *temp_s0;
    u8 *temp_s4;

    var_s2 = 0;
    if (M2C_FIELD(D_800D52D4, s32 *, 0) >= 0) {
        printf((s32) D_800622B8);
        return -1;
    }
    temp_s0 = D_800D52D4 + 0x10;
    func_800508D4(arg0, (s32) temp_s0);
    strcat((s32) temp_s0, arg1);
    M2C_FIELD(D_800D52D4, s32 *, -4) = arg0;
    temp_s4 = D_800D52D4 - 0x14;
loop_3:
loop_4:
    if (open() < 0) {
        D_800D5318 = func_80051284(0);
        if (M2C_FIELD(temp_s0, s32 *, -0x24) > 0) {
            printf((s32) D_800621BC);
        } else {
            M2C_FIELD(temp_s0, s32 *, -0x24) = 2;
            M2C_FIELD(temp_s4, s32 *, 4) = 0;
            M2C_FIELD(temp_s4, s32 *, 8) = 0;
            D_800D52D0 = arg0;
            UserFuncOpen((s32) func_80050034);
        }
        func_80051298(0, 0, (s32) &sp10);
        func_80051284(D_800D5318);
        if (sp10 != 3) {
            if ((sp10 != 2) || (var_s2 += 1, ((var_s2 < 5) == 0))) {
                if (sp10 == 0) {
                    sp10 = 5;
                }
                return sp10;
            }
            goto loop_3;
        }
        goto loop_4;
    }
    close();
    func_80051D14();
    M2C_FIELD(temp_s0, s32 *, -0x10) = open();
    return 0;
}
