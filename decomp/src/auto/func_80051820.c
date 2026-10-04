#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D52C0;
extern u8 D_80062360[];


s32 func_80051820(s32 arg0) {
    M2C_UNK sp10;
    s8 sp8F;
    s32 var_s0;
    s32 var_s0_2;
    s8 *var_v0;

    if (D_800D52C0 != 0) {
        printf((s32) D_80062360);
        return -1;
    }
    var_s0 = 0x7F;
    var_v0 = &sp8F;
    do {
        *var_v0 = -1;
        var_s0 -= 1;
        var_v0 -= 1;
    } while (var_s0 >= 0);
    var_s0_2 = 0;
loop_6:
    func_80051D14();
    _new_card();
    _card_write();
    var_s0_2 += 1;
    if (func_80051EF4() == 0) {
        if (var_s0_2 >= 0xF) {
            return 1;
        }
        goto loop_6;
    }
    return 0;
}
