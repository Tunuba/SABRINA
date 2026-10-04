#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006246C[];


s32 func_80052434(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp10;
    s32 var_a0;
    s32 var_a1_2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    s8 temp_v0_2;
    s8 var_a1;
    u8 *var_a0_2;
    u8 temp_v0;
    u8 temp_v0_3;

    var_s1 = 0;
    var_v1 = arg2;
    var_a1 = 0;
    var_a0 = 0x7E;
    do {
        temp_v0 = *var_v1;
        var_v1 += 1;
        var_a0 -= 1;
        temp_v0_2 = var_a1 ^ temp_v0;
        var_a1 = temp_v0_2;
    } while (var_a0 >= 0);
    *var_v1 = temp_v0_2;
loop_3:
    var_v0 = 0;
    if (var_s1 < 8) {
        _new_card();
        var_v0 = 0;
        if (_card_write() == 1) {
            do {

            } while (!(_card_status() & 1));
            bzero((s32) &sp10, 0x80);
            _new_card();
            if (_card_read() != 1) {
                printf((s32) D_8006246C);
                var_a0_2 = &sp10;
            } else {
                do {
                    var_a0_2 = &sp10;
                } while (!(_card_status() & 1));
            }
            var_a1_2 = 0;
            var_v1_2 = 0x7E;
            do {
                temp_v0_3 = *var_a0_2;
                var_a0_2 += 1;
                var_v1_2 -= 1;
                var_a1_2 ^= temp_v0_3;
            } while (var_v1_2 >= 0);
            var_s1 += 1;
            if (M2C_FIELD(arg2, u8 *, 0x7F) == (var_a1_2 & 0xFF)) {
                var_v0 = 1;
            } else {
                goto loop_3;
            }
        }
    }
    return var_v0;
}
