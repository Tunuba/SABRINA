#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D52C0;
extern u8 D_80062360[];


void func_80051764(s32 arg0) {
    s32 var_a0;

    if (D_800D52C0 != 0) {
        printf((s32) D_80062360);
        return;
    }
loop_2:
    func_80051D14();
    if (func_80052578(arg0) == 0) {
        var_a0 = func_80051EF4();
        if (var_a0 & 4) {
            goto loop_2;
        }
    } else {
        func_80051D14();
        _card_load();
        do {

        } while (func_80051FCC() == 0);
        var_a0 = func_80051E1C();
    }
    func_800507D4(var_a0);
}
